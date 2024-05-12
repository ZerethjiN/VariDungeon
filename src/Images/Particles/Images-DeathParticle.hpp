#pragma once

#include <Zerengine.hpp>

static const ImageAsset deathParticleUV("Textures/DeathParticle.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Death Particle A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Death Particle B
});

static const AnimationAsset deathParticleAnim({
    {"Default", {
        {0.10f, deathParticleUV[0]},
        {0.10f, deathParticleUV[1]},
    }},
});