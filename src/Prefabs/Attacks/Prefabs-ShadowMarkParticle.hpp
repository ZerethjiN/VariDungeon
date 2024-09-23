#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowMarkParticle(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.create_entity(
        EnemyWeapon(),
        Damage(1),
        ShadowMark(
            /*PreExplosionDuration:*/ 1.0f,
            /*ExplosionDuration:*/ 0.5f
        ),
        IsShadowMarkPreExplosion(1.0f),
        Sprite(textureManager, shadowMarkParticleUV),
        Animation(shadowMarkParticleAnim, ShadowMarkParticleAnimType::PRE_EXPLOSION),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-10)
    );
}