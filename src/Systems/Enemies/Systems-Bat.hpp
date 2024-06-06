#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void batMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsBatMove, Orientation, const Speed, const Bat, const Transform, const ZIndex>(without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isBatMove, orientation, speed, bat, enemyTransform, zindex]: enemies) {
        if (isBatMove.canSwitchState(time.fixedDelta())) {
            world.del<IsBatMove>(enemyEnt);
            world.add(enemyEnt, IsBatAttack(bat.getAttackDuration()));

            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 0, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 0,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 0, -16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16 * 1, -16), zindex)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 0, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 0,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 0, -16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1, +16), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1,   0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16 * 1, -16), zindex)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, 16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, 16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, 16 * 1), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, 16 * 1), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16 * 1), zindex)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, -16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, -16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16 * 0), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(+16, -16 * 1), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(  0, -16 * 1), zindex),
                        instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16 * 1), zindex)
                    });
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

void batAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, IsBatAttack, Orientation, const Bat, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, isBatAttack, orientation, bat, enemyTransform]: enemies) {
        if (isBatAttack.canSwitchState(time.fixedDelta())) {
            world.del<IsBatAttack>(enemyEnt);
            world.add(enemyEnt, IsBatMove(bat.getMoveDuration()));
            if (fabs(orientation.x) > fabs(orientation.y)) {
                if (orientation.x > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 90)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 270)
                    });
                }
            } else {
                if (orientation.y > 0) {
                    world.appendChildren(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 180)
                    });
                } else {
                    world.appendChildren(enemyEnt, {
                        instantiateBatAttackParticle(world, enemyTransform.getPosition(), 0)
                    });
                }
            }
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