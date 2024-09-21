#pragma once

#include <Zerengine.hpp>

static const ImageAsset voidSlimeUV("Textures/VoidSlime.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Void Slime Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Void Slime Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Void Slime Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Void Slime Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Void Slime Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Void Slime Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Void Slime Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Void Slime Move Up B

    // Pre Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Void Slime Pre Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Void Slime Pre Attack Down B

    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Void Slime Pre Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Void Slime Pre Attack Right B

    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Void Slime Pre Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Void Slime Pre Attack Left B

    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Void Slime Pre Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Void Slime Pre Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Void Slime Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Void Slime Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Void Slime Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Void Slime Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Void Slime Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Void Slime Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Void Slime Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Void Slime Hit Move Up B

    // Hit Pre Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Void Slime Hit Pre Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Void Slime Hit Pre Attack Down B

    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Void Slime Hit Pre Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Void Slime Hit Pre Attack Right B

    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Void Slime Hit Pre Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Void Slime Hit Pre Attack Left B

    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Void Slime Hit Pre Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Void Slime Hit Pre Attack Up B
});

enum class VoidSlimeAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    PRE_ATTACK_DOWN,
    PRE_ATTACK_RIGHT,
    PRE_ATTACK_LEFT,
    PRE_ATTACK_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
    HIT_PRE_ATTACK_DOWN,
    HIT_PRE_ATTACK_RIGHT,
    HIT_PRE_ATTACK_LEFT,
    HIT_PRE_ATTACK_UP,
};

static const AnimationAsset voidSlimeAnim(animEnum<VoidSlimeAnimType>, {
    // Movements
    {VoidSlimeAnimType::MOVE_DOWN, {{
        {0.20f, voidSlimeUV[0]},
        {0.20f, voidSlimeUV[1]},
    }}},
    {VoidSlimeAnimType::MOVE_RIGHT, {{
        {0.20f, voidSlimeUV[2]},
        {0.20f, voidSlimeUV[3]},
    }}},
    {VoidSlimeAnimType::MOVE_LEFT, {{
        {0.20f, voidSlimeUV[4]},
        {0.20f, voidSlimeUV[5]},
    }}},
    {VoidSlimeAnimType::MOVE_UP, {{
        {0.20f, voidSlimeUV[6]},
        {0.20f, voidSlimeUV[7]},
    }}},

    // Pre Attacks
    {VoidSlimeAnimType::PRE_ATTACK_DOWN, {{
        {0.20f, voidSlimeUV[8]},
        {0.20f, voidSlimeUV[9]},
    }}},
    {VoidSlimeAnimType::PRE_ATTACK_RIGHT, {{
        {0.20f, voidSlimeUV[10]},
        {0.20f, voidSlimeUV[11]},
    }}},
    {VoidSlimeAnimType::PRE_ATTACK_LEFT, {{
        {0.20f, voidSlimeUV[12]},
        {0.20f, voidSlimeUV[13]},
    }}},
    {VoidSlimeAnimType::PRE_ATTACK_UP, {{
        {0.20f, voidSlimeUV[14]},
        {0.20f, voidSlimeUV[15]},
    }}},

    // Hit Movements
    {VoidSlimeAnimType::HIT_MOVE_DOWN, {{
        {0.20f, voidSlimeUV[16]},
        {0.20f, voidSlimeUV[17]},
    }}},
    {VoidSlimeAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, voidSlimeUV[18]},
        {0.20f, voidSlimeUV[19]},
    }}},
    {VoidSlimeAnimType::HIT_MOVE_LEFT, {{
        {0.20f, voidSlimeUV[20]},
        {0.20f, voidSlimeUV[21]},
    }}},
    {VoidSlimeAnimType::HIT_MOVE_UP, {{
        {0.20f, voidSlimeUV[22]},
        {0.20f, voidSlimeUV[23]},
    }}},

    // Hit Pre Attacks
    {VoidSlimeAnimType::HIT_PRE_ATTACK_DOWN, {{
        {0.20f, voidSlimeUV[24]},
        {0.20f, voidSlimeUV[25]},
    }}},
    {VoidSlimeAnimType::HIT_PRE_ATTACK_RIGHT, {{
        {0.20f, voidSlimeUV[26]},
        {0.20f, voidSlimeUV[27]},
    }}},
    {VoidSlimeAnimType::HIT_PRE_ATTACK_LEFT, {{
        {0.20f, voidSlimeUV[28]},
        {0.20f, voidSlimeUV[29]},
    }}},
    {VoidSlimeAnimType::HIT_PRE_ATTACK_UP, {{
        {0.20f, voidSlimeUV[30]},
        {0.20f, voidSlimeUV[31]},
    }}},
});