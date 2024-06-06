#pragma once

#include <Zerengine.hpp>

static const ImageAsset rockBossUV("Textures/RockBoss.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Rock Boss Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Rock Boss Move Down B
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Rock Boss Move Right A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Rock Boss Move Right B
    {{  0,  64, 32, 32}, {0.5f, 0.5f}}, //  4: Rock Boss Move Left A
    {{ 32,  64, 32, 32}, {0.5f, 0.5f}}, //  5: Rock Boss Move Left B
    {{  0,  96, 32, 32}, {0.5f, 0.5f}}, //  6: Rock Boss Move Up A
    {{ 32,  96, 32, 32}, {0.5f, 0.5f}}, //  7: Rock Boss Move Up B

    // Rolls
    {{  0, 128, 32, 32}, {0.5f, 0.5f}}, //  8: Rock Boss Roll Down A
    {{ 32, 128, 32, 32}, {0.5f, 0.5f}}, //  9: Rock Boss Roll Down B
    {{  0, 160, 32, 32}, {0.5f, 0.5f}}, // 10: Rock Boss Roll Right A
    {{ 32, 160, 32, 32}, {0.5f, 0.5f}}, // 11: Rock Boss Roll Right B
    {{  0, 192, 32, 32}, {0.5f, 0.5f}}, // 12: Rock Boss Roll Left A
    {{ 32, 192, 32, 32}, {0.5f, 0.5f}}, // 13: Rock Boss Roll Left B
    {{  0, 224, 32, 32}, {0.5f, 0.5f}}, // 14: Rock Boss Roll Up A
    {{ 32, 224, 32, 32}, {0.5f, 0.5f}}, // 15: Rock Boss Roll Up B

    // Stuns
    {{  0, 256, 32, 32}, {0.5f, 0.5f}}, // 16: Rock Boss Stun Down A
    {{ 32, 256, 32, 32}, {0.5f, 0.5f}}, // 17: Rock Boss Stun Down B
    {{  0, 288, 32, 32}, {0.5f, 0.5f}}, // 18: Rock Boss Stun Right A
    {{ 32, 288, 32, 32}, {0.5f, 0.5f}}, // 19: Rock Boss Stun Right B
    {{  0, 320, 32, 32}, {0.5f, 0.5f}}, // 20: Rock Boss Stun Left A
    {{ 32, 320, 32, 32}, {0.5f, 0.5f}}, // 21: Rock Boss Stun Left B
    {{  0, 352, 32, 32}, {0.5f, 0.5f}}, // 22: Rock Boss Stun Up A
    {{ 32, 352, 32, 32}, {0.5f, 0.5f}}, // 23: Rock Boss Stun Up B

    // Hit Stuns
    {{ 64, 256, 32, 32}, {0.5f, 0.5f}}, // 24: Rock Boss Hit Stun Down A
    {{ 96, 256, 32, 32}, {0.5f, 0.5f}}, // 25: Rock Boss Hit Stun Down B
    {{ 64, 288, 32, 32}, {0.5f, 0.5f}}, // 26: Rock Boss Hit Stun Right A
    {{ 96, 288, 32, 32}, {0.5f, 0.5f}}, // 27: Rock Boss Hit Stun Right B
    {{ 64, 320, 32, 32}, {0.5f, 0.5f}}, // 28: Rock Boss Hit Stun Left A
    {{ 96, 320, 32, 32}, {0.5f, 0.5f}}, // 29: Rock Boss Hit Stun Left B
    {{ 64, 352, 32, 32}, {0.5f, 0.5f}}, // 30: Rock Boss Hit Stun Up A
    {{ 96, 352, 32, 32}, {0.5f, 0.5f}}, // 31: Rock Boss Hit Stun Up B
});

static const AnimationAsset rockBossAnim({
    // Movements
    {"MoveDown", {
        {0.20f, rockBossUV[0]},
        {0.20f, rockBossUV[1]},
    }},
    {"MoveRight", {
        {0.20f, rockBossUV[2]},
        {0.20f, rockBossUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, rockBossUV[4]},
        {0.20f, rockBossUV[5]},
    }},
    {"MoveUp", {
        {0.20f, rockBossUV[6]},
        {0.20f, rockBossUV[7]},
    }},

    // Rolls
    {"RollDown", {
        {0.20f, rockBossUV[8]},
        {0.20f, rockBossUV[9]},
    }},
    {"RollRight", {
        {0.20f, rockBossUV[10]},
        {0.20f, rockBossUV[11]},
    }},
    {"RollLeft", {
        {0.20f, rockBossUV[12]},
        {0.20f, rockBossUV[13]},
    }},
    {"RollUp", {
        {0.20f, rockBossUV[14]},
        {0.20f, rockBossUV[15]},
    }},

    // Stuns
    {"StunDown", {
        {0.20f, rockBossUV[16]},
        {0.20f, rockBossUV[17]},
    }},
    {"StunRight", {
        {0.20f, rockBossUV[18]},
        {0.20f, rockBossUV[19]},
    }},
    {"StunLeft", {
        {0.20f, rockBossUV[20]},
        {0.20f, rockBossUV[21]},
    }},
    {"StunUp", {
        {0.20f, rockBossUV[22]},
        {0.20f, rockBossUV[23]},
    }},

    // Hit Stuns
    {"HitStunDown", {
        {0.20f, rockBossUV[24]},
        {0.20f, rockBossUV[25]},
    }},
    {"HitStunRight", {
        {0.20f, rockBossUV[26]},
        {0.20f, rockBossUV[27]},
    }},
    {"HitStunLeft", {
        {0.20f, rockBossUV[28]},
        {0.20f, rockBossUV[29]},
    }},
    {"HitStunUp", {
        {0.20f, rockBossUV[30]},
        {0.20f, rockBossUV[31]},
    }},
});