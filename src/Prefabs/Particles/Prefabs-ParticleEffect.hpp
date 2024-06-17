#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateParticleEffectFire(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(particleEffectUV),
        Animation(particleEffectAnim, "FireParticle"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectStun(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(particleEffectUV),
        Animation(particleEffectAnim, "StunParticle"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectFrost(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(particleEffectUV),
        Animation(particleEffectAnim, "FrostParticle"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}

Ent instantiateParticleEffectStar(World& world, const glm::vec2& position) {
    return world.newEnt(
        SpriteCreator(particleEffectUV),
        Animation(particleEffectAnim, "StarParticle"),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(99),
        LifeTime(0.3f)
    );
}