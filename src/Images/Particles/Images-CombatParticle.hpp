#pragma once

#include <Zerengine.hpp>

static const ImageAsset combatParticleUV("Textures/CombatParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Combat Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Combat Particle B
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Combat Particle C
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  3: Combat Particle D
});

enum class CombatParticleAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset combatParticleAnim(animEnum<CombatParticleAnimType>, {
    {CombatParticleAnimType::DEFAULT, {{
        {0.05f, combatParticleUV[0]},
        {0.05f, combatParticleUV[1]},
        {0.05f, combatParticleUV[2]},
        {0.05f, combatParticleUV[3]},
    }}},
});