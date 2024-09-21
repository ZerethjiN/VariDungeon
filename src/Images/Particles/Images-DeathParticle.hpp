#pragma once

#include <Zerengine.hpp>

static const ImageAsset deathParticleUV("Textures/DeathParticle.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Death Particle A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Death Particle B
});

enum class DeathParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset deathParticleAnim(animEnum<DeathParticleAnimType>, {
    {DeathParticleAnimType::DEFAULT, {{
        {0.15f, deathParticleUV[0]},
        {0.15f, deathParticleUV[1]},
    }}},
});