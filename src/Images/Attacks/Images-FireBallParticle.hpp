#pragma once

#include <Zerengine.hpp>

static const ImageAsset fireBallParticleUV("Textures/FireBallParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Fire Ball Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Fire Ball Particle B
});

static const AnimationAsset fireBallParticleAnim({
    {"Default", {
        {0.1f, fireBallParticleUV[0]},
        {0.1f, fireBallParticleUV[1]},
    }},
});