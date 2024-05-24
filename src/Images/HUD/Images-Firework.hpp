#pragma once

#include <Zerengine.hpp>

static const ImageAsset fireworkUV("Textures/Firework.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Firework A
    {{ 64,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Firework B
    {{ 96,   0, 32, 32}, {0.5f, 0.5f}}, //  2: Firework C
});

static const AnimationAsset fireworkAnim({
    {"Default", {
        {0.10f, fireworkUV[0]},
        {0.10f, fireworkUV[1]},
        {0.10f, fireworkUV[2]},
    }},
});