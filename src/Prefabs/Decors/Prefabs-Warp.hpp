#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateWarp(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Warp(),
        Sprite(textureManager, warpUV),
        Animation(warpAnim, WarpAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Trigger(-24 / 2, -24 / 2, 24, 24),
        ZIndex(-5)
    );
}