#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSarcophageClose(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(sarcophageUV, 0),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 16)
    );
}

Ent instantiateSarcophageOpen(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(sarcophageUV, 1),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Collider(-32 / 2, -16 / 2, 32, 16)
    );
}