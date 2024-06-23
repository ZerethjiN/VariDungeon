#pragma once

#include <Zerengine.hpp>

static const ImageAsset bigCrystalUV("Textures/Crystal.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Crystal A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Crystal B
});

static const AnimationAsset bigCrystalAnim({
    {"Default", {
        {0.50f, bigCrystalUV[0]},
        {0.50f, bigCrystalUV[1]},
    }},
});