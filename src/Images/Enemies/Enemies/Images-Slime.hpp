#pragma once

#include <Zerengine.hpp>

static const ImageAsset slimeUV("Textures/Slime.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Slime Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Slime Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Slime Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Slime Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Slime Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Slime Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Slime Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Slime Move Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  8: Slime Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  9: Slime Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 10: Slime Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 11: Slime Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 12: Slime Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 13: Slime Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 14: Slime Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 15: Slime Hit Move Up B
});

enum class SlimeAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
};

static const AnimationAsset slimeAnim(animEnum<SlimeAnimType>, {
    // Movements
    {SlimeAnimType::MOVE_DOWN, {{
        {0.20f, slimeUV[0]},
        {0.20f, slimeUV[1]},
    }}},
    {SlimeAnimType::MOVE_RIGHT, {{
        {0.20f, slimeUV[2]},
        {0.20f, slimeUV[3]},
    }}},
    {SlimeAnimType::MOVE_LEFT, {{
        {0.20f, slimeUV[4]},
        {0.20f, slimeUV[5]},
    }}},
    {SlimeAnimType::MOVE_UP, {{
        {0.20f, slimeUV[6]},
        {0.20f, slimeUV[7]},
    }}},

    // Hit Movements
    {SlimeAnimType::HIT_MOVE_DOWN, {{
        {0.20f, slimeUV[8]},
        {0.20f, slimeUV[9]},
    }}},
    {SlimeAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, slimeUV[10]},
        {0.20f, slimeUV[11]},
    }}},
    {SlimeAnimType::HIT_MOVE_LEFT, {{
        {0.20f, slimeUV[12]},
        {0.20f, slimeUV[13]},
    }}},
    {SlimeAnimType::HIT_MOVE_UP, {{
        {0.20f, slimeUV[14]},
        {0.20f, slimeUV[15]},
    }}},
});