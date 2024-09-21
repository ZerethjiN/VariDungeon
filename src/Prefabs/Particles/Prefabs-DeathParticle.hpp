#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateDeathParticle(World& world, const glm::vec2& position, int baseZIndex) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.newEnt(
        Sprite(textureManager, deathParticleUV),
        Animation(deathParticleAnim, DeathParticleAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(baseZIndex + 15),
        LifeTime(deathParticleAnim[DeathParticleAnimType::DEFAULT].getTotalDuration())
    );
}