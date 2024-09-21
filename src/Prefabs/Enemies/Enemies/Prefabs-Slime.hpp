#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSlime(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Slime(0.5f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, slimeUV),
        Animation(slimeAnim, SlimeAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 2, 3}}),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}