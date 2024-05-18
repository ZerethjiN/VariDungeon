#pragma once

#include <Zerengine.hpp>

static const ImageAsset explosionParticleUV("Textures/ExplosionParticle.png", {
    {{  0,   0, 48, 48}, {0.5f, 0.5f}}, //  0: Small Explosion Particle A
    {{ 48,   0, 48, 48}, {0.5f, 0.5f}}, //  1: Small Explosion Particle B
});

static const AnimationAsset explosionParticleAnim({
    {"SmallExplosion", {
        {0.15f, explosionParticleUV[0]},
        {0.15f, explosionParticleUV[1]},
    }},
});