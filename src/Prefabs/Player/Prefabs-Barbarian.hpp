#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateBarbarian(World& world, const glm::vec2& position) {
    return world.newEnt(
        Player(),
        Barbarian(),
        SpriteCreator(barbareUV),
        Animation(barbareAnim, "MoveDown"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Velocity(),
        Speed(64),
        Orientation(Orientation::SOUTH),
        Collider(-8 / 2, -8 / 2, 8, 8)
    );
}