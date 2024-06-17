#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateRock(World& world, const glm::vec2& position) {
    return world.newEnt(
        Breakable("NoHit", "Hit", "Destroyed"),
        Life(1),
        SpriteCreator(rockUV),
        Animation(rockAnim, "NoHit"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        Loots({{LOOT_TYPE_COIN, 2, 3}}),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}