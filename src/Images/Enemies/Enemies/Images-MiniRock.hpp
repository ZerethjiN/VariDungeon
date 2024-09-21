#pragma once

#include <Zerengine.hpp>

static const ImageAsset miniRockUV("Textures/MiniRock.png", {
    // Spawner
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Spawner A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Spawner B

    // Hit Spawner
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Hit Spawner A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  3: Hit Spawner B

    // Mini Rock
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  4: Mini Rock Move Down A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  5: Mini Rock Move Down B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  6: Mini Rock Move Right A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  7: Mini Rock Move Right B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  8: Mini Rock Move Left A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  9: Mini Rock Move Left B
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, // 10: Mini Rock Move Up A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, // 11: Mini Rock Move Up B

    // Hit Mini Rock
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 12: Hit Mini Rock Move Down A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 13: Hit Mini Rock Move Down B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 14: Hit Mini Rock Move Right A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 15: Hit Mini Rock Move Right B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 16: Hit Mini Rock Move Left A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 17: Hit Mini Rock Move Left B
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 18: Hit Mini Rock Move Up A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 19: Hit Mini Rock Move Up B
});

enum class MiniRockAnimType: std::size_t {
    SPAWNER,
    HIT_SPAWNER,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
};

static const AnimationAsset miniRockAnim(animEnum<MiniRockAnimType>, {
    {MiniRockAnimType::SPAWNER, {{
        {1.0f, miniRockUV[0]},
        {0.5f, miniRockUV[1]},
    }}},

    {MiniRockAnimType::HIT_SPAWNER, {{
        {1.0f, miniRockUV[2]},
        {0.5f, miniRockUV[3]},
    }}},

    {MiniRockAnimType::MOVE_DOWN, {{
        {0.2f, miniRockUV[4]},
        {0.2f, miniRockUV[5]},
    }}},
    {MiniRockAnimType::MOVE_RIGHT, {{
        {0.2f, miniRockUV[6]},
        {0.2f, miniRockUV[7]},
    }}},
    {MiniRockAnimType::MOVE_LEFT, {{
        {0.2f, miniRockUV[8]},
        {0.2f, miniRockUV[9]},
    }}},
    {MiniRockAnimType::MOVE_UP, {{
        {0.2f, miniRockUV[10]},
        {0.2f, miniRockUV[11]},
    }}},

    {MiniRockAnimType::HIT_MOVE_DOWN, {{
        {0.2f, miniRockUV[12]},
        {0.2f, miniRockUV[13]},
    }}},
    {MiniRockAnimType::HIT_MOVE_RIGHT, {{
        {0.2f, miniRockUV[14]},
        {0.2f, miniRockUV[15]},
    }}},
    {MiniRockAnimType::HIT_MOVE_LEFT, {{
        {0.2f, miniRockUV[16]},
        {0.2f, miniRockUV[17]},
    }}},
    {MiniRockAnimType::HIT_MOVE_UP, {{
        {0.2f, miniRockUV[18]},
        {0.2f, miniRockUV[19]},
    }}},
});