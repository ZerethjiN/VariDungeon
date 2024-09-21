#pragma once

#include <Zerengine.hpp>

static const ImageAsset bigCrystalUV("Textures/Crystal.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Crystal A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Crystal B
});

enum class BigCrystalAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset bigCrystalAnim(animEnum<BigCrystalAnimType>, {
    {BigCrystalAnimType::DEFAULT, {{
        {0.50f, bigCrystalUV[0]},
        {0.50f, bigCrystalUV[1]},
    }}},
});