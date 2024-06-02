#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void miniRockSpawnerSys(World& world) {
    auto enemies = world.view<Animation, MiniRockSpawner, const Transform>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, miniRockSpawner, enemyTransform]: enemies) {
        if (miniRockSpawner.canSpawn(time.fixedDelta())) {
            for (int i = 0; i < miniRockSpawner.nbMiniRock; i++) {
                instantiateMiniRock(world, enemyTransform.getPosition());
            }
        }

        if (world.has<InvincibleFrame>(enemyEnt)) {
            animation.play("HitSpawner");
        } else {
            animation.play("Spawner");
        }
    }
}

void miniRockMoveSys(World& world) {
    auto enemies = world.view<Velocity, Animation, Orientation, const Speed, const Transform, const ZIndex>(with<MiniRock>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform>(with<Player>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, velocity, animation, orientation, speed, enemyTransform, zindex]: enemies) {
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