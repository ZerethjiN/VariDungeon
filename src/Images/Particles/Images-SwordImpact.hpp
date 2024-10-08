#pragma once

#include <Zerengine.hpp>

static const ImageAsset swordImpactUV("Textures/SwordImpact.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Sword Impact A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Sword Impact B

    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Sword Impact Small A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  3: Sword Impact Small B
});

enum class SwordImpactAnimType: std::size_t {
    DEFAULT,
    SMALL,
};

static const AnimationAsset swordImpactAnim(animEnum<SwordImpactAnimType>, {
    {SwordImpactAnimType::DEFAULT, {{
        {0.05f, swordImpactUV[0]},
        {0.05f, swordImpactUV[1]},
    }}},
    {SwordImpactAnimType::SMALL, {{
        {0.05f, swordImpactUV[2]},
        {0.05f, swordImpactUV[3]},
    }}},
});