#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateAnubisLvl2(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        AnubisLvl2(
            /*AttackDuration:*/ 1.0f,
            /*VanishDuration:*/ 2.0f
        ),
        IsAnubisLvl2Attack(1.0f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(anubisLvl2UV),
        Animation(anubisLvl2Anim, "AttackDown"),
        Transform(
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