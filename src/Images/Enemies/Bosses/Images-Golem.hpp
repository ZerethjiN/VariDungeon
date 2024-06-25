#pragma once

#include <Zerengine.hpp>

static const ImageAsset golemUV("Textures/Golem.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Golem Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Golem Move Down B
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Golem Move Right A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Golem Move Right B
    {{  0,  64, 32, 32}, {0.5f, 0.5f}}, //  4: Golem Move Left A
    {{ 32,  64, 32, 32}, {0.5f, 0.5f}}, //  5: Golem Move Left B
    {{  0,  96, 32, 32}, {0.5f, 0.5f}}, //  6: Golem Move Up A
    {{ 32,  96, 32, 32}, {0.5f, 0.5f}}, //  7: Golem Move Up B

    // Attacks
    {{  0, 128, 32, 32}, {0.5f, 0.5f}}, //  8: Golem Attack Down A
    {{ 32, 128, 32, 32}, {0.5f, 0.5f}}, //  9: Golem Attack Down B
    {{  0, 160, 32, 32}, {0.5f, 0.5f}}, // 10: Golem Attack Right A
    {{ 32, 160, 32, 32}, {0.5f, 0.5f}}, // 11: Golem Attack Right B
    {{  0, 192, 32, 32}, {0.5f, 0.5f}}, // 12: Golem Attack Left A
    {{ 32, 192, 32, 32}, {0.5f, 0.5f}}, // 13: Golem Attack Left B
    {{  0, 224, 32, 32}, {0.5f, 0.5f}}, // 14: Golem Attack Up A
    {{ 32, 224, 32, 32}, {0.5f, 0.5f}}, // 15: Golem Attack Up B

    // Hit Movements
    {{ 64,   0, 32, 32}, {0.5f, 0.5f}}, // 16: Golem Hit Move Down A
    {{ 96,   0, 32, 32}, {0.5f, 0.5f}}, // 17: Golem Hit Move Down B
    {{ 64,  32, 32, 32}, {0.5f, 0.5f}}, // 18: Golem Hit Move Right A
    {{ 96,  32, 32, 32}, {0.5f, 0.5f}}, // 19: Golem Hit Move Right B
    {{ 64,  64, 32, 32}, {0.5f, 0.5f}}, // 20: Golem Hit Move Left A
    {{ 96,  64, 32, 32}, {0.5f, 0.5f}}, // 21: Golem Hit Move Left B
    {{ 64,  96, 32, 32}, {0.5f, 0.5f}}, // 22: Golem Hit Move Up A
    {{ 96,  96, 32, 32}, {0.5f, 0.5f}}, // 23: Golem Hit Move Up B

    // Hit Attacks
    {{ 64, 128, 32, 32}, {0.5f, 0.5f}}, // 24: Golem Hit Attack Down A
    {{ 96, 128, 32, 32}, {0.5f, 0.5f}}, // 25: Golem Hit Attack Down B
    {{ 64, 160, 32, 32}, {0.5f, 0.5f}}, // 26: Golem Hit Attack Right A
    {{ 96, 160, 32, 32}, {0.5f, 0.5f}}, // 27: Golem Hit Attack Right B
    {{ 64, 192, 32, 32}, {0.5f, 0.5f}}, // 28: Golem Hit Attack Left A
    {{ 96, 192, 32, 32}, {0.5f, 0.5f}}, // 29: Golem Hit Attack Left B
    {{ 64, 224, 32, 32}, {0.5f, 0.5f}}, // 30: Golem Hit Attack Up A
    {{ 96, 224, 32, 32}, {0.5f, 0.5f}}, // 31: Golem Hit Attack Up B
});

static const AnimationAsset golemAnim({
    // Movements
    {"MoveDown", {
        {0.20f, golemUV[0]},
        {0.20f, golemUV[1]},
    }},
    {"MoveRight", {
        {0.20f, golemUV[2]},
        {0.20f, golemUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, golemUV[4]},
        {0.20f, golemUV[5]},
    }},
    {"MoveUp", {
        {0.20f, golemUV[6]},
        {0.20f, golemUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.40f, golemUV[8]},
        {0.40f, golemUV[9]},
    }},
    {"AttackRight", {
        {0.40f, golemUV[10]},
        {0.40f, golemUV[11]},
    }},
    {"AttackLeft", {
        {0.40f, golemUV[12]},
        {0.40f, golemUV[13]},
    }},
    {"AttackUp", {
        {0.40f, golemUV[14]},
        {0.40f, golemUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, golemUV[16]},
        {0.20f, golemUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, golemUV[18]},
        {0.20f, golemUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, golemUV[20]},
        {0.20f, golemUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, golemUV[22]},
        {0.20f, golemUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.40f, golemUV[24]},
        {0.40f, golemUV[25]},
    }},
    {"HitAttackRight", {
        {0.40f, golemUV[26]},
        {0.40f, golemUV[27]},
    }},
    {"HitAttackLeft", {
        {0.40f, golemUV[28]},
        {0.40f, golemUV[29]},
    }},
    {"HitAttackUp", {
        {0.40f, golemUV[30]},
        {0.40f, golemUV[31]},
    }},
});