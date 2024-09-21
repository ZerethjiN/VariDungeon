#pragma once

#include <Zerengine.hpp>

static const ImageAsset shurikenParticleUV("Textures/Shuriken.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Shuriken Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Shuriken Particle B
});

enum class ShurikenParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset shurikenParticleAnim(animEnum<ShurikenParticleAnimType>, {
    {ShurikenParticleAnimType::DEFAULT, {{
        {0.20f, shurikenParticleUV[0]},
        {0.20f, shurikenParticleUV[1]},
    }}},
});