#pragma once

#include <Zerengine.hpp>

static const ImageAsset lightningBallParticleUV("Textures/LightningBall.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Lightning Ball Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Lightning Ball Particle B
});

enum class LightningBallParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset lightningBallParticleAnim(animEnum<LightningBallParticleAnimType>, {
    {LightningBallParticleAnimType::DEFAULT, {{
        {0.2f, lightningBallParticleUV[0]},
        {0.2f, lightningBallParticleUV[1]},
    }}},
});