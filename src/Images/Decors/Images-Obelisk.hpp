#pragma once

#include <Zerengine.hpp>

static const ImageAsset obeliskUV("Textures/Obelisk.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Obelisk A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Obelisk B
});

enum class ObeliskAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset obeliskAnim(animEnum<ObeliskAnimType>, {
    {ObeliskAnimType::DEFAULT, {{
        {1.50f, obeliskUV[0]},
        {1.50f, obeliskUV[1]},
    }}},
});