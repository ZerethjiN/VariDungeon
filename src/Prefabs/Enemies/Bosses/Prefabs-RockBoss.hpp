#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRockBoss(World& world, const glm::vec2& position) {
    return world.newEnt(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        RockBoss(
            /*StunDuration:*/ 1.5f,
            /*SmallCrystalDuration:*/ 4.0f,
            /*GroundCrystalDuration:*/ 2.5f,
            /*RollSpeedCoeff:*/ 8.0f
        ),
        IsRockBossRoll(),
        Unhittable(),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(rockBossUV),
        Animation(rockBossAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(15),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}