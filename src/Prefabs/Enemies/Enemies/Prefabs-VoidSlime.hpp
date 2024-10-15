#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateVoidSlime(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        VoidSlime(1.5f, 1.5f, 20.f, 32.f),
        IsVoidSlimeMove(1.5f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, voidSlimeUV),
        Animation(voidSlimeAnim, VoidSlimeAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 2, 3}}),
        ZIndex(0),
        Life(3),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}