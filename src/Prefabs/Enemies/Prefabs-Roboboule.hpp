#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRoboboule(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        EnemyPreSpawn(0.5f, 2),
        Roboboule(0.75f, 32.f),
        IsRobobouleMove(),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(robobouleUV),
        Animation(robobouleAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(2),
        Velocity(),
        Speed(32),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}