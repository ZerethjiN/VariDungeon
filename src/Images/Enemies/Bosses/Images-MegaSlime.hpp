#pragma once

#include <Zerengine.hpp>

static const ImageAsset megaSlimeUV("Textures/MegaSlime.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Mega Slime Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Mega Slime Move Down B
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Mega Slime Move Right A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Mega Slime Move Right B
    {{  0,  64, 32, 32}, {0.5f, 0.5f}}, //  4: Mega Slime Move Left A
    {{ 32,  64, 32, 32}, {0.5f, 0.5f}}, //  5: Mega Slime Move Left B
    {{  0,  96, 32, 32}, {0.5f, 0.5f}}, //  6: Mega Slime Move Up A
    {{ 32,  96, 32, 32}, {0.5f, 0.5f}}, //  7: Mega Slime Move Up B

    // Attacks
    {{  0, 128, 32, 32}, {0.5f, 0.5f}}, //  8: Mega Slime Attack Down A
    {{ 32, 128, 32, 32}, {0.5f, 0.5f}}, //  9: Mega Slime Attack Down B
    {{  0, 160, 32, 32}, {0.5f, 0.5f}}, // 10: Mega Slime Attack Right A
    {{ 32, 160, 32, 32}, {0.5f, 0.5f}}, // 11: Mega Slime Attack Right B
    {{  0, 192, 32, 32}, {0.5f, 0.5f}}, // 12: Mega Slime Attack Left A
    {{ 32, 192, 32, 32}, {0.5f, 0.5f}}, // 13: Mega Slime Attack Left B
    {{  0, 224, 32, 32}, {0.5f, 0.5f}}, // 14: Mega Slime Attack Up A
    {{ 32, 224, 32, 32}, {0.5f, 0.5f}}, // 15: Mega Slime Attack Up B

    // Hit Movements
    {{ 64,   0, 32, 32}, {0.5f, 0.5f}}, // 16: Mega Slime Hit Move Down A
    {{ 96,   0, 32, 32}, {0.5f, 0.5f}}, // 17: Mega Slime Hit Move Down B
    {{ 64,  32, 32, 32}, {0.5f, 0.5f}}, // 18: Mega Slime Hit Move Right A
    {{ 96,  32, 32, 32}, {0.5f, 0.5f}}, // 19: Mega Slime Hit Move Right B
    {{ 64,  64, 32, 32}, {0.5f, 0.5f}}, // 20: Mega Slime Hit Move Left A
    {{ 96,  64, 32, 32}, {0.5f, 0.5f}}, // 21: Mega Slime Hit Move Left B
    {{ 64,  96, 32, 32}, {0.5f, 0.5f}}, // 22: Mega Slime Hit Move Up A
    {{ 96,  96, 32, 32}, {0.5f, 0.5f}}, // 23: Mega Slime Hit Move Up B

    // Hit Attacks
    {{ 64, 128, 32, 32}, {0.5f, 0.5f}}, // 24: Mega Slime Hit Attack Down A
    {{ 96, 128, 32, 32}, {0.5f, 0.5f}}, // 25: Mega Slime Hit Attack Down B
    {{ 64, 160, 32, 32}, {0.5f, 0.5f}}, // 26: Mega Slime Hit Attack Right A
    {{ 96, 160, 32, 32}, {0.5f, 0.5f}}, // 27: Mega Slime Hit Attack Right B
    {{ 64, 192, 32, 32}, {0.5f, 0.5f}}, // 28: Mega Slime Hit Attack Left A
    {{ 96, 192, 32, 32}, {0.5f, 0.5f}}, // 29: Mega Slime Hit Attack Left B
    {{ 64, 224, 32, 32}, {0.5f, 0.5f}}, // 30: Mega Slime Hit Attack Up A
    {{ 96, 224, 32, 32}, {0.5f, 0.5f}}, // 31: Mega Slime Hit Attack Up B

    // Shadow:
    {{ 32, 256, 32, 32}, {0.5f, 0.5f}}, // 32: Shadow A
    {{ 32, 256, 32, 32}, {0.5f, 0.5f}}, // 33: Shadow B

    // P2 Movements
    {{  0, 288, 32, 32}, {0.5f, 0.5f}}, // 34: Mega Slime P2 Move Down A
    {{ 32, 288, 32, 32}, {0.5f, 0.5f}}, // 35: Mega Slime P2 Move Down B
    {{  0, 320, 32, 32}, {0.5f, 0.5f}}, // 36: Mega Slime P2 Move Right A
    {{ 32, 320, 32, 32}, {0.5f, 0.5f}}, // 37: Mega Slime P2 Move Right B
    {{  0, 352, 32, 32}, {0.5f, 0.5f}}, // 38: Mega Slime P2 Move Left A
    {{ 32, 352, 32, 32}, {0.5f, 0.5f}}, // 39: Mega Slime P2 Move Left B
    {{  0, 384, 32, 32}, {0.5f, 0.5f}}, // 40: Mega Slime P2 Move Up A
    {{ 32, 384, 32, 32}, {0.5f, 0.5f}}, // 41: Mega Slime P2 Move Up B

    // P2 Attacks
    {{  0, 416, 32, 32}, {0.5f, 0.5f}}, // 42: Mega Slime P2 Attack Down A
    {{ 32, 416, 32, 32}, {0.5f, 0.5f}}, // 43: Mega Slime P2 Attack Down B
    {{  0, 448, 32, 32}, {0.5f, 0.5f}}, // 44: Mega Slime P2 Attack Right A
    {{ 32, 448, 32, 32}, {0.5f, 0.5f}}, // 45: Mega Slime P2 Attack Right B
    {{  0, 480, 32, 32}, {0.5f, 0.5f}}, // 46: Mega Slime P2 Attack Left A
    {{ 32, 480, 32, 32}, {0.5f, 0.5f}}, // 47: Mega Slime P2 Attack Left B
    {{  0, 512, 32, 32}, {0.5f, 0.5f}}, // 48: Mega Slime P2 Attack Up A
    {{ 32, 512, 32, 32}, {0.5f, 0.5f}}, // 49: Mega Slime P2 Attack Up B

    // P2 Hit Movements
    {{ 64, 288, 32, 32}, {0.5f, 0.5f}}, // 50: Mega Slime P2 Hit Move Down A
    {{ 96, 288, 32, 32}, {0.5f, 0.5f}}, // 51: Mega Slime P2 Hit Move Down B
    {{ 64, 320, 32, 32}, {0.5f, 0.5f}}, // 52: Mega Slime P2 Hit Move Right A
    {{ 96, 320, 32, 32}, {0.5f, 0.5f}}, // 53: Mega Slime P2 Hit Move Right B
    {{ 64, 352, 32, 32}, {0.5f, 0.5f}}, // 54: Mega Slime P2 Hit Move Left A
    {{ 96, 352, 32, 32}, {0.5f, 0.5f}}, // 55: Mega Slime P2 Hit Move Left B
    {{ 64, 384, 32, 32}, {0.5f, 0.5f}}, // 56: Mega Slime P2 Hit Move Up A
    {{ 96, 384, 32, 32}, {0.5f, 0.5f}}, // 57: Mega Slime P2 Hit Move Up B

    // P2 Hit Attacks
    {{ 64, 416, 32, 32}, {0.5f, 0.5f}}, // 58: Mega Slime P2 Hit Attack Down A
    {{ 96, 416, 32, 32}, {0.5f, 0.5f}}, // 59: Mega Slime P2 Hit Attack Down B
    {{ 64, 448, 32, 32}, {0.5f, 0.5f}}, // 60: Mega Slime P2 Hit Attack Right A
    {{ 96, 448, 32, 32}, {0.5f, 0.5f}}, // 61: Mega Slime P2 Hit Attack Right B
    {{ 64, 480, 32, 32}, {0.5f, 0.5f}}, // 62: Mega Slime P2 Hit Attack Left A
    {{ 96, 480, 32, 32}, {0.5f, 0.5f}}, // 63: Mega Slime P2 Hit Attack Left B
    {{ 64, 512, 32, 32}, {0.5f, 0.5f}}, // 64: Mega Slime P2 Hit Attack Up A
    {{ 96, 512, 32, 32}, {0.5f, 0.5f}}, // 65: Mega Slime P2 Hit Attack Up B
});

static const AnimationAsset megaSlimeAnim({
    // Movements
    {"MoveDown", {
        {0.20f, megaSlimeUV[0]},
        {0.20f, megaSlimeUV[1]},
    }},
    {"MoveRight", {
        {0.20f, megaSlimeUV[2]},
        {0.20f, megaSlimeUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, megaSlimeUV[4]},
        {0.20f, megaSlimeUV[5]},
    }},
    {"MoveUp", {
        {0.20f, megaSlimeUV[6]},
        {0.20f, megaSlimeUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.40f, megaSlimeUV[8]},
        {0.40f, megaSlimeUV[9]},
    }},
    {"AttackRight", {
        {0.40f, megaSlimeUV[10]},
        {0.40f, megaSlimeUV[11]},
    }},
    {"AttackLeft", {
        {0.40f, megaSlimeUV[12]},
        {0.40f, megaSlimeUV[13]},
    }},
    {"AttackUp", {
        {0.40f, megaSlimeUV[14]},
        {0.40f, megaSlimeUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, megaSlimeUV[16]},
        {0.20f, megaSlimeUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, megaSlimeUV[18]},
        {0.20f, megaSlimeUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, megaSlimeUV[20]},
        {0.20f, megaSlimeUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, megaSlimeUV[22]},
        {0.20f, megaSlimeUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.40f, megaSlimeUV[24]},
        {0.40f, megaSlimeUV[25]},
    }},
    {"HitAttackRight", {
        {0.40f, megaSlimeUV[26]},
        {0.40f, megaSlimeUV[27]},
    }},
    {"HitAttackLeft", {
        {0.40f, megaSlimeUV[28]},
        {0.40f, megaSlimeUV[29]},
    }},
    {"HitAttackUp", {
        {0.40f, megaSlimeUV[30]},
        {0.40f, megaSlimeUV[31]},
    }},

    // Shadow:
    {"Shadow", {
        {0.50f, megaSlimeUV[32]},
        {0.50f, megaSlimeUV[33]},
    }},

    // P2 Movements
    {"P2MoveDown", {
        {0.20f, megaSlimeUV[34]},
        {0.20f, megaSlimeUV[35]},
    }},
    {"P2MoveRight", {
        {0.20f, megaSlimeUV[36]},
        {0.20f, megaSlimeUV[37]},
    }},
    {"P2MoveLeft", {
        {0.20f, megaSlimeUV[38]},
        {0.20f, megaSlimeUV[39]},
    }},
    {"P2MoveUp", {
        {0.20f, megaSlimeUV[40]},
        {0.20f, megaSlimeUV[41]},
    }},

    // P2 Attacks
    {"P2AttackDown", {
        {0.40f, megaSlimeUV[42]},
        {0.40f, megaSlimeUV[43]},
    }},
    {"P2AttackRight", {
        {0.40f, megaSlimeUV[44]},
        {0.40f, megaSlimeUV[45]},
    }},
    {"P2AttackLeft", {
        {0.40f, megaSlimeUV[46]},
        {0.40f, megaSlimeUV[47]},
    }},
    {"P2AttackUp", {
        {0.40f, megaSlimeUV[48]},
        {0.40f, megaSlimeUV[49]},
    }},

    // P2 Hit Movements
    {"P2HitMoveDown", {
        {0.20f, megaSlimeUV[50]},
        {0.20f, megaSlimeUV[51]},
    }},
    {"P2HitMoveRight", {
        {0.20f, megaSlimeUV[52]},
        {0.20f, megaSlimeUV[53]},
    }},
    {"P2HitMoveLeft", {
        {0.20f, megaSlimeUV[54]},
        {0.20f, megaSlimeUV[55]},
    }},
    {"P2HitMoveUp", {
        {0.20f, megaSlimeUV[56]},
        {0.20f, megaSlimeUV[57]},
    }},

    // P2 Hit Attacks
    {"P2HitAttackDown", {
        {0.40f, megaSlimeUV[58]},
        {0.40f, megaSlimeUV[59]},
    }},
    {"P2HitAttackRight", {
        {0.40f, megaSlimeUV[60]},
        {0.40f, megaSlimeUV[61]},
    }},
    {"P2HitAttackLeft", {
        {0.40f, megaSlimeUV[62]},
        {0.40f, megaSlimeUV[63]},
    }},
    {"P2HitAttackUp", {
        {0.40f, megaSlimeUV[64]},
        {0.40f, megaSlimeUV[65]},
    }},
});