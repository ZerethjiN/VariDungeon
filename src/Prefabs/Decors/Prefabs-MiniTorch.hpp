#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMiniTorch(World& world, const glm::vec2& position, float rotation) {
    return world.newEnt(
        SpriteCreator(miniTorchUV),
        Animation(miniTorchAnim, "Default"),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        )
    );
}