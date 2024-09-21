#pragma once

#include <Zerengine.hpp>

static const ImageAsset torchUV("Textures/Torch.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Torch Off A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Torch Off B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Torch On A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Torch On B
});

enum class TorchAnimType: std::size_t {
    OFF,
    ON,
};

static const AnimationAsset torchAnim(animEnum<TorchAnimType>, {
    {TorchAnimType::OFF, {{
        {0.50f, torchUV[0]},
        {0.50f, torchUV[1]},
    }}},
    {TorchAnimType::ON, {{
        {0.50f, torchUV[2]},
        {0.50f, torchUV[3]},
    }}},
});