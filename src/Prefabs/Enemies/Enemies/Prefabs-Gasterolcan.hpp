#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGasterolcan(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Gasterolcan(1.0f, 0.75f, 1.0f, 4.f),
        IsGasterolcanMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, gasterolcanUV),
        Animation(gasterolcanAnim, GasterolcanAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 2, 3}}),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(12),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}