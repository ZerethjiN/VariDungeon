#pragma once

#include <Zerengine.hpp>

static const ImageAsset spectreUV("Textures/Spectre.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Spectre Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Spectre Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Spectre Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Spectre Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Spectre Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Spectre Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Spectre Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Spectre Move Up B

    // Attacks
    {{  0, 128, 16, 16}, {0.5f, 0.5f}}, //  8: Spectre Attack Down A
    {{ 16, 128, 16, 16}, {0.5f, 0.5f}}, //  9: Spectre Attack Down B
    {{  0, 144, 16, 16}, {0.5f, 0.5f}}, // 10: Spectre Attack Right A
    {{ 16, 144, 16, 16}, {0.5f, 0.5f}}, // 11: Spectre Attack Right B
    {{  0, 160, 16, 16}, {0.5f, 0.5f}}, // 12: Spectre Attack Left A
    {{ 16, 160, 16, 16}, {0.5f, 0.5f}}, // 13: Spectre Attack Left B
    {{  0, 176, 16, 16}, {0.5f, 0.5f}}, // 14: Spectre Attack Up A
    {{ 16, 176, 16, 16}, {0.5f, 0.5f}}, // 15: Spectre Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Spectre Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Spectre Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Spectre Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Spectre Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Spectre Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Spectre Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Spectre Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Spectre Hit Move Up B

    // Hit Attacks
    {{ 32, 128, 16, 16}, {0.5f, 0.5f}}, // 24: Spectre Hit Attack Down A
    {{ 48, 128, 16, 16}, {0.5f, 0.5f}}, // 25: Spectre Hit Attack Down B
    {{ 32, 144, 16, 16}, {0.5f, 0.5f}}, // 26: Spectre Hit Attack Right A
    {{ 48, 144, 16, 16}, {0.5f, 0.5f}}, // 27: Spectre Hit Attack Right B
    {{ 32, 160, 16, 16}, {0.5f, 0.5f}}, // 28: Spectre Hit Attack Left A
    {{ 48, 160, 16, 16}, {0.5f, 0.5f}}, // 29: Spectre Hit Attack Left B
    {{ 32, 176, 16, 16}, {0.5f, 0.5f}}, // 30: Spectre Hit Attack Up A
    {{ 48, 176, 16, 16}, {0.5f, 0.5f}}, // 31: Spectre Hit Attack Up B

    // Vanish
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, // 32: Spectre Vanish Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, // 33: Spectre Vanish Down B
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 34: Spectre Vanish Down C
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 35: Spectre Vanish Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 36: Spectre Vanish Right B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 37: Spectre Vanish Right C
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 38: Spectre Vanish Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 39: Spectre Vanish Left B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 40: Spectre Vanish Left C
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 41: Spectre Vanish Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 42: Spectre Vanish Up B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 43: Spectre Vanish Up C
});

static const AnimationAsset spectreAnim({
    // Movements
    {"MoveDown", {
        {0.20f, spectreUV[0]},
        {0.20f, spectreUV[1]},
    }},
    {"MoveRight", {
        {0.20f, spectreUV[2]},
        {0.20f, spectreUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, spectreUV[4]},
        {0.20f, spectreUV[5]},
    }},
    {"MoveUp", {
        {0.20f, spectreUV[6]},
        {0.20f, spectreUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, spectreUV[8]},
        {0.20f, spectreUV[9]},
    }},
    {"AttackRight", {
        {0.20f, spectreUV[10]},
        {0.20f, spectreUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, spectreUV[12]},
        {0.20f, spectreUV[13]},
    }},
    {"AttackUp", {
        {0.20f, spectreUV[14]},
        {0.20f, spectreUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, spectreUV[16]},
        {0.20f, spectreUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, spectreUV[18]},
        {0.20f, spectreUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, spectreUV[20]},
        {0.20f, spectreUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, spectreUV[22]},
        {0.20f, spectreUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, spectreUV[24]},
        {0.20f, spectreUV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, spectreUV[26]},
        {0.20f, spectreUV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, spectreUV[28]},
        {0.20f, spectreUV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, spectreUV[30]},
        {0.20f, spectreUV[31]},
    }},

    // Vanish
    {"VanishDown", {{
        {0.20f, spectreUV[32]},
        {0.20f, spectreUV[33]},
        {1.00f, spectreUV[34]},
    }, AnimationType::ONE_SHOT}},
    {"VanishRight", {{
        {0.20f, spectreUV[35]},
        {0.20f, spectreUV[36]},
        {1.00f, spectreUV[37]},
    }, AnimationType::ONE_SHOT}},
    {"VanishLeft", {{
        {0.20f, spectreUV[38]},
        {0.20f, spectreUV[39]},
        {1.00f, spectreUV[40]},
    }, AnimationType::ONE_SHOT}},
    {"VanishUp", {{
        {0.20f, spectreUV[41]},
        {0.20f, spectreUV[42]},
        {1.00f, spectreUV[43]},
    }, AnimationType::ONE_SHOT}},
});