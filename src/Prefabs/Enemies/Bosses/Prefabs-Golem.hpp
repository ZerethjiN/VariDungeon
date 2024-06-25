#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGolem(World& world, const glm::vec2& position) {
    return world.newEnt(
        Boss(),
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Golem(
            /*PreLaserDuration:*/ 0.75f,
            /*LaserDuration:*/ 2.0f,
            /*NbLasers:*/ 4,
            /*RockDuration:*/ 3.0f,
            /*NbRocks:*/ 7,
            /*FootDuration:*/ 0.75f
        ),
        IsGolemRockAttack(3.0f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(golemUV),
        Animation(golemAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_XP, 4, 6}}),
        ZIndex(0),
        Life(30),
        Velocity(),
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-24 / 2, -24 / 2, 24, 24)
    );
}

Ent instantiateGolemRock(World& world, const glm::vec2& position) {
    return world.newEnt(
        GolemRock(0.75f),
        Breakable("NoHit", "Hit", "Destroyed"),
        Life(1),
        // SpriteCreator(rockUV),
        // Animation(rockAnim, "NoHit"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots(),
        ZIndex(0),
        LifeTime(6.0)
        // Collider(-12 / 2, -12 / 2, 12, 12)
    );
}