#pragma once

#include <Zerengine.hpp>

static const ImageAsset batUV("Textures/Bat.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Bat Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Bat Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Bat Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Bat Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Bat Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Bat Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Bat Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Bat Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Bat Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Bat Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Bat Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Bat Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Bat Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Bat Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Bat Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Bat Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Bat Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Bat Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Bat Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Bat Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Bat Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Bat Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Bat Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Bat Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Bat Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Bat Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Bat Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Bat Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Bat Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Bat Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Bat Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Bat Hit Attack Up B
});

enum class BatAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    ATTACK_DOWN,
    ATTACK_RIGHT,
    ATTACK_LEFT,
    ATTACK_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
    HIT_ATTACK_DOWN,
    HIT_ATTACK_RIGHT,
    HIT_ATTACK_LEFT,
    HIT_ATTACK_UP,
};

static const AnimationAsset batAnim(animEnum<BatAnimType>, {
    // Movements
    {BatAnimType::MOVE_DOWN, {{
        {0.20f, batUV[0]},
        {0.20f, batUV[1]},
    }}},
    {BatAnimType::MOVE_RIGHT, {{
        {0.20f, batUV[2]},
        {0.20f, batUV[3]},
    }}},
    {BatAnimType::MOVE_LEFT, {{
        {0.20f, batUV[4]},
        {0.20f, batUV[5]},
    }}},
    {BatAnimType::MOVE_UP, {{
        {0.20f, batUV[6]},
        {0.20f, batUV[7]},
    }}},

    // Attacks
    {BatAnimType::ATTACK_DOWN, {{
        {0.20f, batUV[8]},
        {0.20f, batUV[9]},
    }}},
    {BatAnimType::ATTACK_RIGHT, {{
        {0.20f, batUV[10]},
        {0.20f, batUV[11]},
    }}},
    {BatAnimType::ATTACK_LEFT, {{
        {0.20f, batUV[12]},
        {0.20f, batUV[13]},
    }}},
    {BatAnimType::ATTACK_UP, {{
        {0.20f, batUV[14]},
        {0.20f, batUV[15]},
    }}},

    // Hit Movements
    {BatAnimType::HIT_MOVE_DOWN, {{
        {0.20f, batUV[16]},
        {0.20f, batUV[17]},
    }}},
    {BatAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, batUV[18]},
        {0.20f, batUV[19]},
    }}},
    {BatAnimType::HIT_MOVE_LEFT, {{
        {0.20f, batUV[20]},
        {0.20f, batUV[21]},
    }}},
    {BatAnimType::HIT_MOVE_UP, {{
        {0.20f, batUV[22]},
        {0.20f, batUV[23]},
    }}},

    // Hit Attacks
    {BatAnimType::HIT_ATTACK_DOWN, {{
        {0.20f, batUV[24]},
        {0.20f, batUV[25]},
    }}},
    {BatAnimType::HIT_ATTACK_RIGHT, {{
        {0.20f, batUV[26]},
        {0.20f, batUV[27]},
    }}},
    {BatAnimType::HIT_ATTACK_LEFT, {{
        {0.20f, batUV[28]},
        {0.20f, batUV[29]},
    }}},
    {BatAnimType::HIT_ATTACK_UP, {{
        {0.20f, batUV[30]},
        {0.20f, batUV[31]},
    }}},
});