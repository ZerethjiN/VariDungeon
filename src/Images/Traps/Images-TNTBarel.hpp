#pragma once

#include <Zerengine.hpp>

static const ImageAsset tntBarelUV("Textures/TntBarel.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: TNT Barel No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: TNT Barel Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: TNT Barel Hit
});

enum class TntBarelAnimType: std::size_t {
    NO_HIT,
    HIT,
    DESTROYED,
};

static const AnimationAsset tntBarelAnim(animEnum<TntBarelAnimType>, {
    {TntBarelAnimType::NO_HIT, {{
        {1.00f, tntBarelUV[0]},
    }, AnimationType::ONE_SHOT}},
    {TntBarelAnimType::HIT, {{
        {1.00f, tntBarelUV[2]},
    }, AnimationType::ONE_SHOT}},
    {TntBarelAnimType::DESTROYED, {{
        {1.00f, tntBarelUV[1]},
    }, AnimationType::ONE_SHOT}},
});