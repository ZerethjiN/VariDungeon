#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRoboboule(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Roboboule(0.75f, 32.f),
        IsRobobouleMove(),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, robobouleUV),
        Animation(robobouleAnim, RobobouleAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 2, 3}}),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(24),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}