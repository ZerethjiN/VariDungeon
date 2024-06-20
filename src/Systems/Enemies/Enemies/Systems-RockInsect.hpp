#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void rockInsectMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsRockInsectMove, Orientation, const Speed, const RockInsect, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRockInsectMove, orientation, speed, rockInsect, enemyTransform, zindex]: enemies) {
        if (isRockInsectMove.canSwitchState(time.fixedDelta())) {
            world.remove<IsRockInsectMove>(enemyEnt);
            world.add(enemyEnt, IsRockInsectPreCast(rockInsect.preCastDuration));

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

void rockInsectPreCastSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsRockInsectPreCast, Orientation, const RockInsect, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockInsectPreCast, orientation, rockInsect, enemyTransform]: enemies) {
        if (isRockInsectPreCast.canSwitchState(time.fixedDelta())) {
            world.remove<IsRockInsectPreCast>(enemyEnt);
            world.add(enemyEnt, IsRockInsectCast(rockInsect.castDuration));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 0)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 180)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 90)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateMegaLaserParticle(world, enemyTransform.getPosition(), 270)
                    });
                }
            }

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

void rockInsectCastSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsRockInsectCast, Orientation, const RockInsect, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isRockInsectCast, orientation, rockInsect, enemyTransform]: enemies) {
        if (isRockInsectCast.canSwitchState(time.fixedDelta())) {
            world.remove<IsRockInsectCast>(enemyEnt);
            world.add(enemyEnt, IsRockInsectMove(rockInsect.moveDuration));
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