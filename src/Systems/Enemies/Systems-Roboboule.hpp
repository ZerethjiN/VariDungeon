#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void robobouleMoveSys(World& world) {
    auto enemies = world.view<Velocity, Animation, Orientation, const Speed, const Roboboule, const Transform, const ZIndex>(with<IsRobobouleMove>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, orientation, speed, roboboule, enemyTransform, zindex]: enemies) {
        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());

            if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) < roboboule.getPreAttackRadius()) {
                world.del<IsRobobouleMove>(enemyEnt);
                world.add(enemyEnt, IsRoboboulePreAttack(roboboule.getPreAttackDuration()));

                // world.appendChildren(enemyEnt, {
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, -16), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 0), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(-16, 16), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, -16), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(0, 16), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, -16), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 0), zindex),
                //     instantiateFloorCrossParticle(world, enemyTransform.getPosition() + glm::vec2(16, 16), zindex),
                // });

                continue;
            }
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

void roboboulePreAttackSys(World& world) {
    auto enemies = world.view<Velocity, Animation, IsRoboboulePreAttack, Orientation, const Speed, const Roboboule, const Transform>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isRoboboulePreAttack, orientation, speed, roboboule, enemyTransform]: enemies) {
        if (isRoboboulePreAttack.canSwitchState(time.fixedDelta())) {
            world.destroy(enemyEnt);
            instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition());
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());

            if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) >= roboboule.getPreAttackRadius()) {
                world.del<IsRoboboulePreAttack>(enemyEnt);
                world.add(enemyEnt, IsRobobouleMove());
                continue;
            }
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackRight");
                } else {
                    animation.play("PreAttackRight");
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackLeft");
                } else {
                    animation.play("PreAttackLeft");
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackDown");
                } else {
                    animation.play("PreAttackDown");
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play("HitPreAttackUp");
                } else {
                    animation.play("PreAttackUp");
                }
            }
        }
    }
}