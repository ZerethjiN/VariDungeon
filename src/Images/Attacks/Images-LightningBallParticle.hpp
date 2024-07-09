#pragma once

#include <Zerengine.hpp>

static const ImageAsset lightningBallParticleUV("Textures/LightningBall.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Lightning Ball Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Lightning Ball Particle B
});

static const AnimationAsset lightningBallParticleAnim({
    {"Default", {
        {0.2f, lightningBallParticleUV[0]},
        {0.2f, lightningBallParticleUV[1]},
    }},
});