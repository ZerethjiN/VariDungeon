#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void mummyLvl2MoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMummyLvl2Move, Orientation, const Speed, const MummyLvl2, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMummyMove, orientation, speed, mummy, enemyTransform, zindex]: enemies) {
        if (isMummyMove.canSwitchState(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) <= mummy.attackRadius) {
                    world.remove<IsMummyLvl2Move>(enemyEnt);
                    world.add(enemyEnt, IsMummyLvl2PreAttack(mummy.preAttackDuration));

                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(24, 8), zindex)
                            });
                        } else {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex)
                            });
                        }
                    } else {
                        if (orientation.y > 0) {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, 24), zindex)
                            });
                        } else {
                            world.appendChildren(enemyEnt, {
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -24), zindex),
                                instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), zindex)
                            });
                        }
                    }

                    continue;
                } else {
                    isMummyMove.resetStateTimer();
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

void mummyLvl2PreAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyLvl2PreAttack, Orientation, const MummyLvl2, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyPreAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyPreAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsMummyLvl2PreAttack>(enemyEnt);
            world.add(enemyEnt, IsMummyLvl2Attack(mummy.attackDuration));
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

void mummyLvl2AttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyLvl2Attack, Orientation, const MummyLvl2, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsMummyLvl2Attack>(enemyEnt);
            world.add(enemyEnt, IsMummyLvl2Move(mummy.moveDuration));
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