#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSlime(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Slime(0.5f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(slimeUV),
        Animation(slimeAnim, "MoveDown"),
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
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}