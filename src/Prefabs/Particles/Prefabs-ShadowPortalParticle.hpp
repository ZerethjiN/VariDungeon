#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowPortalParticle(World& world, const glm::vec2& position, float rotation) {
    return world.newEnt(
        SpriteCreator(shadowPortalParticleUV),
        Transform(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(0.75f)
    );
}