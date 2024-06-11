#pragma once

#include <Zerengine.hpp>

static const ImageAsset groundCrystalAttackUV("Textures/GroundCrystalAttack.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Floor Cross Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Floor Cross Particle B

    {{  0,   16, 16, 16}, {0.5f, 0.5f}}, //  2: Crystal Particle
});

static const AnimationAsset groundCrystalAttackAnim({
    {"Cross", {
        {0.25f, groundCrystalAttackUV[0]},
        {0.25f, groundCrystalAttackUV[1]},
    }},
    {"Crystal", {{
        {1.0f, groundCrystalAttackUV[2]},
    }, AnimationType::ONE_SHOT}},
});