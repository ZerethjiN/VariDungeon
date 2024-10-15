#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMummy(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Mummy(
            /*MoveDuration:*/ 1.0f,
            /*PreAttackDuration:*/ 0.75f,
            /*AttackDuration:*/ 0.5f,
            /*AttackRadius:*/ 32.f
        ),
        IsMummyMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, mummyUV),
        Animation(mummyAnim, MummyAnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LootType::XP, 2, 3}}),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(24),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}