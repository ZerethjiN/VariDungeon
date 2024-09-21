#pragma once

#include <Zerengine.hpp>

static const ImageAsset merchantUV("Textures/Merchant.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Merchant A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Merchant B
});

enum class MerchantAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset merchantAnim(animEnum<MerchantAnimType>, {
    {MerchantAnimType::DEFAULT, {{
        {0.50f, merchantUV[0]},
        {0.50f, merchantUV[1]},
    }}},
});