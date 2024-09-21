#pragma once

#include <Zerengine.hpp>

static const ImageAsset popHitParticleUV("Textures/PopHitParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Pop Hit Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Pop Hit Particle B
});

enum class PopHitParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset popHitParticleAnim(animEnum<PopHitParticleAnimType>, {
    {PopHitParticleAnimType::DEFAULT, {{
        {0.05f, popHitParticleUV[0]},
        {0.05f, popHitParticleUV[1]},
    }}},
});