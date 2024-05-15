#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBat(World& world, const glm::vec2& position) {
    return world.newEnt(
        Enemy(),
        Bat(
            /*MoveDuration:*/ 1.0f,
            /*AttackDuration:*/ 1.0f
        ),
        IsBatMove(1.0f),
        SpriteCreator(batUV),
        Animation(batAnim, "MoveDown"),
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