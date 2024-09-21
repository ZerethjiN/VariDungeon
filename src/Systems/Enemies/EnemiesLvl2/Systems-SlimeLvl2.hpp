#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void slimeLvl2MoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSlimeLvl2Move, Orientation, SlimeLvl2, const Speed, const Transform2D>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSlimeLvl2Move, orientation, slime, speed, enemyTransform]: enemies) {
        if (isSlimeLvl2Move.canSwitchState(time.fixedDelta())) {
            world.remove<IsSlimeLvl2Move>(enemyEnt);
            world.add(enemyEnt, IsSlimeLvl2Jump(slime.jumpDuration));
            animation.play(SlimeLvl2AnimType::SHADOW);

            if (auto opt = world.get<const Collider>(enemyEnt)) {
                auto [collider] = opt.value();
                slime.tmpCollider = collider.col;
                world.remove<Collider>(enemyEnt);
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
                    animation.play(SlimeLvl2AnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(SlimeLvl2AnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(SlimeLvl2AnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(SlimeLvl2AnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(SlimeLvl2AnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(SlimeLvl2AnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has<InvincibleFrame>(enemyEnt)) {
                    animation.play(SlimeLvl2AnimType::HIT_MOVE_UP);
                } else {
                    animation.play(SlimeLvl2AnimType::MOVE_UP);
                }
            }
        }
    }
}

void slimeLvl2JumpSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, IsSlimeLvl2Jump, Orientation, const Speed, const Transform2D, const SlimeLvl2>(without<EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, isSlimeLvl2Jump, orientation, speed, enemyTransform, slime]: enemies) {
        if (isSlimeLvl2Jump.canSwitchState(time.fixedDelta())) {
            world.remove<IsSlimeLvl2Jump>(enemyEnt);
            world.add(enemyEnt, IsSlimeLvl2Move(slime.moveDuration));

            if (!world.has<Collider>(enemyEnt)) {
                world.add(enemyEnt, Collider(slime.tmpCollider));
            }

            instantiateEnemyExplosionAttackParticle(world, enemyTransform.getPosition());
        }

        glm::vec2 newdirection;
        for (auto [_, playerTransform]: players) {
            newdirection = glm::normalize(playerTransform.getPosition() - enemyTransform.getPosition());
        }

        velocity += newdirection * speed.speed * slime.jumpSpeedCoeff * time.fixedDelta();
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