#pragma once

#include <Zerengine.hpp>

static const ImageAsset menuBonusHUDUV("Textures/MenuBonusHUD.png", {
    {{  0,   0, 144, 112}, {0.0f, 0.0f}}, //  0: Background

    {{  0, 112, 128,  32}, {0.0f, 0.0f}}, //  1: Medium Selector A
    {{  0, 144, 128,  32}, {0.0f, 0.0f}}, //  2: Medium Selector B

    {{  0, 176, 128,  48}, {0.0f, 0.0f}}, //  3: Large Selector A
    {{  0, 224, 128,  48}, {0.0f, 0.0f}}, //  4: Large Selector B
});

static const AnimationAsset menuBonusHUDAnim({
    {"MediumSelector", {
        {0.50f, menuBonusHUDUV[1]},
        {0.50f, menuBonusHUDUV[2]},
    }},
    {"LargeSelector", {
        {0.50f, menuBonusHUDUV[3]},
        {0.50f, menuBonusHUDUV[4]},
    }},
});