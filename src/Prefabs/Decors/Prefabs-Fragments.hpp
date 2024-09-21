#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateFragments(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, rockUV, 1),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-10)
    );
}