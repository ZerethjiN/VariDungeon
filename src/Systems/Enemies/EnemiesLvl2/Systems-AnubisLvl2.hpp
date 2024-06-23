#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void anubisLvl2AttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsAnubisLvl2Attack, Orientation, AnubisLvl2, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isAnubisAttack, orientation, anubis, enemyTransform]: enemies) {
        if (isAnubisAttack.canSwitchState(time.fixedDelta())) {
            world.remove<IsAnubisLvl2Attack>(enemyEnt);

            if (auto oth = world.get<const Collider>(enemyEnt)) {
                auto [collider] = oth.value();
                anubis.tmpCol = collider.col;
                world.remove<Collider>(enemyEnt);

                world.add(enemyEnt, IsAnubisLvl2Vanish(anubis.vanishDuration));

                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        animation.play("VanishRight");
                    } else {
                        animation.play("VanishLeft");
                    }
                } else {
                    if (orientation.y > 0) {
                        animation.play("VanishDown");
                    } else {
                        animation.play("VanishUp");
                    }
                }
            } else {
                printf("Error Script Anubis\n");
            }

            instantiateFireBallParticle(world, enemyTransform.getPosition(), orientation.orientation, 128.f);

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

void anubisLvl2VanishSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsAnubisLvl2Vanish, Orientation, const Speed, const AnubisLvl2, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isAnubisMove, orientation, speed, anubis, enemyTransform, zindex]: enemies) {
        if (isAnubisMove.canSwitchState(time.fixedDelta())) {
            world.remove<IsAnubisLvl2Vanish>(enemyEnt);
            world.add(enemyEnt, IsAnubisLvl2Attack(anubis.attackDuration));

            if (!world.has<Collider>(enemyEnt)) {
                world.add(enemyEnt, Collider(anubis.tmpCol));
            }

            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex)
                        });
                    } else {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex)
                        });
                    } else {
                        world.appendChildren(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex)
                        });
                    }
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
            } else {
                orientation = Orientation::WEST;
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
            } else {
                orientation = Orientation::NORTH;
            }
        }
    }
}