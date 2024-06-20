#pragma once

#include <Zerengine.hpp>

static const ImageAsset rockInsectUV("Textures/RockInsect.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Rock Insect Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Rock Insect Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Rock Insect Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Rock Insect Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Rock Insect Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Rock Insect Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Rock Insect Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Rock Insect Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Rock Insect Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Rock Insect Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Rock Insect Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Rock Insect Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Rock Insect Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Rock Insect Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Rock Insect Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Rock Insect Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Rock Insect Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Rock Insect Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Rock Insect Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Rock Insect Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Rock Insect Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Rock Insect Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Rock Insect Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Rock Insect Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Rock Insect Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Rock Insect Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Rock Insect Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Rock Insect Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Rock Insect Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Rock Insect Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Rock Insect Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Rock Insect Hit Attack Up B
});

static const AnimationAsset rockInsectAnim({
    // Movements
    {"MoveDown", {
        {0.20f, rockInsectUV[0]},
        {0.20f, rockInsectUV[1]},
    }},
    {"MoveRight", {
        {0.20f, rockInsectUV[2]},
        {0.20f, rockInsectUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, rockInsectUV[4]},
        {0.20f, rockInsectUV[5]},
    }},
    {"MoveUp", {
        {0.20f, rockInsectUV[6]},
        {0.20f, rockInsectUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, rockInsectUV[8]},
        {0.20f, rockInsectUV[9]},
    }},
    {"AttackRight", {
        {0.20f, rockInsectUV[10]},
        {0.20f, rockInsectUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, rockInsectUV[12]},
        {0.20f, rockInsectUV[13]},
    }},
    {"AttackUp", {
        {0.20f, rockInsectUV[14]},
        {0.20f, rockInsectUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, rockInsectUV[16]},
        {0.20f, rockInsectUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, rockInsectUV[18]},
        {0.20f, rockInsectUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, rockInsectUV[20]},
        {0.20f, rockInsectUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, rockInsectUV[22]},
        {0.20f, rockInsectUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, rockInsectUV[24]},
        {0.20f, rockInsectUV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, rockInsectUV[26]},
        {0.20f, rockInsectUV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, rockInsectUV[28]},
        {0.20f, rockInsectUV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, rockInsectUV[30]},
        {0.20f, rockInsectUV[31]},
    }},
});