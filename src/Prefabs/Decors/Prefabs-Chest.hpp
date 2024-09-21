#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateChest(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Chest(),
        Sprite(textureManager, chestUV),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}