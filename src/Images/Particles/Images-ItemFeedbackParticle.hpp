#pragma once

#include <Zerengine.hpp>

static const ImageAsset itemFeedbackParticleUV("Textures/ItemFeedbackParticle.png", {
    // Big Particle
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  0: Big Particle A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  1: Big Particle B
});

static const AnimationAsset itemFeedbackParticleAnim({
    {"Big", {
        {0.1f, itemFeedbackParticleUV[0]},
        {0.1f, itemFeedbackParticleUV[1]},
    }},
});