#pragma once

#include <Zerengine.hpp>

static const ImageAsset voidSlimeUV("Textures/VoidSlime.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Void Slime Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Void Slime Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Void Slime Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Void Slime Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Void Slime Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Void Slime Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Void Slime Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Void Slime Move Up B

    // Pre Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Void Slime Pre Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Void Slime Pre Attack Down B

    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Void Slime Pre Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Void Slime Pre Attack Right B

    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Void Slime Pre Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Void Slime Pre Attack Left B

    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Void Slime Pre Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Void Slime Pre Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Void Slime Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Void Slime Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Void Slime Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Void Slime Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Void Slime Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Void Slime Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Void Slime Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Void Slime Hit Move Up B

    // Hit Pre Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Void Slime Hit Pre Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Void Slime Hit Pre Attack Down B

    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Void Slime Hit Pre Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Void Slime Hit Pre Attack Right B

    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Void Slime Hit Pre Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Void Slime Hit Pre Attack Left B

    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Void Slime Hit Pre Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Void Slime Hit Pre Attack Up B
});

static const AnimationAsset voidSlimeAnim({
    // Movements
    {"MoveDown", {
        {0.20f, voidSlimeUV[0]},
        {0.20f, voidSlimeUV[1]},
    }},
    {"MoveRight", {
        {0.20f, voidSlimeUV[2]},
        {0.20f, voidSlimeUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, voidSlimeUV[4]},
        {0.20f, voidSlimeUV[5]},
    }},
    {"MoveUp", {
        {0.20f, voidSlimeUV[6]},
        {0.20f, voidSlimeUV[7]},
    }},

    // Pre Attacks
    {"PreAttackDown", {
        {0.20f, voidSlimeUV[8]},
        {0.20f, voidSlimeUV[9]},
    }},
    {"PreAttackRight", {
        {0.20f, voidSlimeUV[10]},
        {0.20f, voidSlimeUV[11]},
    }},
    {"PreAttackLeft", {
        {0.20f, voidSlimeUV[12]},
        {0.20f, voidSlimeUV[13]},
    }},
    {"PreAttackUp", {
        {0.20f, voidSlimeUV[14]},
        {0.20f, voidSlimeUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, voidSlimeUV[16]},
        {0.20f, voidSlimeUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, voidSlimeUV[18]},
        {0.20f, voidSlimeUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, voidSlimeUV[20]},
        {0.20f, voidSlimeUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, voidSlimeUV[22]},
        {0.20f, voidSlimeUV[23]},
    }},

    // Hit Pre Attacks
    {"HitPreAttackDown", {
        {0.20f, voidSlimeUV[24]},
        {0.20f, voidSlimeUV[25]},
    }},
    {"HitPreAttackRight", {
        {0.20f, voidSlimeUV[26]},
        {0.20f, voidSlimeUV[27]},
    }},
    {"HitPreAttackLeft", {
        {0.20f, voidSlimeUV[28]},
        {0.20f, voidSlimeUV[29]},
    }},
    {"HitPreAttackUp", {
        {0.20f, voidSlimeUV[30]},
        {0.20f, voidSlimeUV[31]},
    }},
});