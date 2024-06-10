#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRockInsect(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        RockInsect(
            /*MoveDuration:*/ 1.5f,
            /*PreCastDuration:*/ 0.75f,
            /*CastDuration:*/ 0.75f
        ),
        IsRockInsectMove(1.5f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(rockInsectUV),
        Animation(rockInsectAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(3),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}