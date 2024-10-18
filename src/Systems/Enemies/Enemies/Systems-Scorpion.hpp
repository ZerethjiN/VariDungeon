#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void scorpionMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsScorpionMove, Orientation, const Speed, const Scorpion, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isScorpionMove, orientation, speed, scorpion, transform, zindex]: enemies) {
        if (isScorpionMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsScorpionMove>(enemyEnt);
            world.add_components(enemyEnt, IsScorpionCast(scorpion.castDuration));

            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, -16 * i), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, -16 * i), zindex)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                            instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(ScorpionAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(ScorpionAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(ScorpionAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(ScorpionAnimType::MOVE_UP);
                }
            }
        }
    }
}

void scorpionAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsScorpionCast, const Transform2D, const Orientation, const Scorpion>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isScorpionCast, enemyTransform, orientation, scorpion]: enemies) {
        if (isScorpionCast.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsScorpionCast>(enemyEnt);
            world.add_components(enemyEnt, IsScorpionMove(scorpion.moveDuration));

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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(ScorpionAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(ScorpionAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(ScorpionAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(ScorpionAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(ScorpionAnimType::ATTACK_UP);
                }
            }
        }
    }
}