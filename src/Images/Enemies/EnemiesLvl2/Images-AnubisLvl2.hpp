#pragma once

#include <Zerengine.hpp>

static const ImageAsset anubisLvl2UV("Textures/AnubisLvl2.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Anubis Lvl2 Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Anubis Lvl2 Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Anubis Lvl2 Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Anubis Lvl2 Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Anubis Lvl2 Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Anubis Lvl2 Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Anubis Lvl2 Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Anubis Lvl2 Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Anubis Lvl2 Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Anubis Lvl2 Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Anubis Lvl2 Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Anubis Lvl2 Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Anubis Lvl2 Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Anubis Lvl2 Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Anubis Lvl2 Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Anubis Lvl2 Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Anubis Lvl2 Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Anubis Lvl2 Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Anubis Lvl2 Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Anubis Lvl2 Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Anubis Lvl2 Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Anubis Lvl2 Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Anubis Lvl2 Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Anubis Lvl2 Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Anubis Lvl2 Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Anubis Lvl2 Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Anubis Lvl2 Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Anubis Lvl2 Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Anubis Lvl2 Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Anubis Lvl2 Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Anubis Lvl2 Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Anubis Lvl2 Hit Attack Up B

    // Vanish
    {{  0, 128, 16, 16}, {0.5f, 0.5f}}, // 32: Anubis Lvl2 Vanish Down A
    {{ 16, 128, 16, 16}, {0.5f, 0.5f}}, // 33: Anubis Lvl2 Vanish Down B
    {{ 32, 128, 16, 16}, {0.5f, 0.5f}}, // 34: Anubis Lvl2 Vanish Down C
    {{  0, 144, 16, 16}, {0.5f, 0.5f}}, // 35: Anubis Lvl2 Vanish Right A
    {{ 16, 144, 16, 16}, {0.5f, 0.5f}}, // 36: Anubis Lvl2 Vanish Right B
    {{ 32, 144, 16, 16}, {0.5f, 0.5f}}, // 37: Anubis Lvl2 Vanish Right C
    {{  0, 160, 16, 16}, {0.5f, 0.5f}}, // 38: Anubis Lvl2 Vanish Left A
    {{ 16, 160, 16, 16}, {0.5f, 0.5f}}, // 39: Anubis Lvl2 Vanish Left B
    {{ 32, 160, 16, 16}, {0.5f, 0.5f}}, // 40: Anubis Lvl2 Vanish Left C
    {{  0, 176, 16, 16}, {0.5f, 0.5f}}, // 41: Anubis Lvl2 Vanish Up A
    {{ 16, 176, 16, 16}, {0.5f, 0.5f}}, // 42: Anubis Lvl2 Vanish Up B
    {{ 32, 176, 16, 16}, {0.5f, 0.5f}}, // 43: Anubis Lvl2 Vanish Up C
});

static const AnimationAsset anubisLvl2Anim({
    // Movements
    {"MoveDown", {
        {0.20f, anubisLvl2UV[0]},
        {0.20f, anubisLvl2UV[1]},
    }},
    {"MoveRight", {
        {0.20f, anubisLvl2UV[2]},
        {0.20f, anubisLvl2UV[3]},
    }},
    {"MoveLeft", {
        {0.20f, anubisLvl2UV[4]},
        {0.20f, anubisLvl2UV[5]},
    }},
    {"MoveUp", {
        {0.20f, anubisLvl2UV[6]},
        {0.20f, anubisLvl2UV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, anubisLvl2UV[8]},
        {0.20f, anubisLvl2UV[9]},
    }},
    {"AttackRight", {
        {0.20f, anubisLvl2UV[10]},
        {0.20f, anubisLvl2UV[11]},
    }},
    {"AttackLeft", {
        {0.20f, anubisLvl2UV[12]},
        {0.20f, anubisLvl2UV[13]},
    }},
    {"AttackUp", {
        {0.20f, anubisLvl2UV[14]},
        {0.20f, anubisLvl2UV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, anubisLvl2UV[16]},
        {0.20f, anubisLvl2UV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, anubisLvl2UV[18]},
        {0.20f, anubisLvl2UV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, anubisLvl2UV[20]},
        {0.20f, anubisLvl2UV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, anubisLvl2UV[22]},
        {0.20f, anubisLvl2UV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, anubisLvl2UV[24]},
        {0.20f, anubisLvl2UV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, anubisLvl2UV[26]},
        {0.20f, anubisLvl2UV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, anubisLvl2UV[28]},
        {0.20f, anubisLvl2UV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, anubisLvl2UV[30]},
        {0.20f, anubisLvl2UV[31]},
    }},

    // Vanish
    {"VanishDown", {{
        {0.20f, anubisLvl2UV[32]},
        {0.20f, anubisLvl2UV[33]},
        {0.20f, anubisLvl2UV[34]},
    }, AnimationType::ONE_SHOT}},
    {"VanishRight", {{
        {0.20f, anubisLvl2UV[35]},
        {0.20f, anubisLvl2UV[36]},
        {0.20f, anubisLvl2UV[37]},
    }, AnimationType::ONE_SHOT}},
    {"VanishLeft", {{
        {0.20f, anubisLvl2UV[38]},
        {0.20f, anubisLvl2UV[39]},
        {0.20f, anubisLvl2UV[40]},
    }, AnimationType::ONE_SHOT}},
    {"VanishUp", {{
        {0.20f, anubisLvl2UV[41]},
        {0.20f, anubisLvl2UV[42]},
        {0.20f, anubisLvl2UV[43]},
    }, AnimationType::ONE_SHOT}},
});