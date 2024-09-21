#pragma once

#include <Zerengine.hpp>

static const ImageAsset attractParticleUV("Textures/AttractParticle.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Attract Particle A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Attract Particle B
});

enum class AttractParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset attractParticleAnim(animEnum<AttractParticleAnimType>, {
    {AttractParticleAnimType::DEFAULT, {{
        {0.2f, attractParticleUV[0]},
        {0.2f, attractParticleUV[1]},
    }}},
});