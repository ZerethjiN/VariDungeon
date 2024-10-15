#pragma once

#include <Zerengine.hpp>

static const ImageAsset shieldParticleUV("Textures/ShieldParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Shield Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Shield Particle B
});

enum class ShieldParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset shieldParticleAnim(animEnum<ShieldParticleAnimType>, {
    {ShieldParticleAnimType::DEFAULT, {{
        {0.25f, shieldParticleUV[0]},
        {0.25f, shieldParticleUV[1]},
    }}},
});