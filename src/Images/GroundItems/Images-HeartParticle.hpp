#pragma once

#include <Zerengine.hpp>

static const ImageAsset heartParticleUV("Textures/HeartParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Heart Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Heart Particle B
});

enum class HeartParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset heartParticleAnim(animEnum<HeartParticleAnimType>, {
    {HeartParticleAnimType::DEFAULT, {{
        {0.25f, heartParticleUV[0]},
        {0.25f, heartParticleUV[1]},
    }}},
});