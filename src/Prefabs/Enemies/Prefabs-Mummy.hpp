#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMummy(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        Mummy(1.0f, 0.75f, 0.5f),
        IsMummyMove(1.0f),
        EnemyWeapon(),
        Damage(1),
        SpriteCreator(mummyUV),
        Animation(mummyAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Life(3),
        Velocity(),
        Speed(32),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}