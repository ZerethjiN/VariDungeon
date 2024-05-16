#pragma once

#include <Zerengine.hpp>

static const ImageAsset xpParticleUV("Textures/XpParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Xp Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Xp Particle B
});

static const AnimationAsset xpParticleAnim({
    {"Default", {
        {0.25f, xpParticleUV[0]},
        {0.25f, xpParticleUV[1]},
    }},
});