#pragma once

#include <Zerengine.hpp>

static const ImageAsset rockUV("Textures/Rock.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Rock No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Rock Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Rock Hit
});

enum class RockAnimType: std::size_t {
    NO_HIT,
    HIT,
    DESTROYED,
};

static const AnimationAsset rockAnim(animEnum<RockAnimType>, {
    {RockAnimType::NO_HIT, {{
        {1.00f, rockUV[0]},
    }, AnimationType::ONE_SHOT}},
    {RockAnimType::HIT, {{
        {1.00f, rockUV[2]},
    }, AnimationType::ONE_SHOT}},
    {RockAnimType::DESTROYED, {{
        {1.00f, rockUV[1]},
    }, AnimationType::ONE_SHOT}},
});