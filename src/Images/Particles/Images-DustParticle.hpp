#pragma once

#include <Zerengine.hpp>

static const ImageAsset dustParticleUV("Textures/DustParticle.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Dust Particle A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Dust Particle B
});

static const AnimationAsset dustParticleAnim({
    {"Default", {
        {0.10f, dustParticleUV[0]},
        {0.10f, dustParticleUV[1]},
    }},
});