#pragma once

#include <Zerengine.hpp>

static const ImageAsset batUV("Textures/Bat.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Bat Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Bat Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Bat Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Bat Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Bat Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Bat Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Bat Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Bat Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Bat Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Bat Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Bat Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Bat Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Bat Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Bat Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Bat Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Bat Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Bat Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Bat Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Bat Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Bat Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Bat Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Bat Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Bat Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Bat Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Bat Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Bat Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Bat Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Bat Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Bat Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Bat Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Bat Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Bat Hit Attack Up B
});

static const AnimationAsset batAnim({
    // Movements
    {"MoveDown", {
        {0.20f, batUV[0]},
        {0.20f, batUV[1]},
    }},
    {"MoveRight", {
        {0.20f, batUV[2]},
        {0.20f, batUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, batUV[4]},
        {0.20f, batUV[5]},
    }},
    {"MoveUp", {
        {0.20f, batUV[6]},
        {0.20f, batUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, batUV[8]},
        {0.20f, batUV[9]},
    }},
    {"AttackRight", {
        {0.20f, batUV[10]},
        {0.20f, batUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, batUV[12]},
        {0.20f, batUV[13]},
    }},
    {"AttackUp", {
        {0.20f, batUV[14]},
        {0.20f, batUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, batUV[16]},
        {0.20f, batUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, batUV[18]},
        {0.20f, batUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, batUV[20]},
        {0.20f, batUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, batUV[22]},
        {0.20f, batUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, batUV[24]},
        {0.20f, batUV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, batUV[26]},
        {0.20f, batUV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, batUV[28]},
        {0.20f, batUV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, batUV[30]},
        {0.20f, batUV[31]},
    }},
});