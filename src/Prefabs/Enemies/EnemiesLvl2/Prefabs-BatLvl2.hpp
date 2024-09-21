#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBatLvl2(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        BatLvl2(
            /*MoveDuration:*/ 1.0f,
            /*AttackDuration:*/ 0.75f,
            /*AttackRadius:*/ 32.f
        ),
        IsBatLvl2Move(1.0f),
        EnemyWeapon(),
        Damage(1),
        Sprite(textureManager, batLvl2UV),
        Animation(batLvl2Anim, BatLvl2AnimType::MOVE_DOWN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 2, 3}}),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(24),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}