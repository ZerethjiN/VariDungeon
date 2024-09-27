#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void miniRockSpawnerSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Animation, MiniRockSpawner, const Transform2D>(without<EnemyPreSpawn>);

    auto [time] = world.resource<const Time>();

    for (auto [enemyEnt, animation, miniRockSpawner, enemyTransform]: enemies) {
        if (miniRockSpawner.canSpawn(time.fixedDelta())) {
            for (int i = 0; i < miniRockSpawner.nbMiniRock; i++) {
                instantiateMiniRock(world, enemyTransform.getPosition());
            }
        }

        if (world.has_components<InvincibleFrame>(enemyEnt)) {
            animation.play(MiniRockAnimType::HIT_SPAWNER);
        } else {
            animation.play(MiniRockAnimType::SPAWNER);
        }
    }
}

void miniRockMoveSys(MainFixedSystem, World& world) {
    auto enemies = world.view<Velocity, Animation, Orientation, const Speed, const Transform2D, const ZIndex>(with<MiniRock>, without<Unmoveable, EnemyPreSpawn>);
    auto players = world.view<const Transform2D>(with<Player>);

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
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MiniRockAnimType::HIT_MOVE_RIGHT);
                } else {
                    animation.play(MiniRockAnimType::MOVE_RIGHT);
                }
            } else {
                orientation = Orientation::WEST;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MiniRockAnimType::HIT_MOVE_LEFT);
                } else {
                    animation.play(MiniRockAnimType::MOVE_LEFT);
                }
            }
        } else {
            if (newdirection.y > 0) {
                orientation = Orientation::SOUTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MiniRockAnimType::HIT_MOVE_DOWN);
                } else {
                    animation.play(MiniRockAnimType::MOVE_DOWN);
                }
            } else {
                orientation = Orientation::NORTH;
                if (world.has_components<InvincibleFrame>(enemyEnt)) {
                    animation.play(MiniRockAnimType::HIT_MOVE_UP);
                } else {
                    animation.play(MiniRockAnimType::MOVE_UP);
                }
            }
        }
    }
}