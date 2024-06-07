#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void scorpionMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsScorpionMove, Orientation, const Speed, const Scorpion, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isScorpionMove, orientation, speed, scorpion, transform, zindex]: enemies) {
        if (isScorpionMove.canSwitchState(time.fixedDelta())) {
            world.remove<IsScorpionMove>(enemyEnt);
            world.add(enemyEnt, IsScorpionCast(scorpion.castDuration));

            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, -16 * i), zindex)
                        });
                    } else {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, -16 * i), zindex)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex)
                        });
                    } else {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, -16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, -16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, -16 * i), zindex)
                        });
                    }
                }
            }

            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - transform.getPosition());
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

void scorpionAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsScorpionCast, const Transform, const Orientation, const Scorpion>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isScorpionCast, enemyTransform, orientation, scorpion]: enemies) {
        if (isScorpionCast.canSwitchState(time.fixedDelta())) {
            world.remove<IsScorpionCast>(enemyEnt);
            world.add(enemyEnt, IsScorpionMove(scorpion.moveDuration));

            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(1, 0), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(1, 1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(1, -1), 128.f);
                } else {
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, 0), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, 1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, -1), 128.f);
                }
            } else {
                if (orientation.y > 0) {
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(0, 1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(1, 1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, 1), 128.f);
                } else {
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(0, -1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(1, -1), 128.f);
                    instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, -1), 128.f);
                }
            }

            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackRight");
                } else {
                    animation.play("AttackRight");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackLeft");
                } else {
                    animation.play("AttackLeft");
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackDown");
                } else {
                    animation.play("AttackDown");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackUp");
                } else {
                    animation.play("AttackUp");
                }
            }
        }
    }
}