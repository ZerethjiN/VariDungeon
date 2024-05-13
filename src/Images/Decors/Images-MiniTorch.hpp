#pragma once

#include <Zerengine.hpp>

static const ImageAsset miniTorchUV("Textures/MiniTorch.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Mini Torch A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: MIni Torch B
});

static const AnimationAsset miniTorchAnim({
    {"Default", {
        {1.0f, miniTorchUV[0]},
        {1.00f, miniTorchUV[1]},
    }},
});