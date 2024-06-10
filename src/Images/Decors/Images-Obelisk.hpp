#pragma once

#include <Zerengine.hpp>

static const ImageAsset obeliskUV("Textures/Obelisk.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Obelisk A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Obelisk B
});

static const AnimationAsset obeliskAnim({
    {"Default", {
        {1.50f, obeliskUV[0]},
        {1.50f, obeliskUV[1]},
    }},
});