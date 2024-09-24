#pragma once

#include <Zerengine.hpp>

static const ImageAsset shadowMarkParticleUV("Textures/ShadowMarkParticle.png", {
    // Pre Explosion
    {{  0,   0, 48, 48}, {0.5f, 0.5f}}, //  0: Shadow Mark Pre Explosion Particle A
    {{ 48,   0, 48, 48}, {0.5f, 0.5f}}, //  1: Shadow Mark Pre Explosion Particle B

    // Explosion
    {{ 96,   0, 48, 48}, {0.5f, 0.5f}}, //  2: Shadow Mark Explosion Particle A
    {{144,   0, 48, 48}, {0.5f, 0.5f}}, //  3: Shadow Mark Explosion Particle B
});

enum class ShadowMarkParticleAnimType: std::size_t {
    PRE_EXPLOSION,
    EXPLOSION,
};

static const AnimationAsset shadowMarkParticleAnim(animEnum<ShadowMarkParticleAnimType>, {
    {ShadowMarkParticleAnimType::PRE_EXPLOSION, {{
        {0.50f, shadowMarkParticleUV[0]},
        {0.50f, shadowMarkParticleUV[1]},
    }}},
    {ShadowMarkParticleAnimType::EXPLOSION, {{
        {0.25f, shadowMarkParticleUV[2]},
        {0.25f, shadowMarkParticleUV[3]},
    }}},
});