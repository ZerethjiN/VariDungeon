#pragma once

#include <Zerengine.hpp>

static const ImageAsset particleEffectUV("Textures/ParticleEffect.png", {
    {{  0,   0,  8,  8}, {0.5f, 0.5f}}, //  0: Fire Particle A
    {{  8,   0,  8,  8}, {0.5f, 0.5f}}, //  1: Fire Particle B

    {{  0,   8,  8,  8}, {0.5f, 0.5f}}, //  2: Stun Particle A
    {{  8,   8,  8,  8}, {0.5f, 0.5f}}, //  3: Stun Particle B
    
    {{  0,  16,  8,  8}, {0.5f, 0.5f}}, //  4: Frost Particle A

    {{  0,  24,  8,  8}, {0.5f, 0.5f}}, //  5: Star Particle A
    {{  8,  24,  8,  8}, {0.5f, 0.5f}}, //  6: Star Particle B
});

enum class ParticleEffectAnimType: std::size_t {
    FIRE_PARTICLE,
    STUN_PARTICLE,
    FROST_PARTICLE,
    STAR_PARTICLE,
};

static const AnimationAsset particleEffectAnim(animEnum<ParticleEffectAnimType>, {
    {ParticleEffectAnimType::FIRE_PARTICLE, {{
        {0.15f, particleEffectUV[0]},
        {0.15f, particleEffectUV[1]},
    }}},
    {ParticleEffectAnimType::STUN_PARTICLE, {{
        {0.15f, particleEffectUV[2]},
        {0.15f, particleEffectUV[3]},
    }}},
    {ParticleEffectAnimType::FROST_PARTICLE, {{
        {0.15f, particleEffectUV[4]},
    }, AnimationType::ONE_SHOT}},
    {ParticleEffectAnimType::STAR_PARTICLE, {{
        {0.15f, particleEffectUV[5]},
        {0.15f, particleEffectUV[6]},
    }}},
});