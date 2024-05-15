#pragma once

#include <Zerengine.hpp>

static const ImageAsset pylonUV("Textures/Pylon.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Pylon A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Pylon B
});

static const AnimationAsset pylonAnim({
    {"Default", {
        {0.50f, pylonUV[0]},
        {0.50f, pylonUV[1]},
    }},
});