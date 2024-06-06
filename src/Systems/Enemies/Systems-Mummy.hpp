#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void mummyMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsMummyMove, Orientation, const Speed, const Mummy, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isMummyMove, orientation, speed, mummy, enemyTransform, zindex]: enemies) {
        if (isMummyMove.canSwitchState(time.fixedDelta())) {
            world.del<IsMummyMove>(enemyEnt);
            world.add(enemyEnt, IsMummyPreAttack(mummy.getPreAttackDuration()));

            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0), zindex)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0), zindex)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16), zindex)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16), zindex)
                    });
                }
            }

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

void mummyPreAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyPreAttack, Orientation, const Mummy, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyPreAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyPreAttack.canSwitchState(time.fixedDelta())) {
            world.del<IsMummyPreAttack>(enemyEnt);
            world.add(enemyEnt, IsMummyAttack(mummy.getAttackDuration()));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.newEnt(
                        Transform(
                            enemyTransform.getPosition() + glm::vec2(16, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Trigger(-12 / 2, -12 / 2, 12, 12),
                        LifeTime(0.25f),
                        EnemyWeapon()
                    );
                } else {
                    world.newEnt(
                        Transform(
                            enemyTransform.getPosition() + glm::vec2(-16, 0),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Trigger(-12 / 2, -12 / 2, 12, 12),
                        LifeTime(0.25f),
                        EnemyWeapon()
                    );
                }
            } else {
                if (orientation.y > 0) {
                    world.newEnt(
                        Transform(
                            enemyTransform.getPosition() + glm::vec2(0, 16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Trigger(-12 / 2, -12 / 2, 12, 12),
                        LifeTime(0.25f),
                        EnemyWeapon()
                    );
                } else {
                    world.newEnt(
                        Transform(
                            enemyTransform.getPosition() + glm::vec2(0, -16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        Trigger(-12 / 2, -12 / 2, 12, 12),
                        LifeTime(0.25f),
                        EnemyWeapon()
                    );
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

void mummyAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsMummyAttack, Orientation, const Mummy, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isMummyAttack, orientation, mummy, enemyTransform]: enemies) {
        if (isMummyAttack.canSwitchState(time.fixedDelta())) {
            world.del<IsMummyAttack>(enemyEnt);
            world.add(enemyEnt, IsMummyMove(mummy.getMoveDuration()));
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