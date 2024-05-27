#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateSkullBossRoom(World& world, const glm::vec2& position, float rotation) {
    return world.newEnt(
        SpriteCreator(skullBossRoomUV),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        )
    );
}