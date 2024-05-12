#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateDustParticle(World& world, const glm::vec2& position, int baseZIndex) {
    return world.newEnt(
        SpriteCreator(dustParticleUV),
        Animation(dustParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex + 1),
        LifeTime(0.2f)
    );
}