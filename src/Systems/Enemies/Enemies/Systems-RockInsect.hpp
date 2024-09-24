#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rockInsectMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsRockInsectMove, Orientation, const Speed, const RockInsect, const Transform2D, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRockInsectMove, orientation, speed, rockInsect, enemyTransform, zindex]: enemies) {
        if (isRockInsectMove.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsRockInsectMove>(enemyEnt);
            world.add_component(enemyEnt, IsRockInsectPreCast(rockInsect.preCastDuration));

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
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(RockInsectAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(RockInsectAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(RockInsectAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(RockInsectAnimType::MOVE_UP);
                }
            }
        }
    }
}

void rockInsectPreCastSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsRockInsectPreCast, Orientation, const RockInsect, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockInsectPreCast, orientation, rockInsect, enemyTransform]: enemies) {
        if (isRockInsectPreCast.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsRockInsectPreCast>(enemyEnt);
            world.add_component(enemyEnt, IsRockInsectCast(rockInsect.castDuration));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.append_children(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 0, 0.75f, 0)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 180, 0.75f, 0)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.append_children(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 90, 0.75f, 0)
                    });
                } else {
                    world.append_children(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 270, 0.75f, 0)
                    });
                }
            }

            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_UP);
                }
            }
        }
    }
}

void rockInsectCastSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsRockInsectCast, Orientation, const RockInsect, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockInsectCast, orientation, rockInsect, enemyTransform]: enemies) {
        if (isRockInsectCast.canSwitchState(time.fixedDelta())) {
            world.remove_component<IsRockInsectCast>(enemyEnt);
            world.add_component(enemyEnt, IsRockInsectMove(rockInsect.moveDuration));
            continue;
        }

        if (fabs(orientation.x) > fabs(orientation.y)) {
            if (orientation.x > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_RIGHT);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_RIGHT);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_LEFT);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_LEFT);
                }
            }
        } else {
            if (orientation.y > 0) {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_DOWN);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_DOWN);
                }
            } else {
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RockInsectAnimType::HIT_ATTACK_UP);
                } else {
                    animation.play(RockInsectAnimType::ATTACK_UP);
                }
            }
        }
    }
}