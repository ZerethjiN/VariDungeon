#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateFloorCrossParticle(World& world, const glm::vec2& position, int baseZIndex) {
    return world.newEnt(
        SpriteCreator(floorCrossParticleUV),
        Animation(floorCrossParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex - 1),
        LifeTime(0.75f)
    );
}