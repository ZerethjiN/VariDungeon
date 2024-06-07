#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void voidSlimeMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsVoidSlimeMove, Orientation, const Speed, const VoidSlime, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isVoidSlimeMove, orientation, speed, voidSlime, enemyTransform, zindex]: enemies) {
        if (isVoidSlimeMove.canSwitchState(time.fixedDelta())) {
            world.remove<IsVoidSlimeMove>(enemyEnt);
            world.add(enemyEnt, IsVoidSlimeAttract(voidSlime.attractDuration));

            world.appendChildren(enemyEnt, {
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
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveRight");
                } else {
                    animation.play("MoveRight");
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveLeft");
                } else {
                    animation.play("MoveLeft");
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveDown");
                } else {
                    animation.play("MoveDown");
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitMoveUp");
                } else {
                    animation.play("MoveUp");
                }
            }
        }
    }
}

void voidSlimeAttractSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsVoidSlimeAttract, Orientation, const VoidSlime, const Transform>(without<EnemyPreSpawn>);
    auto players = world.view<Velocity, const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isVoidSlimeAttract, orientation, voidSlime, enemyTransform]: enemies) {
        if (isVoidSlimeAttract.canSwitchState(time.fixedDelta())) {
            world.remove<IsVoidSlimeAttract>(enemyEnt);
            world.add(enemyEnt, IsVoidSlimeMove(voidSlime.moveDuration));
            continue;
        }

        for (auto [_, playerVelocity, playerTransform]: players) {
            playerVelocity.vel += glm::normalize(enemyTransform.getPosition() - playerTransform.getPosition()) * voidSlime.attractStrength * time.fixedDelta();

            if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= voidSlime.attractRadius) {
                world.appendChildren(enemyEnt, {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition())
                });
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackRight");
                } else {
                    animation.play("PreAttackRight");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackLeft");
                } else {
                    animation.play("PreAttackLeft");
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackDown");
                } else {
                    animation.play("PreAttackDown");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackUp");
                } else {
                    animation.play("PreAttackUp");
                }
            }
        }
    }
}