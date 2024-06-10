#pragma once

#include <Zerengine.hpp>

static const ImageAsset crystalUV("Textures/GroundCrystal.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Crystal No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Crystal Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Crystal Hit
});

static const AnimationAsset crystalAnim({
    {"NoHit", {{
        {1.00f, crystalUV[0]},
    }, AnimationType::ONE_SHOT}},
    {"Hit", {{
        {1.00f, crystalUV[2]},
    }, AnimationType::ONE_SHOT}},
    {"Destroyed", {{
        {1.00f, crystalUV[1]},
    }, AnimationType::ONE_SHOT}},
});