#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void anubisLvl2AttackSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsAnubisLvl2Attack, Orientation, AnubisLvl2, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isAnubisAttack, orientation, anubis, enemyTransform]: enemies) {
        if (isAnubisAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsAnubisLvl2Attack>(enemyEnt);

            if (auto oth = world.get_components<const Collider>(enemyEnt)) {
                auto [collider] = oth.value();
                anubis.tmpCol = collider.col;
                world.remove_components<Collider>(enemyEnt);

                world.add_components(enemyEnt, IsAnubisLvl2Vanish(anubis.vanishDuration));

                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        animation.play(AnubisLvl2AnimType::VANISH_RIGHT);
                    } else {
                        animation.play(AnubisLvl2AnimType::VANISH_LEFT);
                    }
                } else {
                    if (orientation.y > 0) {
                        animation.play(AnubisLvl2AnimType::VANISH_DOWN);
                    } else {
                        animation.play(AnubisLvl2AnimType::VANISH_UP);
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisLvl2AnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(AnubisLvl2AnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisLvl2AnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(AnubisLvl2AnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisLvl2AnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(AnubisLvl2AnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(AnubisLvl2AnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(AnubisLvl2AnimType::ATTACK_UP);
                }
            }
        }
    }
}

void anubisLvl2VanishSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsAnubisLvl2Vanish, Orientation, const Speed, const AnubisLvl2, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isAnubisMove, orientation, speed, anubis, enemyTransform, zindex]: enemies) {
        if (isAnubisMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsAnubisLvl2Vanish>(enemyEnt);
            world.add_components(enemyEnt, IsAnubisLvl2Attack(anubis.attackDuration));

            if (!world.has_components<Collider>(enemyEnt)) {
                world.add_components(enemyEnt, Collider(anubis.tmpCol));
            }

            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex)
                        });
                    } else {
                        world.append_children(enemyEnt, {
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