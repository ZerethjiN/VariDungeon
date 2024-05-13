#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateJar(World& world, const glm::vec2& position) {
    return world.newEnt(
        Breakable("NoHit", "Hit"),
        Life(1),
        SpriteCreator(jarUV),
        Animation(jarAnim, "NoHit"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0),
        Collider(-12 / 2, -12 / 2, 12, 12)
    );
}