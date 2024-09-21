#pragma once

#include <Zerengine.hpp>

static const ImageAsset homeButtonUV("Textures/HomeButton.png", {
    {{  0,   0,  96, 32}, {0.5f, 0.5f}}, //  0: Big Border Button

    {{128, 128, 128, 16}, {0.5f, 0.5f}}, //  1: Light Selector
    {{128, 144, 128, 16}, {0.5f, 0.5f}}, //  2: Light Selector
});

enum class HomeButtonAnimType: std::size_t {
    LIGHT_SELECTOR,
};

static const AnimationAsset homeButtonAnim(animEnum<HomeButtonAnimType>, {
    {HomeButtonAnimType::LIGHT_SELECTOR, {{
        {0.5f, homeButtonUV[1]},
        {0.5f, homeButtonUV[2]},
    }}},
});