#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void voidSlimeMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsVoidSlimeMove, Orientation, const Speed, const VoidSlime, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isVoidSlimeMove, orientation, speed, voidSlime, enemyTransform, zindex]: enemies) {
        if (isVoidSlimeMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsVoidSlimeMove>(enemyEnt);
            world.add_components(enemyEnt, IsVoidSlimeAttract(voidSlime.attractDuration));

            world.append_children(enemyEnt, {
                instantiateAttractParticle(world, enemyTransform.getPosition(), zindex + 1, voidSlime.attractDuration)
            });
            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(VoidSlimeAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(VoidSlimeAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(VoidSlimeAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(VoidSlimeAnimType::MOVE_UP);
                }
            }
        }
    }
}

void voidSlimeAttractSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsVoidSlimeAttract, Orientation, const VoidSlime, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.query<Velocity, const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isVoidSlimeAttract, orientation, voidSlime, enemyTransform]: enemies) {
        if (isVoidSlimeAttract.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsVoidSlimeAttract>(enemyEnt);
            world.add_components(enemyEnt, IsVoidSlimeMove(voidSlime.moveDuration));
            continue;
        }

        for (auto [_, playerVelocity, playerTransform]: players) {
            playerVelocity.vel += glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()) * voidSlime.attractStrength * time.fixedDelta();

            if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= voidSlime.attractRadius) {
                world.append_children(enemyEnt, {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition())
                });
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(VoidSlimeAnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(VoidSlimeAnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(VoidSlimeAnimType::PRE_ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(VoidSlimeAnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(VoidSlimeAnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}