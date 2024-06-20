#pragma once

#include <Zerengine.hpp>

static const ImageAsset insectUV("Textures/Insect.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Insect Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Insect Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Insect Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Insect Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Insect Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Insect Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Insect Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Insect Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Insect Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Insect Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Insect Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Insect Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Insect Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Insect Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Insect Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Insect Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Insect Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Insect Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Insect Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Insect Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Insect Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Insect Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Insect Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Insect Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Insect Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Insect Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Insect Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Insect Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Insect Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Insect Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Insect Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Insect Hit Attack Up B
});

static const AnimationAsset insectAnim({
    // Movements
    {"MoveDown", {
        {0.20f, insectUV[0]},
        {0.20f, insectUV[1]},
    }},
    {"MoveRight", {
        {0.20f, insectUV[2]},
        {0.20f, insectUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, insectUV[4]},
        {0.20f, insectUV[5]},
    }},
    {"MoveUp", {
        {0.20f, insectUV[6]},
        {0.20f, insectUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, insectUV[8]},
        {0.20f, insectUV[9]},
    }},
    {"AttackRight", {
        {0.20f, insectUV[10]},
        {0.20f, insectUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, insectUV[12]},
        {0.20f, insectUV[13]},
    }},
    {"AttackUp", {
        {0.20f, insectUV[14]},
        {0.20f, insectUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, insectUV[16]},
        {0.20f, insectUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, insectUV[18]},
        {0.20f, insectUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, insectUV[20]},
        {0.20f, insectUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, insectUV[22]},
        {0.20f, insectUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, insectUV[24]},
        {0.20f, insectUV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, insectUV[26]},
        {0.20f, insectUV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, insectUV[28]},
        {0.20f, insectUV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, insectUV[30]},
        {0.20f, insectUV[31]},
    }},
});