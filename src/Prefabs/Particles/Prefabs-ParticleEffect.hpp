#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectFire(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, particleEffectUV),
        Animation(particleEffectAnim, ParticleEffectAnimType::FIRE_PARTICLE),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectStun(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, particleEffectUV),
        Animation(particleEffectAnim, ParticleEffectAnimType::STUN_PARTICLE),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectFrost(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, particleEffectUV),
        Animation(particleEffectAnim, ParticleEffectAnimType::FROST_PARTICLE),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectStar(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        Sprite(textureManager, particleEffectUV),
        Animation(particleEffectAnim, ParticleEffectAnimType::STAR_PARTICLE),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}