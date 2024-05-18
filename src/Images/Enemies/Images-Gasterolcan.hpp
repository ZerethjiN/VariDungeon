#pragma once

#include <Zerengine.hpp>

static const ImageAsset gasterolcanUV("Textures/Gasterolcan.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Gasterolcan Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Gasterolcan Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Gasterolcan Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Gasterolcan Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Gasterolcan Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Gasterolcan Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Gasterolcan Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Gasterolcan Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Gasterolcan Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Gasterolcan Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Gasterolcan Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Gasterolcan Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Gasterolcan Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Gasterolcan Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Gasterolcan Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Gasterolcan Attack Up B

    // Pre Attacks
    {{  0, 128, 16, 16}, {0.5f, 0.5f}}, // 16: Gasterolcan Pre Attack Down A
    {{ 16, 128, 16, 16}, {0.5f, 0.5f}}, // 17: Gasterolcan Pre Attack Down B
    {{  0, 144, 16, 16}, {0.5f, 0.5f}}, // 18: Gasterolcan Pre Attack Right A
    {{ 16, 144, 16, 16}, {0.5f, 0.5f}}, // 19: Gasterolcan Pre Attack Right B
    {{  0, 160, 16, 16}, {0.5f, 0.5f}}, // 20: Gasterolcan Pre Attack Left A
    {{ 16, 160, 16, 16}, {0.5f, 0.5f}}, // 21: Gasterolcan Pre Attack Left B
    {{  0, 176, 16, 16}, {0.5f, 0.5f}}, // 22: Gasterolcan Pre Attack Up A
    {{ 16, 176, 16, 16}, {0.5f, 0.5f}}, // 23: Gasterolcan Pre Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 24: Gasterolcan Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 25: Gasterolcan Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 26: Gasterolcan Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 27: Gasterolcan Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 28: Gasterolcan Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 29: Gasterolcan Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 30: Gasterolcan Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 31: Gasterolcan Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 32: Gasterolcan Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 33: Gasterolcan Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 34: Gasterolcan Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 35: Gasterolcan Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 36: Gasterolcan Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 37: Gasterolcan Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 38: Gasterolcan Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 39: Gasterolcan Hit Attack Up B

    // Hit Pre Attacks
    {{ 32, 128, 16, 16}, {0.5f, 0.5f}}, // 40: Gasterolcan Hit Pre Attack Down A
    {{ 48, 128, 16, 16}, {0.5f, 0.5f}}, // 41: Gasterolcan Hit Pre Attack Down B
    {{ 32, 144, 16, 16}, {0.5f, 0.5f}}, // 42: Gasterolcan Hit Pre Attack Right A
    {{ 48, 144, 16, 16}, {0.5f, 0.5f}}, // 43: Gasterolcan Hit Pre Attack Right B
    {{ 32, 160, 16, 16}, {0.5f, 0.5f}}, // 44: Gasterolcan Hit Pre Attack Left A
    {{ 48, 160, 16, 16}, {0.5f, 0.5f}}, // 45: Gasterolcan Hit Pre Attack Left B
    {{ 32, 176, 16, 16}, {0.5f, 0.5f}}, // 46: Gasterolcan Hit Pre Attack Up A
    {{ 48, 176, 16, 16}, {0.5f, 0.5f}}, // 47: Gasterolcan Hit Pre Attack Up B
});

static const AnimationAsset gasterolcanAnim({
    // Movements
    {"MoveDown", {
        {0.20f, gasterolcanUV[0]},
        {0.20f, gasterolcanUV[1]},
    }},
    {"MoveRight", {
        {0.20f, gasterolcanUV[2]},
        {0.20f, gasterolcanUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, gasterolcanUV[4]},
        {0.20f, gasterolcanUV[5]},
    }},
    {"MoveUp", {
        {0.20f, gasterolcanUV[6]},
        {0.20f, gasterolcanUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, gasterolcanUV[8]},
        {0.20f, gasterolcanUV[9]},
    }},
    {"AttackRight", {
        {0.20f, gasterolcanUV[10]},
        {0.20f, gasterolcanUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, gasterolcanUV[12]},
        {0.20f, gasterolcanUV[13]},
    }},
    {"AttackUp", {
        {0.20f, gasterolcanUV[14]},
        {0.20f, gasterolcanUV[15]},
    }},

    // Pre Attacks
    {"PreAttackDown", {
        {0.20f, gasterolcanUV[16]},
        {0.20f, gasterolcanUV[17]},
    }},
    {"PreAttackRight", {
        {0.20f, gasterolcanUV[18]},
        {0.20f, gasterolcanUV[19]},
    }},
    {"PreAttackLeft", {
        {0.20f, gasterolcanUV[20]},
        {0.20f, gasterolcanUV[21]},
    }},
    {"PreAttackUp", {
        {0.20f, gasterolcanUV[22]},
        {0.20f, gasterolcanUV[23]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, gasterolcanUV[24]},
        {0.20f, gasterolcanUV[25]},
    }},
    {"HitMoveRight", {
        {0.20f, gasterolcanUV[26]},
        {0.20f, gasterolcanUV[27]},
    }},
    {"HitMoveLeft", {
        {0.20f, gasterolcanUV[28]},
        {0.20f, gasterolcanUV[29]},
    }},
    {"HitMoveUp", {
        {0.20f, gasterolcanUV[30]},
        {0.20f, gasterolcanUV[31]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, gasterolcanUV[32]},
        {0.20f, gasterolcanUV[33]},
    }},
    {"HitAttackRight", {
        {0.20f, gasterolcanUV[34]},
        {0.20f, gasterolcanUV[35]},
    }},
    {"HitAttackLeft", {
        {0.20f, gasterolcanUV[36]},
        {0.20f, gasterolcanUV[37]},
    }},
    {"HitAttackUp", {
        {0.20f, gasterolcanUV[38]},
        {0.20f, gasterolcanUV[39]},
    }},

    // Hit Pre Attacks
    {"HitPreAttackDown", {
        {0.20f, gasterolcanUV[40]},
        {0.20f, gasterolcanUV[41]},
    }},
    {"HitPreAttackRight", {
        {0.20f, gasterolcanUV[42]},
        {0.20f, gasterolcanUV[43]},
    }},
    {"HitPreAttackLeft", {
        {0.20f, gasterolcanUV[44]},
        {0.20f, gasterolcanUV[45]},
    }},
    {"HitPreAttackUp", {
        {0.20f, gasterolcanUV[46]},
        {0.20f, gasterolcanUV[47]},
    }},
});