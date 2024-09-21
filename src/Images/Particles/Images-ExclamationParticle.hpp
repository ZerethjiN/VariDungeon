#pragma once

#include <Zerengine.hpp>

static const ImageAsset exclamationParticleUV("Textures/ExclamationParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Exclamation Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Exclamation Particle B
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Exclamation Particle C
});

enum class ExclamationParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset exclamationParticleAnim(animEnum<ExclamationParticleAnimType>, {
    {ExclamationParticleAnimType::DEFAULT, {{
        {0.05f, exclamationParticleUV[0]},
        {0.05f, exclamationParticleUV[1]},
        {1.00f, exclamationParticleUV[2]},
    }}},
});