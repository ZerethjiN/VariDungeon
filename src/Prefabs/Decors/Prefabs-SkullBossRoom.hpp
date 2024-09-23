#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSkullBossRoom(World& world, const glm::vec2& position, float rotation) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, skullBossRoomUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        )
    );
}