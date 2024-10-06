#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowPortalParticle(World& world, const glm::vec2& position, float rotation) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, shadowPortalParticleUV),
        Transform2D(
            position,
            rotation,
            glm::vec2(1, 1)
        ),
        LifeTime(0.75f),
        ZIndex(5)
    );
}