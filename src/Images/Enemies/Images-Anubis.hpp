#pragma once

#include <Zerengine.hpp>

static const ImageAsset anubisUV("Textures/Anubis.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Anubis Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Anubis Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Anubis Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Anubis Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Anubis Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Anubis Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Anubis Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Anubis Move Up B

    // Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Anubis Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Anubis Attack Down B
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Anubis Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Anubis Attack Right B
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Anubis Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Anubis Attack Left B
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Anubis Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Anubis Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Anubis Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Anubis Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Anubis Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Anubis Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Anubis Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Anubis Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Anubis Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Anubis Hit Move Up B

    // Hit Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Anubis Hit Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Anubis Hit Attack Down B
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Anubis Hit Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Anubis Hit Attack Right B
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Anubis Hit Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Anubis Hit Attack Left B
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Anubis Hit Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Anubis Hit Attack Up B
});

static const AnimationAsset anubisAnim({
    // Movements
    {"MoveDown", {
        {0.20f, anubisUV[0]},
        {0.20f, anubisUV[1]},
    }},
    {"MoveRight", {
        {0.20f, anubisUV[2]},
        {0.20f, anubisUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, anubisUV[4]},
        {0.20f, anubisUV[5]},
    }},
    {"MoveUp", {
        {0.20f, anubisUV[6]},
        {0.20f, anubisUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.20f, anubisUV[8]},
        {0.20f, anubisUV[9]},
    }},
    {"AttackRight", {
        {0.20f, anubisUV[10]},
        {0.20f, anubisUV[11]},
    }},
    {"AttackLeft", {
        {0.20f, anubisUV[12]},
        {0.20f, anubisUV[13]},
    }},
    {"AttackUp", {
        {0.20f, anubisUV[14]},
        {0.20f, anubisUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, anubisUV[16]},
        {0.20f, anubisUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, anubisUV[18]},
        {0.20f, anubisUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, anubisUV[20]},
        {0.20f, anubisUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, anubisUV[22]},
        {0.20f, anubisUV[23]},
    }},

    // Hit Attacks
    {"HitAttackDown", {
        {0.20f, anubisUV[24]},
        {0.20f, anubisUV[25]},
    }},
    {"HitAttackRight", {
        {0.20f, anubisUV[26]},
        {0.20f, anubisUV[27]},
    }},
    {"HitAttackLeft", {
        {0.20f, anubisUV[28]},
        {0.20f, anubisUV[29]},
    }},
    {"HitAttackUp", {
        {0.20f, anubisUV[30]},
        {0.20f, anubisUV[31]},
    }},
});