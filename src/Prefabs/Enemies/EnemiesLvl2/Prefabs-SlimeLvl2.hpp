#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSlimeLvl2(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        SlimeLvl2(
            /*MoveDuration:*/ 1.5f,
            /*JumpDuration:*/ 1.0f,
            /*JumpSpeedCoeff*/ 2.f
        ),
        IsSlimeLvl2Move(1.0f),
        EnemyWeapon(),
        Damage(2),
        Sprite(textureManager, slimeLvl2UV),
        Animation(slimeLvl2Anim, SlimeLvl2AnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 2, 3}}),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(24),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}