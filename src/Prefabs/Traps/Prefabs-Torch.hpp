#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateTorch(World& world, const glm::vec2& position) {
    return world.newEnt(
        Torch(1.5f, 0.75f),
        IsTorchIdle(1.5f),
        SpriteCreator(torchUV),
        Animation(torchAnim, "On"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Orientation(Orientation::SOUTH),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}