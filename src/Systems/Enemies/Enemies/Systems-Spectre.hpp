#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

// Run With: [spectreMoveSys, spectreVanishSys, spectreCastSys]
void spectreMoveSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsSpectreMove, Orientation, const Speed, const Spectre, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreMove, orientation, speed, spectre, enemyTransform]: enemies) {
        if (isSpectreMove.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsSpectreMove>(enemyEnt);
            switch (rand() % 3) {
                case 0:
                    world.add_components(enemyEnt, IsSpectreVanish(spectre.vanishDuration));
                    if (fabs(orientation.x) > fabs(orientation.y)) {
                        if (orientation.x > 0) {
                            animation.play(SpectreAnimType::VANISH_RIGHT);
                        } else {
                            animation.play(SpectreAnimType::VANISH_LEFT);
                        }
                    } else {
                        if (orientation.y > 0) {
                            animation.play(SpectreAnimType::VANISH_DOWN);
                        } else {
                            animation.play(SpectreAnimType::VANISH_UP);
                        }
                    }
                    world.remove_components<Collider>(enemyEnt);
                    break;

                case 1:
                case 2:
                    world.add_components(enemyEnt, IsSpectreCast(spectre.castDuration));
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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(SpectreAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(SpectreAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(SpectreAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(SpectreAnimType::MOVE_UP);
                }
            }
        }
    }
}

// Run With: [spectreMoveSys, spectreVanishSys, spectreCastSys]
void spectreVanishSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsSpectreVanish, Orientation, const Spectre, const Speed, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreVanish, orientation, spectre, speed, enemyTransform]: enemies) {
        if (isSpectreVanish.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsSpectreVanish>(enemyEnt);
            world.add_components(enemyEnt, IsSpectreMove(spectre.moveDuration));
            world.add_components(enemyEnt, Collider(-12 / 2, -12 / 2, 12, 12));
            // instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, -1), 32.f);
            // instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(-1, +1), 32.f);
            // instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(+1, -1), 32.f);
            // instantiateFireBallParticle(world, enemyTransform.getPosition(), glm::vec2(+1, +1), 32.f);
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

// Run With: [spectreMoveSys, spectreVanishSys, spectreCastSys]
void spectreCastSys(ThreadedFixedSystem, World& world) {
    auto enemies = world.query<Velocity, Animation, IsSpectreCast, Orientation, const Speed, const Spectre, const Transform2D>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.query<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSpectreCast, orientation, speed, spectre, enemyTransform]: enemies) {
        if (isSpectreCast.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsSpectreCast>(enemyEnt);
            world.add_components(enemyEnt, IsSpectreMove(spectre.moveDuration));

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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(SpectreAnimType::ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(SpectreAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(SpectreAnimType::ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(SpectreAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(SpectreAnimType::ATTACK_UP);
                }
            }
        }
    }
}