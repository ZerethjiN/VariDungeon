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

                    continue;;
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
            world.add(enemyEnt, IsRockBossRoll(), Unhittable());
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