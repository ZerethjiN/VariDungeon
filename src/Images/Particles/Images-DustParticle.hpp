#pragma once

#include <Zerengine.hpp>

static const ImageAsset dustParticleUV("Textures/DustParticle.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Dust Particle A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Dust Particle B
});

enum class DustParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset dustParticleAnim(animEnum<DustParticleAnimType>, {
    {DustParticleAnimType::DEFAULT, {{
        {0.15f, dustParticleUV[0]},
        {0.15f, dustParticleUV[1]},
    }}},
});