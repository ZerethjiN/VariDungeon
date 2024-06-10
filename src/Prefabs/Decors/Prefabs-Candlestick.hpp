#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateCandlestick(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(candlestickUV),
        Animation(candlestickAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}