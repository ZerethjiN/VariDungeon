#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void lavaSlimeMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsLavaSlimeMove, Orientation, const Speed, const LavaSlime, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isLavaSlimeMove, orientation, speed, lavaSlime, enemyTransform, zindex]: enemies) {
        if (isLavaSlimeMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsLavaSlimeMove>(enemyEnt);
            world.add_components(enemyEnt, IsLavaSlimePreAttack(lavaSlime.preAttackDuration));

            world.append_children(enemyEnt, {
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, -16), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0), zindex),
                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 16), zindex),
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
                    animation.play(LavaSlimeAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(LavaSlimeAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(LavaSlimeAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(LavaSlimeAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(LavaSlimeAnimType::MOVE_UP);
                }
            }
        }
    }
}

void lavaSlimeAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsLavaSlimePreAttack, Orientation, const LavaSlime, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isLavaSlimePreAttack, orientation, lavaSlime, enemyTransform]: enemies) {
        if (isLavaSlimePreAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsLavaSlimePreAttack>(enemyEnt);
            world.add_components(enemyEnt, IsLavaSlimeMove(lavaSlime.moveDuration));

            world.append_children(enemyEnt, {
                instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition())
            });
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(LavaSlimeAnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(LavaSlimeAnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(LavaSlimeAnimType::PRE_ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(LavaSlimeAnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(LavaSlimeAnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}