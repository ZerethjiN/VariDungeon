#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSphere(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(sphereUV),
        Animation(sphereAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -48 / 2, 32, 48)
    );
}