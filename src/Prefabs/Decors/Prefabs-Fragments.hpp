#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateFragments(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(rockUV, 1),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-10)
    );
}