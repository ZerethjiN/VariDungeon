#pragma once

#include <Zerengine.hpp>

static const ImageAsset mummyLvl2UV("Textures/MummyLvl2.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Mummy Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Mummy Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Mummy Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Mummy Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Mummy Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Mummy Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Mummy Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Mummy Move Up B

    // Pre Attack
    {{  0, 128, 16, 16}, {0.5f, 0.5f}}, //  8: Mummy Pre Attack Down A
    {{  0, 144, 16, 16}, {0.5f, 0.5f}}, //  9: Mummy Pre Attack Right A
    {{  0, 160, 16, 16}, {0.5f, 0.5f}}, // 10: Mummy Pre Attack Left A
    {{  0, 176, 16, 16}, {0.5f, 0.5f}}, // 11: Mummy Pre Attack Up A

    // Attack
    {{  0,  64, 16, 32}, {0.5f, 0.25f}}, // 12: Mummy Attack Down
    {{  0,  96, 32, 16}, {0.25f, 0.5f}}, // 13: Mummy Attack Right
    {{  0, 112, 32, 16}, {0.75f, 0.5f}}, // 14: Mummy Attack Left
    {{ 16,  64, 16, 32}, {0.5f, 0.75f}}, // 15: Mummy Attack Up

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Mummy Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Mummy Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Mummy Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Mummy Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Mummy Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Mummy Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Mummy Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Mummy Hit Move Up B

    // Hit Pre Attack
    {{ 32, 128, 16, 16}, {0.5f, 0.5f}}, // 24: Mummy Hit Pre Attack Down A
    {{ 32, 144, 16, 16}, {0.5f, 0.5f}}, // 25: Mummy Hit Pre Attack Right A
    {{ 32, 160, 16, 16}, {0.5f, 0.5f}}, // 26: Mummy Hit Pre Attack Left A
    {{ 32, 176, 16, 16}, {0.5f, 0.5f}}, // 27: Mummy Hit Pre Attack Up A

    // Hit Attack
    {{ 32,  64, 16, 32}, {0.5f, 0.25f}}, // 28: Mummy Hit Attack Down
    {{ 32,  96, 32, 16}, {0.25f, 0.5f}}, // 29: Mummy Hit Attack Right
    {{ 32, 112, 32, 16}, {0.75f, 0.5f}}, // 30: Mummy Hit Attack Left
    {{ 48,  64, 16, 32}, {0.5f, 0.75f}}, // 31: Mummy Hit Attack Up
});

enum class MummyLvl2AnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    PRE_ATTACK_DOWN,
    PRE_ATTACK_RIGHT,
    PRE_ATTACK_LEFT,
    PRE_ATTACK_UP,
    ATTACK_DOWN,
    ATTACK_RIGHT,
    ATTACK_LEFT,
    ATTACK_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
    HIT_PRE_ATTACK_DOWN,
    HIT_PRE_ATTACK_RIGHT,
    HIT_PRE_ATTACK_LEFT,
    HIT_PRE_ATTACK_UP,
    HIT_ATTACK_DOWN,
    HIT_ATTACK_RIGHT,
    HIT_ATTACK_LEFT,
    HIT_ATTACK_UP,
};

static const AnimationAsset mummyLvl2Anim(animEnum<MummyLvl2AnimType>, {
    // Movements
    {MummyLvl2AnimType::MOVE_DOWN, {{
        {0.20f, mummyLvl2UV[0]},
        {0.20f, mummyLvl2UV[1]},
    }}},
    {MummyLvl2AnimType::MOVE_RIGHT, {{
        {0.20f, mummyLvl2UV[2]},
        {0.20f, mummyLvl2UV[3]},
    }}},
    {MummyLvl2AnimType::MOVE_LEFT, {{
        {0.20f, mummyLvl2UV[4]},
        {0.20f, mummyLvl2UV[5]},
    }}},
    {MummyLvl2AnimType::MOVE_UP, {{
        {0.20f, mummyLvl2UV[6]},
        {0.20f, mummyLvl2UV[7]},
    }}},

    // Pre Attack
    {MummyLvl2AnimType::PRE_ATTACK_DOWN, {{
        {0.20f, mummyLvl2UV[8]},
        {0.20f, mummyLvl2UV[1]},
    }}},
    {MummyLvl2AnimType::PRE_ATTACK_RIGHT, {{
        {0.20f, mummyLvl2UV[9]},
        {0.20f, mummyLvl2UV[3]},
    }}},
    {MummyLvl2AnimType::PRE_ATTACK_LEFT, {{
        {0.20f, mummyLvl2UV[10]},
        {0.20f, mummyLvl2UV[5]},
    }}},
    {MummyLvl2AnimType::PRE_ATTACK_UP, {{
        {0.20f, mummyLvl2UV[11]},
        {0.20f, mummyLvl2UV[7]},
    }}},

    // Attack
    {MummyLvl2AnimType::ATTACK_DOWN, {{
        {0.20f, mummyLvl2UV[12]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::ATTACK_RIGHT, {{
        {0.20f, mummyLvl2UV[13]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::ATTACK_LEFT, {{
        {0.20f, mummyLvl2UV[14]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::ATTACK_UP, {{
        {0.20f, mummyLvl2UV[15]},
    }, AnimationType::ONE_SHOT}},

    // Hit Movements
    {MummyLvl2AnimType::HIT_MOVE_DOWN, {{
        {0.20f, mummyLvl2UV[16]},
        {0.20f, mummyLvl2UV[17]},
    }}},
    {MummyLvl2AnimType::HIT_MOVE_RIGHT, {{
        {0.20f, mummyLvl2UV[18]},
        {0.20f, mummyLvl2UV[19]},
    }}},
    {MummyLvl2AnimType::HIT_MOVE_LEFT, {{
        {0.20f, mummyLvl2UV[20]},
        {0.20f, mummyLvl2UV[21]},
    }}},
    {MummyLvl2AnimType::HIT_MOVE_UP, {{
        {0.20f, mummyLvl2UV[22]},
        {0.20f, mummyLvl2UV[23]},
    }}},

    // Hit Pre Attack
    {MummyLvl2AnimType::HIT_PRE_ATTACK_DOWN, {{
        {0.20f, mummyLvl2UV[24]},
        {0.20f, mummyLvl2UV[17]},
    }}},
    {MummyLvl2AnimType::HIT_PRE_ATTACK_RIGHT, {{
        {0.20f, mummyLvl2UV[25]},
        {0.20f, mummyLvl2UV[19]},
    }}},
    {MummyLvl2AnimType::HIT_PRE_ATTACK_LEFT, {{
        {0.20f, mummyLvl2UV[26]},
        {0.20f, mummyLvl2UV[21]},
    }}},
    {MummyLvl2AnimType::HIT_PRE_ATTACK_UP, {{
        {0.20f, mummyLvl2UV[27]},
        {0.20f, mummyLvl2UV[23]},
    }}},

    // Hit Attack
    {MummyLvl2AnimType::HIT_ATTACK_DOWN, {{
        {1.00f, mummyLvl2UV[28]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::HIT_ATTACK_RIGHT, {{
        {0.20f, mummyLvl2UV[29]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::HIT_ATTACK_LEFT, {{
        {0.20f, mummyLvl2UV[30]},
    }, AnimationType::ONE_SHOT}},
    {MummyLvl2AnimType::HIT_ATTACK_UP, {{
        {0.20f, mummyLvl2UV[31]},
    }, AnimationType::ONE_SHOT}},
});