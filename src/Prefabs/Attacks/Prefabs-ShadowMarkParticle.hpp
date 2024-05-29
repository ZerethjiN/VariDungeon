#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateShadowMarkParticle(World& world, const glm::vec2& position) {
    return world.newEnt(
        EnemyWeapon(),
        Damage(1),
        ShadowMark(
            /*PreExplosionDuration:*/ 1.0f,
            /*ExplosionDuration:*/ 0.5f
        ),
        IsShadowMarkPreExplosion(1.0f),
        SpriteCreator(shadowMarkParticleUV),
        Animation(shadowMarkParticleAnim, "PreExplosion"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(-10)
    );
}