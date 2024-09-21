#pragma once

#include <Zerengine.hpp>

static const ImageAsset batLvl2UV("Textures/BatLvl2.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Bat Lvl2 Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Bat Lvl2 Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Bat Lvl2 Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Bat Lvl2 Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Bat Lvl2 Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Bat Lvl2 Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Bat Lvl2 Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Bat Lvl2 Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Bat Lvl2 Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Bat Lvl2 Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Bat Lvl2 Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Bat Lvl2 Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Bat Lvl2 Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Bat Lvl2 Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Bat Lvl2 Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Bat Lvl2 Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Bat Lvl2 Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Bat Lvl2 Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Bat Lvl2 Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Bat Lvl2 Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Bat Lvl2 Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Bat Lvl2 Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Bat Lvl2 Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Bat Lvl2 Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Bat Lvl2 Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Bat Lvl2 Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Bat Lvl2 Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Bat Lvl2 Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Bat Lvl2 Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Bat Lvl2 Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Bat Lvl2 Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Bat Lvl2 Hit Attack Up B
});

enum class BatLvl2AnimType: std::size_t {
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

static const AnimationAsset batLvl2Anim(animEnum<BatLvl2AnimType>, {
    // Movements
    {BatLvl2AnimType::MOVE_DOWN, {{
        {0.20f, batLvl2UV[0]},
        {0.20f, batLvl2UV[1]},
    }}},
    {BatLvl2AnimType::MOVE_RIGHT, {{
        {0.20f, batLvl2UV[2]},
        {0.20f, batLvl2UV[3]},
    }}},
    {BatLvl2AnimType::MOVE_LEFT, {{
        {0.20f, batLvl2UV[4]},
        {0.20f, batLvl2UV[5]},
    }}},
    {BatLvl2AnimType::MOVE_UP, {{
        {0.20f, batLvl2UV[6]},
        {0.20f, batLvl2UV[7]},
    }}},

    // Attacks
    {BatLvl2AnimType::ATTACK_DOWN, {{
        {0.20f, batLvl2UV[8]},
        {0.20f, batLvl2UV[9]},
    }}},
    {BatLvl2AnimType::ATTACK_RIGHT, {{
        {0.20f, batLvl2UV[10]},
        {0.20f, batLvl2UV[11]},
    }}},
    {BatLvl2AnimType::ATTACK_LEFT, {{
        {0.20f, batLvl2UV[12]},
        {0.20f, batLvl2UV[13]},
    }}},
    {BatLvl2AnimType::ATTACK_UP, {{
        {0.20f, batLvl2UV[14]},
        {0.20f, batLvl2UV[15]},
    }}},

    // Hit Movements
    {BatLvl2AnimType::HIT_MOVE_DOWN, {{
        {0.20f, batLvl2UV[16]},
        {0.20f, batLvl2UV[17]},
    }}},
    {BatLvl2AnimType::HIT_MOVE_RIGHT, {{
        {0.20f, batLvl2UV[18]},
        {0.20f, batLvl2UV[19]},
    }}},
    {BatLvl2AnimType::HIT_MOVE_LEFT, {{
        {0.20f, batLvl2UV[20]},
        {0.20f, batLvl2UV[21]},
    }}},
    {BatLvl2AnimType::HIT_MOVE_UP, {{
        {0.20f, batLvl2UV[22]},
        {0.20f, batLvl2UV[23]},
    }}},

    // Hit Attacks
    {BatLvl2AnimType::HIT_ATTACK_DOWN, {{
        {0.20f, batLvl2UV[24]},
        {0.20f, batLvl2UV[25]},
    }}},
    {BatLvl2AnimType::HIT_ATTACK_RIGHT, {{
        {0.20f, batLvl2UV[26]},
        {0.20f, batLvl2UV[27]},
    }}},
    {BatLvl2AnimType::HIT_ATTACK_LEFT, {{
        {0.20f, batLvl2UV[28]},
        {0.20f, batLvl2UV[29]},
    }}},
    {BatLvl2AnimType::HIT_ATTACK_UP, {{
        {0.20f, batLvl2UV[30]},
        {0.20f, batLvl2UV[31]},
    }}},
});