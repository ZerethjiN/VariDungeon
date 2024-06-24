#pragma once

#include <Zerengine.hpp>

static const ImageAsset scorpionUV("Textures/Scorpion.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Scorpion Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Scorpion Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Scorpion Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Scorpion Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Scorpion Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Scorpion Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Scorpion Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Scorpion Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Scorpion Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Scorpion Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Scorpion Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Scorpion Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Scorpion Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Scorpion Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Scorpion Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Scorpion Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Scorpion Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Scorpion Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Scorpion Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Scorpion Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Scorpion Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Scorpion Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Scorpion Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Scorpion Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Scorpion Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Scorpion Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Scorpion Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Scorpion Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Scorpion Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Scorpion Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Scorpion Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Scorpion Hit Attack Up B
});

static const AnimationAsset scorpionAnim({
    // Movements
    {"MoveDown", {
        {0.50f, scorpionUV[0]},
        {0.50f, scorpionUV[1]},
    }},
    {"MoveRight", {
        {0.50f, scorpionUV[2]},
        {0.50f, scorpionUV[3]},
    }},
    {"MoveLeft", {
        {0.50f, scorpionUV[4]},
        {0.50f, scorpionUV[5]},
    }},
    {"MoveUp", {
        {0.50f, scorpionUV[6]},
        {0.50f, scorpionUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.50f, scorpionUV[8]},
        {0.50f, scorpionUV[9]},
    }},
    {"AttackRight", {
        {0.50f, scorpionUV[10]},
        {0.50f, scorpionUV[11]},
    }},
    {"AttackLeft", {
        {0.50f, scorpionUV[12]},
        {0.50f, scorpionUV[13]},
    }},
    {"AttackUp", {
        {0.50f, scorpionUV[14]},
        {0.50f, scorpionUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.50f, scorpionUV[16]},
        {0.50f, scorpionUV[17]},
    }},
    {"HitMoveRight", {
        {0.50f, scorpionUV[18]},
        {0.50f, scorpionUV[19]},
    }},
    {"HitMoveLeft", {
        {0.50f, scorpionUV[20]},
        {0.50f, scorpionUV[21]},
    }},
    {"HitMoveUp", {
        {0.50f, scorpionUV[22]},
        {0.50f, scorpionUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.50f, scorpionUV[24]},
        {0.50f, scorpionUV[25]},
    }},
    {"HitAttackRight", {
        {0.50f, scorpionUV[26]},
        {0.50f, scorpionUV[27]},
    }},
    {"HitAttackLeft", {
        {0.50f, scorpionUV[28]},
        {0.50f, scorpionUV[29]},
    }},
    {"HitAttackUp", {
        {0.50f, scorpionUV[30]},
        {0.50f, scorpionUV[31]},
    }},
});