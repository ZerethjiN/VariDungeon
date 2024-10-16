#pragma once

#include <Zerengine.hpp>

static const ImageAsset shadowMinionUV("Textures/ShadowMinion.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Shadow Minion Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Shadow Minion Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Shadow Minion Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Shadow Minion Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Shadow Minion Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Shadow Minion Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Shadow Minion Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Shadow Minion Move Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  8: Shadow Minion Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  9: Shadow Minion Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 10: Shadow Minion Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 11: Shadow Minion Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 12: Shadow Minion Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 13: Shadow Minion Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 14: Shadow Minion Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 15: Shadow Minion Hit Move Up B
});

enum class ShadowMinionAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
};

static const AnimationAsset shadowMinionAnim(animEnum<ShadowMinionAnimType>, {
    // Movements
    {ShadowMinionAnimType::MOVE_DOWN, {{
        {0.20f, shadowMinionUV[0]},
        {0.20f, shadowMinionUV[1]},
    }}},
    {ShadowMinionAnimType::MOVE_RIGHT, {{
        {0.20f, shadowMinionUV[2]},
        {0.20f, shadowMinionUV[3]},
    }}},
    {ShadowMinionAnimType::MOVE_LEFT, {{
        {0.20f, shadowMinionUV[4]},
        {0.20f, shadowMinionUV[5]},
    }}},
    {ShadowMinionAnimType::MOVE_UP, {{
        {0.20f, shadowMinionUV[6]},
        {0.20f, shadowMinionUV[7]},
    }}},

    // Hit Movements
    {ShadowMinionAnimType::HIT_MOVE_DOWN, {{
        {0.20f, shadowMinionUV[8]},
        {0.20f, shadowMinionUV[9]},
    }}},
    {ShadowMinionAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, shadowMinionUV[10]},
        {0.20f, shadowMinionUV[11]},
    }}},
    {ShadowMinionAnimType::HIT_MOVE_LEFT, {{
        {0.20f, shadowMinionUV[12]},
        {0.20f, shadowMinionUV[13]},
    }}},
    {ShadowMinionAnimType::HIT_MOVE_UP, {{
        {0.20f, shadowMinionUV[14]},
        {0.20f, shadowMinionUV[15]},
    }}},
});