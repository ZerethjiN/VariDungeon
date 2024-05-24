#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateWarp(World& world, const glm::vec2& position) {
    return world.newEnt(
        Warp(),
        SpriteCreator(warpUV),
        Animation(warpAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Trigger(-24 / 2, -24 / 2, 24, 24),
        ZIndex(-5)
    );
}