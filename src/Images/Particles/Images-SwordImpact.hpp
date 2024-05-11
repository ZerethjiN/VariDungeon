#pragma once

#include <Zerengine.hpp>

static const ImageAsset swordImpactUV("Textures/SwordImpact.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Sword Impact A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Sword Impact B
});

static const AnimationAsset swordImpactAnim({
    {"Default", {
        {0.05f, swordImpactUV[0]},
        {0.05f, swordImpactUV[1]},
    }},
});