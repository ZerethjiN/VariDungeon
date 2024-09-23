#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

// Run With: [mummyMoveSys, mummyPreAttack, mummyAttackSys]
void mummyMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMummyMove, Orientation, const Speed, const Mummy, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMummyMove, orientation, speed, mummy, enemyTransform, zindex]: enemies) {
        if (isMummyMove.canSwitchState(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= mummy.attackRadius) {
                    world.remove_component<IsMummyMove>(enemyEnt);
                    world.add_component(enemyEnt, IsMummyPreAttack(mummy.preAttackDuration));

                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, 8), zindex),
                            });
                        } else {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                            });
                        }
                    } else {
                        if (orientation.y > 0) {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 24), zindex),
                            });
                        } else {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex),
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
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(MummyAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(MummyAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(MummyAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(MummyAnimType::MOVE_UP);
                }
            }
        }
    }
}

// Run With: [mummyMoveSys, mummyPreAttack, mummyAttackSys]
void mummyPreAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyPreAttack, Orientation, const Mummy, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyPreAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyPreAttack.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMummyPreAttack>(enemyEnt);
            world.add_component(enemyEnt, IsMummyAttack(mummy.attackDuration));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0));
                } else {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0));
                }
            } else {
                if (orientation.y > 0) {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16));
                } else {
                    instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16));
                }
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(MummyAnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(MummyAnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(MummyAnimType::PRE_ATTACK_DOWN);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(MummyAnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}

// Run With: [mummyMoveSys, mummyPreAttack, mummyAttackSys]
void mummyAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyAttack, Orientation, const Mummy, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyAttack.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsMummyAttack>(enemyEnt);
            world.add_component(enemyEnt, IsMummyMove(mummy.moveDuration));
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(MummyAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(MummyAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(MummyAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(MummyAnimType::ATTACK_UP);
                }
            }
        }
    }
}