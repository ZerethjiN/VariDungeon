#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateAnubis(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        Anubis(1.5f, 0.75f),
        IsAnubisMove(1.5f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(anubisUV),
        Animation(anubisAnim, "MoveDown"),
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