#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rockBossPreRollSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsRockBossPreRoll, const Orientation, const RockBoss>(with<Unhittable>, without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemy_ent, animation, is_rock_boss_pre_roll, orientation, rock_boss]: enemies) {
        if (is_rock_boss_pre_roll.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsRockBossPreRoll>(enemy_ent);
            world.add_components(enemy_ent, IsRockBossRoll());
        }
    }
}

void rockBossRollSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, RockBoss, const Orientation, const Speed>(with<IsRockBossRoll, Unhittable>, without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, rockBoss, orientation, speed]: enemies) {
        if (auto opt = world.get_components<const OnCollisionEnter>(enemyEnt)) {
            auto [collisions] = opt.value();

            bool isHit = false;
            for (auto othEnt: collisions) {
                if (world.has_components<Collider>(othEnt)) {
                    world.remove_components<IsRockBossRoll, Unhittable>(enemyEnt);
                    world.add_components(enemyEnt, IsRockBossStun(rockBoss.stunDuration));
                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            animation.play(RockBossAnimType::STUN_RIGHT);
                        } else {
                            animation.play(RockBossAnimType::STUN_LEFT);
                        }
                    } else {
                        if (orientation.y > 0) {
                            animation.play(RockBossAnimType::STUN_DOWN);
                        } else {
                            animation.play(RockBossAnimType::STUN_UP);
                        }
                    }

                    if (auto childrenOpt = world.get_children(enemyEnt)) {
                        for (auto childrenEnt: childrenOpt.value().get()) {
                            if (world.has_components<SmallCrystalRotation>(childrenEnt)) {
                                world.delete_entity(childrenEnt);
                            }
                        }
                    }

                    isHit = true;

                    continue;
                }
            }

            if (isHit) {
                continue;
            }
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                animation.play(RockBossAnimType::ROLL_RIGHT);
                velocity.vel.x += speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            } else {
                animation.play(RockBossAnimType::ROLL_LEFT);
                velocity.vel.x -= speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            }
        } else {
            if (orientation.y > 0) {
                animation.play(RockBossAnimType::ROLL_DOWN);
                velocity.vel.y += speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            } else {
                animation.play(RockBossAnimType::ROLL_UP);
                velocity.vel.y -= speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            }
        }
    }
}

void rockBossStunSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Animation, IsRockBossStun, RockBoss, const Orientation, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockBossStun, rockBoss, orientation, enemyTransform]: enemies) {
        if (isRockBossStun.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsRockBossStun>(enemyEnt);
            world.add_components(enemyEnt, IsRockBossGroundCrystals(rockBoss.groundCrystalsCooldown), Unhittable());

            world.append_children(enemyEnt, {
                instantiateSmallCrystalParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16), 0.f, 16.f, glm::vec2(0, -16)),
                instantiateSmallCrystalParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16), +180.f, 16.f, glm::vec2(0, 16)),
                instantiateSmallCrystalParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0), -90.f, 16.f, glm::vec2(-16, 0)),
                instantiateSmallCrystalParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0), +90.f, 16.f, glm::vec2(16, 0)),
            });

            // switch (rand() % 2) {
            //     case 0:
            //         for (auto [_, roomTransform]: world.query<const Transform2D>(with<ChunkInfos>)) {
            //             for (int l = 0; l < 3; l++) {
            //                 for (int i = 0; i < 8; i++) {
            //                     instantiateGroundCrystalAttack(world, roomTransform.getPosition() + glm::vec2(i * 16.f - 64.f,  l * 40.f - 48.f));
            //                 }
            //             }
            //         }
            //         break;
            //     case 1:
            //         for (auto [_, roomTransform]: world.query<const Transform2D>(with<ChunkInfos>)) {
            //             for (int l = 0; l < 3; l++) {
            //                 for (int i = 0; i < 6; i++) {
            //                     instantiateGroundCrystalAttack(world, roomTransform.getPosition() + glm::vec2(l * 56.f - 64.f, i * 16.f - 48.f));
            //                 }
            //             }
            //         }
            //         break;
            // }

            for (auto i = 1; i < 8; i++) {
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2( i * 16.f, 0));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(-i * 16.f, 0));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(0,  i * 16.f));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(0, -i * 16.f));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2( i * 16.f, i * 16.f));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(-i * 16.f, i * 16.f));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(i * 16.f, -i * 16.f));
                instantiateGroundCrystalAttack(world, enemyTransform.getPosition() + glm::vec2(-i * 16.f, -i * 16.f));
            }
            
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockBossAnimType::HIT_STUN_RIGHT);
                } else {
                    animation.play(RockBossAnimType::STUN_RIGHT);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockBossAnimType::HIT_STUN_LEFT);
                } else {
                    animation.play(RockBossAnimType::STUN_RIGHT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockBossAnimType::HIT_STUN_DOWN);
                } else {
                    animation.play(RockBossAnimType::STUN_DOWN);
                }
            } else {
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockBossAnimType::HIT_STUN_UP);
                } else {
                    animation.play(RockBossAnimType::STUN_UP);
                }
            }
        }
    }
}

void rockBossGroundCrystalsSys(MainFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsRockBossGroundCrystals, RockBoss, Orientation, const Speed, const Transform2D>(with<Unhittable>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRockBossGroundCrystals, rockBoss, orientation, speed, enemyTransform]: enemies) {
        if (isRockBossGroundCrystals.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsRockBossGroundCrystals>(enemyEnt);
            world.add_components(enemyEnt, IsRockBossPreRoll(rockBoss.pre_roll_cooldown));
            for (int i = 1; i < 7; i++) {
                if (fabs(orientation.x) > fabs(orientation.y)) {
                    if (orientation.x > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), 15)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), 15)
                        });
                    }
                } else {
                    if (orientation.y > 0) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), 15)
                        });
                    } else {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), 15)
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
                animation.play(RockBossAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(RockBossAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(RockBossAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(RockBossAnimType::MOVE_UP);
            }
        }
    }
}

void rockBossSmallCrystalThrowSys(MainFixedSystem, World& world) {
    auto enemies = world.query<RockBoss>(without<IsRockBossStun, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, rockBoss]: enemies) {
        if (rockBoss.canThrowSmallCrystal(time.fixedDelta())) {
            for (auto [smallCrystalEnt]: world.query(with<SmallCrystalRotation>)) {
                for (auto [_, playerTransform, zindex]: world.query<const Transform2D, const ZIndex>(with<Player>)) {
                    world.remove_components<SmallCrystalRotation>(smallCrystalEnt);
                    world.add_components(smallCrystalEnt, SmallCrystalThrow(playerTransform.getPosition(), 64.f));
                    instantiateFloorCrossParticle(world, playerTransform.getPosition(), zindex);
                }
                break;
            }
        }
    }
}