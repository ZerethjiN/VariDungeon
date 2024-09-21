#pragma once

#include <Zerengine.hpp>

static const ImageAsset explosionParticleUV("Textures/ExplosionParticle.png", {
    {{  0,   0, 48, 48}, {0.5f, 0.5f}}, //  0: Small Explosion Particle A
    {{ 48,   0, 48, 48}, {0.5f, 0.5f}}, //  1: Small Explosion Particle B

    {{  0,  48, 64, 64}, {0.5f, 0.5f}}, //  2: Big Explosion Particle A
    {{ 64,  48, 64, 64}, {0.5f, 0.5f}}, //  3: Big Explosion Particle B
});

enum class ExplosionParticleAnimType: std::size_t {
    SMALL_EXPLOSION,
    BIG_EXPLOSION,
};

static const AnimationAsset explosionParticleAnim(animEnum<ExplosionParticleAnimType>, {
    {ExplosionParticleAnimType::SMALL_EXPLOSION, {{
        {0.15f, explosionParticleUV[0]},
        {0.15f, explosionParticleUV[1]},
    }}},
    {ExplosionParticleAnimType::BIG_EXPLOSION, {{
        {0.15f, explosionParticleUV[2]},
        {0.15f, explosionParticleUV[3]},
    }}},
});