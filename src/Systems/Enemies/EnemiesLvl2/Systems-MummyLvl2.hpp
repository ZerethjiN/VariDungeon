#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void mummyLvl2MoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMummyLvl2Move, Orientation, const Speed, const MummyLvl2, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMummyMove, orientation, speed, mummy, enemyTransform, zindex]: enemies) {
        if (isMummyMove.canTick(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= mummy.attackRadius) {
                    world.remove_components<IsMummyLvl2Move>(enemyEnt);
                    world.add_components(enemyEnt, IsMummyLvl2PreAttack(mummy.preAttackDuration));

                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, 8), zindex)
                            });
                        } else {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex)
                            });
                        }
                    } else {
                        if (orientation.y > 0) {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 24), zindex)
                            });
                        } else {
                            world.append_children(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex)
                            });
                        }
                    }

                    continue;
                } else {
                    isMummyMove.resetTick();
                    instantiateShadowMarkParticle(world, playerTransform.getPosition());

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
                    animation.play(MummyLvl2AnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(MummyLvl2AnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(MummyLvl2AnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(MummyLvl2AnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_MOVE_UP);
                } else {
                    animation.play(MummyLvl2AnimType::MOVE_UP);
                }
            }
        }
    }
}

void mummyLvl2PreAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyLvl2PreAttack, Orientation, const MummyLvl2, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyPreAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyPreAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsMummyLvl2PreAttack>(enemyEnt);
            world.add_components(enemyEnt, IsMummyLvl2Attack(mummy.attackDuration));
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(MummyLvl2AnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(MummyLvl2AnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(MummyLvl2AnimType::PRE_ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(MummyLvl2AnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}

void mummyLvl2AttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyLvl2Attack, Orientation, const MummyLvl2, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsMummyLvl2Attack>(enemyEnt);
            world.add_components(enemyEnt, IsMummyLvl2Move(mummy.moveDuration));
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(MummyLvl2AnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(MummyLvl2AnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(MummyLvl2AnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MummyLvl2AnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(MummyLvl2AnimType::ATTACK_UP);
                }
            }
        }
    }
}