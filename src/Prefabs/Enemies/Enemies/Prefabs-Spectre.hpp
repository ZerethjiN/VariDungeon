#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSpectre(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
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
        Sprite(textureManager, spectreUV),
        Animation(spectreAnim, SpectreAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 2, 3}}),
        ZIndex(0),
        Life(3),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}