#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateInsect(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Insect(
            /*MoveDuration:*/ 1.5f,
            /*DirectionCooldown:*/ 0.5f,
            /*AttackDuration:*/ 2.5f,
            /*AttackSpeedCoeff:*/ 2.f
        ),
        IsInsectMove(1.5f),
        IsInsectChangeDirection(0.5f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, insectUV),
        Animation(insectAnim, InsectAnimType::MOVE_DOWN),
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