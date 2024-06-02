#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateAttractParticle(World& world, const glm::vec2& position, std::size_t newZIndex, float newLifeTime) {
    return world.newEnt(
        SpriteCreator(attractParticleUV),
        Animation(attractParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(newZIndex),
        LifeTime(newLifeTime)
    );
}