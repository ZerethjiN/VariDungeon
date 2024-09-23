#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectFire(World&, const glm::vec2&);

Ent instantiateCandlestick(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, candlestickUV),
        Animation(candlestickAnim, CandlestickAnimType::DEFAULT),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ParticleGenerator(instantiateParticleEffectFire, 1.0f, 8.f, glm::vec2(0, -8)),
        Collider(-16 / 2, -32 / 2, 16, 32)
    );
}