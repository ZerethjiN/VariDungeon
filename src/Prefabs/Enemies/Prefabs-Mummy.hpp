#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMummy(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        // Anubis(1.5f, 1.0f),
        // IsAnubisMove(1.5f),
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
        Speed(16),
        Orientation(Orientation::SOUTH),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}