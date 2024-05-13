#pragma once

#include <Zerengine.hpp>

static const ImageAsset shadowUV("Textures/Shadow.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Shadow Small A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Shadow Small B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Shadow Big A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Shadow Big B
});

static const AnimationAsset shadowAnim({
    {"Small", {
        {1.00f, combatParticleUV[0]},
        {1.00f, combatParticleUV[1]},
    }},
    {"Big", {
        {1.00f, combatParticleUV[2]},
        {1.00f, combatParticleUV[3]},
    }},
});