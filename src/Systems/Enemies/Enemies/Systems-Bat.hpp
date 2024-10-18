#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void batMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsBatMove, Orientation, const Speed, const Bat, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isBatMove, orientation, speed, bat, enemyTransform, zindex]: enemies) {
        if (isBatMove.canSwitchState(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= bat.attackRadius) {
                    world.remove_components<IsBatMove>(enemyEnt);
                    world.add_components(enemyEnt, IsBatAttack(bat.attackDuration));

                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 0, +16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 0, -16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1, +16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1,   0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1, -16), zindex)
                            });
                        } else {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 0, +16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 0, -16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1, +16), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1,   0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1, -16), zindex)
                            });
                        }
                    } else {
                        if (orientation.y > 0) {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, 16 * 0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16 * 0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, 16 * 1), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, 16 * 1), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16 * 1), zindex)
                            });
                        } else {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, -16 * 0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16 * 0), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, -16 * 1), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, -16 * 1), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16 * 1), zindex)
                            });
                        }
                    }
                    continue;
                }
            }
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
                    animation.play(BatAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(BatAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(BatAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(BatAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(BatAnimType::MOVE_UP);
                }
            }
        }
    }
}

void batAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsBatAttack, Orientation, const Bat, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isBatAttack, orientation, bat, enemyTransform]: enemies) {
        if (isBatAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsBatAttack>(enemyEnt);
            world.add_components(enemyEnt, IsBatMove(bat.moveDuration));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 90)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 270)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 180)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 0)
                    });
                }
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(BatAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(BatAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(BatAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(BatAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(BatAnimType::ATTACK_UP);
                }
            }
        }
    }
}