#pragma once

#include <Zerengine.hpp>

static const ImageAsset levelUpUV("Textures/LevelUp.png", {
    {{  0,   0, 96, 32}, {0.5f, 0.5f}}, //  0: Level Up Text A
    {{ 96,   0, 96, 32}, {0.5f, 0.5f}}, //  1: Level Up Text B
    {{192,   0, 96, 32}, {0.5f, 0.5f}}, //  2: Level Up Text C
});

static const AnimationAsset levelUpAnim({
    {"Default", {
        {0.20f, levelUpUV[0]},
        {0.20f, levelUpUV[1]},
        {0.20f, levelUpUV[2]},
    }},
});