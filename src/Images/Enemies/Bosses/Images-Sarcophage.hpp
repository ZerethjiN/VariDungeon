#pragma once

#include <Zerengine.hpp>

static const ImageAsset sarcophageUV("Textures/Sarcophage.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Sarcophage Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Sarcophage Move Down B
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Sarcophage Move Right A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Sarcophage Move Right B
    {{  0,  64, 32, 32}, {0.5f, 0.5f}}, //  4: Sarcophage Move Left A
    {{ 32,  64, 32, 32}, {0.5f, 0.5f}}, //  5: Sarcophage Move Left B
    {{  0,  96, 32, 32}, {0.5f, 0.5f}}, //  6: Sarcophage Move Up A
    {{ 32,  96, 32, 32}, {0.5f, 0.5f}}, //  7: Sarcophage Move Up B

    // Attacks
    {{  0, 128, 32, 32}, {0.5f, 0.5f}}, //  8: Sarcophage Attack Down A
    {{ 32, 128, 32, 32}, {0.5f, 0.5f}}, //  9: Sarcophage Attack Down B
    {{  0, 160, 32, 32}, {0.5f, 0.5f}}, // 10: Sarcophage Attack Right A
    {{ 32, 160, 32, 32}, {0.5f, 0.5f}}, // 11: Sarcophage Attack Right B
    {{  0, 192, 32, 32}, {0.5f, 0.5f}}, // 12: Sarcophage Attack Left A
    {{ 32, 192, 32, 32}, {0.5f, 0.5f}}, // 13: Sarcophage Attack Left B
    {{  0, 224, 32, 32}, {0.5f, 0.5f}}, // 14: Sarcophage Attack Up A
    {{ 32, 224, 32, 32}, {0.5f, 0.5f}}, // 15: Sarcophage Attack Up B

    // Hit Movements
    {{ 64,   0, 32, 32}, {0.5f, 0.5f}}, // 16: Sarcophage Hit Move Down A
    {{ 96,   0, 32, 32}, {0.5f, 0.5f}}, // 17: Sarcophage Hit Move Down B
    {{ 64,  32, 32, 32}, {0.5f, 0.5f}}, // 18: Sarcophage Hit Move Right A
    {{ 96,  32, 32, 32}, {0.5f, 0.5f}}, // 19: Sarcophage Hit Move Right B
    {{ 64,  64, 32, 32}, {0.5f, 0.5f}}, // 20: Sarcophage Hit Move Left A
    {{ 96,  64, 32, 32}, {0.5f, 0.5f}}, // 21: Sarcophage Hit Move Left B
    {{ 64,  96, 32, 32}, {0.5f, 0.5f}}, // 22: Sarcophage Hit Move Up A
    {{ 96,  96, 32, 32}, {0.5f, 0.5f}}, // 23: Sarcophage Hit Move Up B

    // Hit Attacks
    {{ 64, 128, 32, 32}, {0.5f, 0.5f}}, // 24: Sarcophage Hit Attack Down A
    {{ 96, 128, 32, 32}, {0.5f, 0.5f}}, // 25: Sarcophage Hit Attack Down B
    {{ 64, 160, 32, 32}, {0.5f, 0.5f}}, // 26: Sarcophage Hit Attack Right A
    {{ 96, 160, 32, 32}, {0.5f, 0.5f}}, // 27: Sarcophage Hit Attack Right B
    {{ 64, 192, 32, 32}, {0.5f, 0.5f}}, // 28: Sarcophage Hit Attack Left A
    {{ 96, 192, 32, 32}, {0.5f, 0.5f}}, // 29: Sarcophage Hit Attack Left B
    {{ 64, 224, 32, 32}, {0.5f, 0.5f}}, // 30: Sarcophage Hit Attack Up A
    {{ 96, 224, 32, 32}, {0.5f, 0.5f}}, // 31: Sarcophage Hit Attack Up B
});

static const AnimationAsset sarcophageAnim({
    // Movements
    {"MoveDown", {
        {0.20f, sarcophageUV[0]},
        {0.20f, sarcophageUV[1]},
    }},
    {"MoveRight", {
        {0.20f, sarcophageUV[2]},
        {0.20f, sarcophageUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, sarcophageUV[4]},
        {0.20f, sarcophageUV[5]},
    }},
    {"MoveUp", {
        {0.20f, sarcophageUV[6]},
        {0.20f, sarcophageUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.40f, sarcophageUV[8]},
        {0.40f, sarcophageUV[9]},
    }},
    {"AttackRight", {
        {0.40f, sarcophageUV[10]},
        {0.40f, sarcophageUV[11]},
    }},
    {"AttackLeft", {
        {0.40f, sarcophageUV[12]},
        {0.40f, sarcophageUV[13]},
    }},
    {"AttackUp", {
        {0.40f, sarcophageUV[14]},
        {0.40f, sarcophageUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, sarcophageUV[16]},
        {0.20f, sarcophageUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, sarcophageUV[18]},
        {0.20f, sarcophageUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, sarcophageUV[20]},
        {0.20f, sarcophageUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, sarcophageUV[22]},
        {0.20f, sarcophageUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.40f, sarcophageUV[24]},
        {0.40f, sarcophageUV[25]},
    }},
    {"HitAttackRight", {
        {0.40f, sarcophageUV[26]},
        {0.40f, sarcophageUV[27]},
    }},
    {"HitAttackLeft", {
        {0.40f, sarcophageUV[28]},
        {0.40f, sarcophageUV[29]},
    }},
    {"HitAttackUp", {
        {0.40f, sarcophageUV[30]},
        {0.40f, sarcophageUV[31]},
    }},
});