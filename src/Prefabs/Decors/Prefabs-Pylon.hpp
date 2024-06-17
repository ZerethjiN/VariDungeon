#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectStar(World&, const glm::vec2&);

Ent instantiatePylon(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(pylonUV),
        Animation(pylonAnim, "Default"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ParticleGenerator(instantiateParticleEffectStar, 1.f, 12.f),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}