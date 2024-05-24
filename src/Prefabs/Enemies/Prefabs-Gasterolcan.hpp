#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateGasterolcan(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Gasterolcan(1.0f, 0.75f, 1.0f, 4.f),
        IsGasterolcanMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(gasterolcanUV),
        Animation(gasterolcanAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(5),
        Velocity(),
        Speed(12),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}