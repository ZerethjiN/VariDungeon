#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateKing(World& world, const glm::vec2& position) {
    return world.newEnt(
        King(),
        SpriteCreator(kingUV),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -16 / 2, 16, 16)
    );
}