#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiatePopHitParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(popHitParticleUV),
        Animation(popHitParticleAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        LifeTime(0.2f)
    );
}