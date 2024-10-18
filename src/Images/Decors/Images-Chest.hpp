#pragma once

#include <Zerengine.hpp>

static const ImageAsset chestUV("Textures/Chest.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Chest A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Chest B
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Chest C
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  3: Chest D
});

enum class ChestAnimType: std::size_t {
    OPENING,
};

static const AnimationAsset chestAnim(animEnum<ChestAnimType>, {
    {ChestAnimType::OPENING, {{
        {0.20f, chestUV[0]},
        {0.20f, chestUV[1]},
        {0.20f, chestUV[2]},
        {0.20f, chestUV[3]},
    }, AnimationType::ONE_SHOT}},
});