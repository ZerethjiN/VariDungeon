#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSarcophageClose(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, sarcophageDecorUV, 0),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 16)
    );
}

Ent instantiateSarcophageOpen(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, sarcophageDecorUV, 1),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 16)
    );
}