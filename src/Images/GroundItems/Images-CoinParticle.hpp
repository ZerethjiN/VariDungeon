#pragma once

#include <Zerengine.hpp>

static const ImageAsset coinParticleUV("Textures/CoinParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Xp Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Xp Particle B
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Xp Particle C
});

static const AnimationAsset coinParticleAnim({
    {"Default", {
        {0.25f, coinParticleUV[0]},
        {0.25f, coinParticleUV[1]},
        {0.25f, coinParticleUV[2]},
        {0.25f, coinParticleUV[1]},
    }},
});