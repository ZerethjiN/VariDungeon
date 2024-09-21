#pragma once

#include <Zerengine.hpp>

static const ImageAsset warpUV("Textures/Warp.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Warp A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Warp B
});

enum class WarpAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset warpAnim(animEnum<WarpAnimType>, {
    {WarpAnimType::DEFAULT, {{
        {0.50f, warpUV[0]},
        {0.50f, warpUV[1]},
    }}},
});