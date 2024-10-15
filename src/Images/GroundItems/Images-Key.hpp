#pragma once

#include <Zerengine.hpp>

static const ImageAsset keyUV("Textures/Key.png", {
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  0: Key A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  1: Key B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Key C
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Key D
});

enum class KeyAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset keyAnim(animEnum<KeyAnimType>, {
    {KeyAnimType::DEFAULT, {{
        {0.20f, keyUV[0]},
        {0.20f, keyUV[1]},
        {0.20f, keyUV[2]},
        {0.20f, keyUV[3]},
    }}},
});