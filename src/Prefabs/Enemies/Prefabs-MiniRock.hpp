#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMiniRockSpawner(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        MiniRockSpawner(4.0f, 2),
        SpriteCreator(miniRockUV),
        Animation(miniRockAnim, "Spawner"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(2),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );
}

Ent instantiateMiniRock(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        MiniRock(),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(miniRockUV),
        Animation(miniRockAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );
}