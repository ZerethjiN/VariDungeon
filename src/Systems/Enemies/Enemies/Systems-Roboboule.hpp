#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void robobouleMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, Orientation, const Speed, const Roboboule, const Transform2D, const ZIndex>(with<IsRobobouleMove>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, orientation, speed, roboboule, enemyTransform, zindex]: enemies) {
        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());

            if (glm::distance(playerTransform.getPosition(), enemyTransform.getPosition()) < roboboule.getPreAttackRadius()) {
                world.remove<IsRobobouleMove>(enemyEnt);
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
                    animation.play(RobobouleAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(RobobouleAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(RobobouleAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(RobobouleAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(RobobouleAnimType::MOVE_UP);
                }
            }
        }
    }
}

void roboboulePreAttackSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsRoboboulePreAttack, Orientation, const Speed, const Roboboule, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

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
                world.remove<IsRoboboulePreAttack>(enemyEnt);
                world.add(enemyEnt, IsRobobouleMove());
                continue;
            }
        }

        velocity += newdirection * speed.speed * time.fixedDelta();
        if (fabs(newdirection.x) > fabs(newdirection.y)) {
            if (newdirection.x > 0) {
                orientation = Orientation::EAST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_PRE_ATTACK_RIGHT);
                } else {
                    animation.play(RobobouleAnimType::PRE_ATTACK_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_PRE_ATTACK_LEFT);
                } else {
                    animation.play(RobobouleAnimType::PRE_ATTACK_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_PRE_ATTACK_DOWN);
                } else {
                    animation.play(RobobouleAnimType::PRE_ATTACK_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(RobobouleAnimType::HIT_PRE_ATTACK_UP);
                } else {
                    animation.play(RobobouleAnimType::PRE_ATTACK_UP);
                }
            }
        }
    }
}