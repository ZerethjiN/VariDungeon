#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void golemRockAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGolemRockAttack, Orientation, const Golem, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGolemRockAttack, orientation, golem, speed, enemyTransform, zindex]: enemies) {
        if (isGolemRockAttack.canSwitchState(time.fixedDelta())) {
            for (auto [_, playerTransform]: players) {
                if (glm::distance(enemyTransform.getPosition(), playerTransform.getPosition()) < 48.f) {
                    world.remove_components<IsGolemRockAttack>(enemyEnt);
                    world.add_components(enemyEnt, IsGolemFootAttack(golem.footDuration));

                    world.append_children(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, -24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, -24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+24, -24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, -8), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, +8), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+24, -8), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+24, +8), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-24, +24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-8, +24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(8, +24), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+24, +24), zindex)
                    });
                } else {
                    // isGolemRockAttack.resetStateTimer();
                    world.remove_components<IsGolemRockAttack>(enemyEnt);
                    world.add_components(enemyEnt, IsGolemPreLaserAttackCardinal(golem.preLaserDuration, 0));

                    for (int i = 1; i < 7; i++) {
                        world.append_children(enemyEnt, {
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex),
                            instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex),
                        });
                    }

                    world.append_children(enemyEnt, {
                        instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(8, 0), 0),
                        instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(0, -8), 90),
                        instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 0), 180),
                        instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(0, 8), 270),
                    });

                    for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                        for (int i = 0; i < golem.nbRocks; i++) {
                            auto rndX = rand() % 8;
                            auto rndY = rand() % 6;

                            if (intersect(enemyTransform.getPosition(), glm::vec4(-16, -16, 32, 32), glm::vec2(1, 1), roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f), glm::vec4(-8, -8, 16, 16), glm::vec2(1, 1))) {
                                continue;
                            }

                            instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 56.f), zindex);
                            instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 56.f), zindex);
                            instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 40.f), zindex);
                            instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 40.f), zindex);
                            instantiateGolemRock(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f));
                        }
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
                animation.play(GolemAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(GolemAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(GolemAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(GolemAnimType::MOVE_UP);
            }
        }
    }
}

void golemRockSys(MainFixedSystem, World& world) {
    auto rocks = world.view<GolemRock, const Transform2D>(with<Breakable>, without<Player>);

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [rockEnt, rock, transform]: rocks) {
        if (rock.canSpawn(time.fixedDelta())) {
            world.remove_components<GolemRock>(rockEnt);
            world.add_components(rockEnt,
                Sprite(textureManager, rockUV),
                Animation(rockAnim, RockAnimType::NO_HIT),
                Collider(-12 / 2, -12 / 2, 12, 12)
            );
            instantiateEnemyExplosionAttackParticle(world, transform.getPosition());
        }
    }
}

void golemPreFootAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<const OnCollisionEnter, const Golem, const Transform2D, const ZIndex>(with<IsGolemRockAttack>, without<IsGolemFootAttack>);

    for (auto [enemyEnt, collisions, golem, transform, zindex]: enemies) {
        for (auto othEnt: collisions) {
            if (world.has_components<Collider, GolemRock>(othEnt)) {
                world.remove_components<IsGolemRockAttack>(enemyEnt);
                world.add_components(enemyEnt, IsGolemFootAttack(golem.footDuration));

                world.append_children(enemyEnt, {
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-24, -24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-8, -24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(8, -24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(+24, -24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-24, -8), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-24, +8), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(+24, -8), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(+24, +8), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-24, +24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-8, +24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(8, +24), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(+24, +24), zindex)
                });

                return;
            }
        }
    }
}

void golemFootAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<IsGolemFootAttack, const Golem, const Transform2D, const ZIndex>();

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, isGolemFootAttack, golem, transform, zindex]: enemies) {
        if (isGolemFootAttack.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGolemFootAttack>(enemyEnt);
            world.add_components(enemyEnt, IsGolemPreLaserAttackCardinal(golem.preLaserDuration, 0));

            for (int i = 1; i < 7; i++) {
                world.append_children(enemyEnt, {
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, -16 * i), zindex),
                    instantiateFloorCrossParticle(world, transform.getPosition() + glm::vec2(0, 16 * i), zindex),
                });
            }
            world.append_children(enemyEnt, {
                instantiateShadowPortalParticle(world, transform.getPosition() + glm::vec2(8, 0), 0),
                instantiateShadowPortalParticle(world, transform.getPosition() + glm::vec2(0, -8), 90),
                instantiateShadowPortalParticle(world, transform.getPosition() + glm::vec2(-8, 0), 180),
                instantiateShadowPortalParticle(world, transform.getPosition() + glm::vec2(0, 8), 270),
            });

            for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                for (int i = 0; i < golem.nbRocks; i++) {
                    auto rndX = rand() % 8;
                    auto rndY = rand() % 6;

                    if (intersect(transform.getPosition(), glm::vec4(-16, -16, 32, 32), glm::vec2(1, 1), roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f), glm::vec4(-8, -8, 16, 16), glm::vec2(1, 1))) {
                        continue;
                    }

                    instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 56.f), zindex);
                    instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 56.f), zindex);
                    instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 40.f), zindex);
                    instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 40.f), zindex);
                    instantiateGolemRock(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f));
                }
            }

            world.add_components(
                instantiateEnemyBigExplosionAttackParticle(world, transform.getPosition()),
                EnemyWeaponForBreakables()
            );
        }
    }
}

void golemPreLaserAttackCardinalSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGolemPreLaserAttackCardinal, Orientation, const Golem, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGolemPreLaserAttackCardinal, orientation, golem, speed, enemyTransform, zindex]: enemies) {
        if (isGolemPreLaserAttackCardinal.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGolemPreLaserAttackCardinal>(enemyEnt);
            world.add_components(enemyEnt, IsGolemLaserAttackCardinal(golem.laserDuration, isGolemPreLaserAttackCardinal.curLasers));

            world.append_children(enemyEnt, {
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),   0, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),  90, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 180, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 270, golem.laserDuration, 0),
            });

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
                animation.play(GolemAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(GolemAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(GolemAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(GolemAnimType::MOVE_UP);
            }
        }
    }
}


void golemLaserAttackCardinalSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGolemLaserAttackCardinal, Orientation, const Golem, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGolemLaserAttackCardinal, orientation, golem, speed, enemyTransform, zindex]: enemies) {
        if (isGolemLaserAttackCardinal.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGolemLaserAttackCardinal>(enemyEnt);
            
            if (isGolemLaserAttackCardinal.curLasers < golem.nbLasers) {
                world.add_components(enemyEnt, IsGolemPreLaserAttackDiagonal(golem.preLaserDuration, isGolemLaserAttackCardinal.curLasers + 1));

                for (int i = 1; i < 7; i++) {
                    world.append_children(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 16 * i), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 16 * i), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, -16 * i), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, -16 * i), zindex),
                    });
                }
                world.append_children(enemyEnt, {
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(8, -8), -45),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(-8, -8), -135),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 8), -225),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(8, 8), -315),
                });
            } else {
                world.add_components(enemyEnt, IsGolemRockAttack(golem.rockDuration));

                for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                    for (int i = 0; i < golem.nbRocks; i++) {
                        auto rndX = rand() % 8;
                        auto rndY = rand() % 6;

                        if (intersect(enemyTransform.getPosition(), glm::vec4(-16, -16, 32, 32), glm::vec2(1, 1), roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f), glm::vec4(-8, -8, 16, 16), glm::vec2(1, 1))) {
                            continue;
                        }

                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 56.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 56.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 40.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 40.f), zindex);
                        instantiateGolemRock(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f));
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
                animation.play(GolemAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(GolemAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(GolemAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(GolemAnimType::MOVE_UP);
            }
        }
    }
}

void golemPreLaserAttackDiagonalSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGolemPreLaserAttackDiagonal, Orientation, const Golem, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGolemPreLaserAttackDiagonal, orientation, golem, speed, enemyTransform, zindex]: enemies) {
        if (isGolemPreLaserAttackDiagonal.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGolemPreLaserAttackDiagonal>(enemyEnt);
            world.add_components(enemyEnt, IsGolemLaserAttackDiagonal(golem.laserDuration, isGolemPreLaserAttackDiagonal.curLasers));

            world.append_children(enemyEnt, {
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(),  45, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 135, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 225, golem.laserDuration, 0),
                instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 315, golem.laserDuration, 0),
            });

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
                animation.play(GolemAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(GolemAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(GolemAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(GolemAnimType::MOVE_UP);
            }
        }
    }
}


void golemLaserAttackDiagonalSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsGolemLaserAttackDiagonal, Orientation, const Golem, const Speed, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isGolemLaserAttackDiagonal, orientation, golem, speed, enemyTransform, zindex]: enemies) {
        if (isGolemLaserAttackDiagonal.canSwitchState(time.fixedDelta())) {
            world.remove_components<IsGolemLaserAttackDiagonal>(enemyEnt);
            
            if (isGolemLaserAttackDiagonal.curLasers < golem.nbLasers) {
                world.add_components(enemyEnt, IsGolemPreLaserAttackCardinal(golem.preLaserDuration, isGolemLaserAttackDiagonal.curLasers + 1));

                for (int i = 1; i < 7; i++) {
                    world.append_children(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * i, 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * i, 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16 * i), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16 * i), zindex),
                    });
                }
                world.append_children(enemyEnt, {
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(8, 0), 0),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(0, -8), 90),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(-8, 0), 180),
                    instantiateShadowPortalParticle(world, enemyTransform.getPosition() + glm::vec2(0, 8), 270),
                });
            } else {
                world.add_components(enemyEnt, IsGolemRockAttack(golem.rockDuration));

                for (auto [_, roomTransform]: world.view<const Transform2D>(with<ChunkInfos>)) {
                    for (int i = 0; i < golem.nbRocks; i++) {
                        auto rndX = rand() % 8;
                        auto rndY = rand() % 6;

                        if (intersect(enemyTransform.getPosition(), glm::vec4(-16, -16, 32, 32), glm::vec2(1, 1), roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f), glm::vec4(-8, -8, 16, 16), glm::vec2(1, 1))) {
                            continue;
                        }

                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 56.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 56.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 72.f, rndY * 16.f - 40.f), zindex);
                        instantiateFloorCrossParticle(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 56.f, rndY * 16.f - 40.f), zindex);
                        instantiateGolemRock(world, roomTransform.getPosition() + glm::vec2(rndX * 16.f - 64.f, rndY * 16.f - 48.f));
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
                animation.play(GolemAnimType::MOVE_RIGHT);
            } else {
                orientation = Orientation::WEST;
                animation.play(GolemAnimType::MOVE_LEFT);
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                animation.play(GolemAnimType::MOVE_DOWN);
            } else {
                orientation = Orientation::NORTH;
                animation.play(GolemAnimType::MOVE_UP);
            }
        }
    }
}