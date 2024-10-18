#pragma once

#include <Zerengine.hpp>

static const ImageAsset warpUV("Textures/Warp.png", {
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Warp A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Warp B

    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Warp Open A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Warp Open B
    {{ 64,  32, 32, 32}, {0.5f, 0.5f}}, //  4: Warp Open C
    {{ 96,  32, 32, 32}, {0.5f, 0.5f}}, //  5: Warp Open D
});

enum class WarpAnimType: std::size_t {
    DEFAULT,
    OPEN,
};

static const AnimationAsset warpAnim(animEnum<WarpAnimType>, {
    {WarpAnimType::DEFAULT, {{
        {0.50f, warpUV[0]},
        {0.50f, warpUV[1]},
    }}},
    {WarpAnimType::OPEN, {{
        {0.15f, warpUV[2]},
        {0.15f, warpUV[3]},
        {0.15f, warpUV[4]},
        {0.15f, warpUV[5]},
    }, AnimationType::ONE_SHOT}},
});