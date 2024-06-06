#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void spectreMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSpectreMove, Orientation, const Speed, const Spectre, const Transform>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreMove, orientation, speed, spectre, enemyTransform]: enemies) {
        if (isSpectreMove.canSwitchState(time.fixedDelta())) {
            world.del<IsSpectreMove>(enemyEnt);
            switch (rand() % 2) {
                case 0:
                    world.add(enemyEnt, IsSpectreVanish(spectre.vanishDuration));
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
                    world.del<Collider>(enemyEnt);
                    break;

                case 1:
                    world.add(enemyEnt, IsSpectreCast(spectre.castDuration));
                    for (auto [_, playerTransform]: players) {
                        instantiateShadowMarkParticle(world, playerTransform.getPosition());
                    }
                    break;
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

void spectreVanishSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSpectreVanish, Orientation, const Spectre, const Speed, const Transform>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreVanish, orientation, spectre, speed, enemyTransform]: enemies) {
        if (isSpectreVanish.canSwitchState(time.fixedDelta())) {
            world.del<IsSpectreVanish>(enemyEnt);
            world.add(enemyEnt, IsSpectreMove(spectre.moveDuration));
            world.add(enemyEnt, Collider(-12 / 2, -12 / 2, 12, 12));
            instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, -1), 32.f);
            instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, +1), 32.f);
            instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(+1, -1), 32.f);
            instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(+1, +1), 32.f);
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

void spectreCastSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSpectreCast, Orientation, const Speed, const Spectre, const Transform>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreCast, orientation, speed, spectre, enemyTransform]: enemies) {
        if (isSpectreCast.canSwitchState(time.fixedDelta())) {
            world.del<IsSpectreCast>(enemyEnt);
            world.add(enemyEnt, IsSpectreMove(spectre.moveDuration));

            continue;
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * 0.5f * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackRight");
                } else {
                    animation.play("AttackRight");
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackLeft");
                } else {
                    animation.play("AttackLeft");
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackDown");
                } else {
                    animation.play("AttackDown");
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitAttackUp");
                } else {
                    animation.play("AttackUp");
                }
            }
        }
    }
}