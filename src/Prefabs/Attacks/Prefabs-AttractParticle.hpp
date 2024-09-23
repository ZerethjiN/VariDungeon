#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateAttractParticle(World& world, const glm::vec2& position, std::size_t newZIndex, float newLifeTime) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, attractParticleUV),
        Animation(attractParticleAnim, AttractParticleAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(newZIndex),
        LifeTime(newLifeTime)
    );
}