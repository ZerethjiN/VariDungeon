#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rockBossRollSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsRockBossRoll, RockBoss, const Orientation, const Speed>(with<Unhittable>, without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRockBossRoll, rockBoss, orientation, speed]: enemies) {
        if (auto opt = world.get<const OnCollisionEnter>(enemyEnt)) {
            auto [collisions] = opt.value();

            bool isHit = false;
            for (auto othEnt: collisions) {
                if (world.has<Collider>(othEnt)) {
                    world.remove<IsRockBossRoll, Unhittable>(enemyEnt);
                    world.add(enemyEnt, IsRockBossStun(rockBoss.stunDuration));
                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            animation.play("StunRight");
                        } else {
                            animation.play("StunLeft");
                        }
                    } else {
                        if (orientation.y > 0) {
                            animation.play("StunDown");
                        } else {
                            animation.play("StunUp");
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
                animation.play("RollRight");
                velocity.vel.x += speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            } else {
                animation.play("RollLeft");
                velocity.vel.x -= speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            }
        } else {
            if (orientation.y > 0) {
                animation.play("RollDown");
                velocity.vel.y += speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            } else {
                animation.play("RollUp");
                velocity.vel.y -= speed.speed * rockBoss.rollSpeedCoeff * time.fixedDelta();
            }
        }
    }
}

void rockBossStunSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsRockBossStun, RockBoss, const Orientation>(without<Unmoveable, EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockBossStun, rockBoss, orientation]: enemies) {
        if (isRockBossStun.canSwitchState(time.fixedDelta())) {
            world.remove<IsRockBossStun>(enemyEnt);
            world.add(enemyEnt, IsRockBossGroundCrystals(rockBoss.groundCrystalsCooldown), Unhittable());

            switch (rand() % 2) {
                case 0:
                    for (auto [_, roomTransform]: world.view<const Transform>(with<ChunkInfos>)) {
                        for (int l = 0; l < 3; l++) {
                            for (int i = 0; i < 8; i++) {
                                instantiateGroundCrystalAttack(world, roomTransform.getPosition() + glm::vec2(i * 16.f - 64.f,  l * 40.f - 48.f));
                            }
                        }
                    }
                    break;
                case 1:
                    for (auto [_, roomTransform]: world.view<const Transform>(with<ChunkInfos>)) {
                        for (int l = 0; l < 3; l++) {
                            for (int i = 0; i < 6; i++) {
                                instantiateGroundCrystalAttack(world, roomTransform.getPosition() + glm::vec2(l * 56.f - 64.f, i * 16.f - 48.f));
                            }
                        }
                    }
                    break;
            }
            
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitStunRight");
                } else {
                    animation.play("StunRight");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitStunLeft");
                } else {
                    animation.play("StunLeft");
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitStunDown");
                } else {
                    animation.play("StunDown");
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitStunUp");
                } else {
                    animation.play("StunUp");
                }
            }
        }
    }
}

void rockBossGroundCrystalsSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsRockBossGroundCrystals, RockBoss, Orientation, const Speed, const Transform>(with<Unhittable>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRockBossGroundCrystals, rockBoss, orientation, speed, enemyTransform]: enemies) {
        if (isRockBossGroundCrystals.canSwitchState(time.fixedDelta())) {
            world.remove<IsRockBossGroundCrystals>(enemyEnt);
            world.add(enemyEnt, IsRockBossRoll());
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
                animation.play("MoveRight");
            } else {
                orientation = Orientation::WEST;
                animation.play("MoveLeft");
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play("MoveDown");
            } else {
                orientation = Orientation::NORTH;
                animation.play("MoveUp");
            }
        }
    }
}