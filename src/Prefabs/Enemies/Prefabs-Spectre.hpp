#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSpectre(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Spectre(
            /*MoveDuration:*/ 1.5f,
            /*VanishDuration:*/ 2.0f,
            /*CastDuration:*/ 1.0f
        ),
        IsSpectreMove(1.5f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(spectreUV),
        Animation(spectreAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}