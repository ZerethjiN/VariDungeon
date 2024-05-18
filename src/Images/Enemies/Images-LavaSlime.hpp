#pragma once

#include <Zerengine.hpp>

static const ImageAsset lavaSlimeUV("Textures/LavaSlime.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Lava Slime Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Lava Slime Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Lava Slime Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Lava Slime Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Lava Slime Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Lava Slime Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Lava Slime Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Lava Slime Move Up B

    // Pre Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Lava Slime Pre Attack Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, //  9: Lava Slime Pre Attack Down B

    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 10: Lava Slime Pre Attack Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 11: Lava Slime Pre Attack Right B

    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 12: Lava Slime Pre Attack Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 13: Lava Slime Pre Attack Left B

    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 14: Lava Slime Pre Attack Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 15: Lava Slime Pre Attack Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 16: Lava Slime Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 17: Lava Slime Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 18: Lava Slime Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 19: Lava Slime Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 20: Lava Slime Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 21: Lava Slime Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 22: Lava Slime Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 23: Lava Slime Hit Move Up B

    // Hit Pre Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Lava Slime Hit Pre Attack Down A
    {{ 48,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Lava Slime Hit Pre Attack Down B

    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Lava Slime Hit Pre Attack Right A
    {{ 48,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Lava Slime Hit Pre Attack Right B

    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Lava Slime Hit Pre Attack Left A
    {{ 48,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Lava Slime Hit Pre Attack Left B

    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Lava Slime Hit Pre Attack Up A
    {{ 48, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Lava Slime Hit Pre Attack Up B
});

static const AnimationAsset lavaSlimeAnim({
    // Movements
    {"MoveDown", {
        {0.20f, lavaSlimeUV[0]},
        {0.20f, lavaSlimeUV[1]},
    }},
    {"MoveRight", {
        {0.20f, lavaSlimeUV[2]},
        {0.20f, lavaSlimeUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, lavaSlimeUV[4]},
        {0.20f, lavaSlimeUV[5]},
    }},
    {"MoveUp", {
        {0.20f, lavaSlimeUV[6]},
        {0.20f, lavaSlimeUV[7]},
    }},

    // Pre Attacks
    {"PreAttackDown", {
        {0.20f, lavaSlimeUV[8]},
        {0.20f, lavaSlimeUV[9]},
    }},
    {"PreAttackRight", {
        {0.20f, lavaSlimeUV[10]},
        {0.20f, lavaSlimeUV[11]},
    }},
    {"PreAttackLeft", {
        {0.20f, lavaSlimeUV[12]},
        {0.20f, lavaSlimeUV[13]},
    }},
    {"PreAttackUp", {
        {0.20f, lavaSlimeUV[14]},
        {0.20f, lavaSlimeUV[15]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, lavaSlimeUV[16]},
        {0.20f, lavaSlimeUV[17]},
    }},
    {"HitMoveRight", {
        {0.20f, lavaSlimeUV[18]},
        {0.20f, lavaSlimeUV[19]},
    }},
    {"HitMoveLeft", {
        {0.20f, lavaSlimeUV[20]},
        {0.20f, lavaSlimeUV[21]},
    }},
    {"HitMoveUp", {
        {0.20f, lavaSlimeUV[22]},
        {0.20f, lavaSlimeUV[23]},
    }},

    // Hit Pre Attacks
    {"HitPreAttackDown", {
        {0.20f, lavaSlimeUV[24]},
        {0.20f, lavaSlimeUV[25]},
    }},
    {"HitPreAttackRight", {
        {0.20f, lavaSlimeUV[26]},
        {0.20f, lavaSlimeUV[27]},
    }},
    {"HitPreAttackLeft", {
        {0.20f, lavaSlimeUV[28]},
        {0.20f, lavaSlimeUV[29]},
    }},
    {"HitPreAttackUp", {
        {0.20f, lavaSlimeUV[30]},
        {0.20f, lavaSlimeUV[31]},
    }},
});