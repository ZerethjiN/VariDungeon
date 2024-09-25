#pragma once

#include <Zerengine.hpp>

static const ImageAsset menuBonusHUDUV("Textures/MenuBonusHUD.png", {
    {{  0,   0, 144, 112}, {0.0f, 0.0f}}, //  0: Background

    {{  0, 112, 128,  32}, {0.0f, 0.0f}}, //  1: Medium Selector A
    {{  0, 144, 128,  32}, {0.0f, 0.0f}}, //  2: Medium Selector B

    {{  0, 176, 128,  48}, {0.0f, 0.0f}}, //  3: Large Selector A
    {{  0, 224, 128,  48}, {0.0f, 0.0f}}, //  4: Large Selector B

    {{128, 112,  32,  32}, {0.0f, 0.0f}}, //  5: Small Selector A
    {{128, 144,  32,  32}, {0.0f, 0.0f}}, //  6: Small Selector B

    {{  0, 272, 128,  32}, {0.0f, 0.0f}}, //  7: Validation Motif A
    {{  0, 304, 128,  32}, {0.0f, 0.0f}}, //  8: Validation Motif B
    {{  0, 336, 128,  32}, {0.0f, 0.0f}}, //  9: Validation Motif C
});

enum class MenuBonusHUDAnimType: std::size_t {
    MEDIUM_SELECTOR,
    LARGE_SELECTOR,
    SMALL_SELECTOR,
    VALIDATION_MOTIF,
};

static const AnimationAsset menuBonusHUDAnim(animEnum<MenuBonusHUDAnimType>, {
    {MenuBonusHUDAnimType::MEDIUM_SELECTOR, {{
        {0.50f, menuBonusHUDUV[1]},
        {0.50f, menuBonusHUDUV[2]},
    }}},
    {MenuBonusHUDAnimType::LARGE_SELECTOR, {{
        {0.50f, menuBonusHUDUV[3]},
        {0.50f, menuBonusHUDUV[4]},
    }}},
    {MenuBonusHUDAnimType::SMALL_SELECTOR, {{
        {0.50f, menuBonusHUDUV[5]},
        {0.50f, menuBonusHUDUV[6]},
    }}},
    {MenuBonusHUDAnimType::VALIDATION_MOTIF, {{
        {0.05f, menuBonusHUDUV[7]},
        {0.05f, menuBonusHUDUV[8]},
        {0.05f, menuBonusHUDUV[9]},
    }, AnimationType::ONE_SHOT}},
});