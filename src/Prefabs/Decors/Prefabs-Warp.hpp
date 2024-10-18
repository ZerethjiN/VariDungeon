#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateWarp(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Warp(),
        WarpOpening(warpAnim[WarpAnimType::OPEN].getTotalDuration()),
        Sprite(textureManager, warpUV),
        Animation(warpAnim, WarpAnimType::OPEN),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        // Trigger(-16 / 2, -16 / 2, 16, 16),
        ZIndex(-5)
    );
}