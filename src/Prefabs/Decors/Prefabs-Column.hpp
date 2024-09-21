#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateColumn(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, columnUV, 0),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}

Ent instantiateColumnBanner(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, columnUV, 1),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}