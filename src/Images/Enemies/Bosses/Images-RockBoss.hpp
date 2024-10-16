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

    // Move P2
    {{  0, 384, 32, 32}, {0.5f, 0.5f}}, // 32: Rock Boss Move P2 Down A
    {{ 32, 384, 32, 32}, {0.5f, 0.5f}}, // 33: Rock Boss Move P2 Down B
    {{  0, 416, 32, 32}, {0.5f, 0.5f}}, // 34: Rock Boss Move P2 Right A
    {{ 32, 416, 32, 32}, {0.5f, 0.5f}}, // 35: Rock Boss Move P2 Right B
    {{  0, 448, 32, 32}, {0.5f, 0.5f}}, // 36: Rock Boss Move P2 Left A
    {{ 32, 448, 32, 32}, {0.5f, 0.5f}}, // 37: Rock Boss Move P2 Left B
    {{  0, 480, 32, 32}, {0.5f, 0.5f}}, // 38: Rock Boss Move P2 Up A
    {{ 32, 480, 32, 32}, {0.5f, 0.5f}}, // 39: Rock Boss Move P2 Up B

    // Roll P2
    {{  0, 512, 32, 32}, {0.5f, 0.5f}}, // 40: Rock Boss Roll P2 Down A
    {{ 32, 512, 32, 32}, {0.5f, 0.5f}}, // 41: Rock Boss Roll P2 Down B
    {{  0, 544, 32, 32}, {0.5f, 0.5f}}, // 42: Rock Boss Roll P2 Right A
    {{ 32, 544, 32, 32}, {0.5f, 0.5f}}, // 43: Rock Boss Roll P2 Right B
    {{  0, 576, 32, 32}, {0.5f, 0.5f}}, // 44: Rock Boss Roll P2 Left A
    {{ 32, 576, 32, 32}, {0.5f, 0.5f}}, // 45: Rock Boss Roll P2 Left B
    {{  0, 608, 32, 32}, {0.5f, 0.5f}}, // 46: Rock Boss Roll P2 Up A
    {{ 32, 608, 32, 32}, {0.5f, 0.5f}}, // 47: Rock Boss Roll P2 Up B
});

enum class RockBossAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    ROLL_DOWN,
    ROLL_RIGHT,
    ROLL_LEFT,
    ROLL_UP,
    STUN_DOWN,
    STUN_RIGHT,
    STUN_LEFT,
    STUN_UP,
    HIT_STUN_DOWN,
    HIT_STUN_RIGHT,
    HIT_STUN_LEFT,
    HIT_STUN_UP,
    P2_MOVE_DOWN,
    P2_MOVE_RIGHT,
    P2_MOVE_LEFT,
    P2_MOVE_UP,
    P2_ROLL_DOWN,
    P2_ROLL_RIGHT,
    P2_ROLL_LEFT,
    P2_ROLL_UP,
};

static const AnimationAsset rockBossAnim(animEnum<RockBossAnimType>, {
    // Movements
    {RockBossAnimType::MOVE_DOWN, {{
        {0.20f, rockBossUV[0]},
        {0.20f, rockBossUV[1]},
    }}},
    {RockBossAnimType::MOVE_RIGHT, {{
        {0.20f, rockBossUV[2]},
        {0.20f, rockBossUV[3]},
    }}},
    {RockBossAnimType::MOVE_LEFT, {{
        {0.20f, rockBossUV[4]},
        {0.20f, rockBossUV[5]},
    }}},
    {RockBossAnimType::MOVE_UP, {{
        {0.20f, rockBossUV[6]},
        {0.20f, rockBossUV[7]},
    }}},

    // Rolls
    {RockBossAnimType::ROLL_DOWN, {{
        {0.20f, rockBossUV[8]},
        {0.20f, rockBossUV[9]},
    }}},
    {RockBossAnimType::ROLL_RIGHT, {{
        {0.20f, rockBossUV[10]},
        {0.20f, rockBossUV[11]},
    }}},
    {RockBossAnimType::ROLL_LEFT, {{
        {0.20f, rockBossUV[12]},
        {0.20f, rockBossUV[13]},
    }}},
    {RockBossAnimType::ROLL_UP, {{
        {0.20f, rockBossUV[14]},
        {0.20f, rockBossUV[15]},
    }}},

    // Stuns
    {RockBossAnimType::STUN_DOWN, {{
        {0.20f, rockBossUV[16]},
        {0.20f, rockBossUV[17]},
    }}},
    {RockBossAnimType::STUN_RIGHT, {{
        {0.20f, rockBossUV[18]},
        {0.20f, rockBossUV[19]},
    }}},
    {RockBossAnimType::STUN_LEFT, {{
        {0.20f, rockBossUV[20]},
        {0.20f, rockBossUV[21]},
    }}},
    {RockBossAnimType::STUN_UP, {{
        {0.20f, rockBossUV[22]},
        {0.20f, rockBossUV[23]},
    }}},

    // Hit Stuns
    {RockBossAnimType::HIT_STUN_DOWN, {{
        {0.20f, rockBossUV[24]},
        {0.20f, rockBossUV[25]},
    }}},
    {RockBossAnimType::HIT_STUN_RIGHT, {{
        {0.20f, rockBossUV[26]},
        {0.20f, rockBossUV[27]},
    }}},
    {RockBossAnimType::HIT_STUN_LEFT, {{
        {0.20f, rockBossUV[28]},
        {0.20f, rockBossUV[29]},
    }}},
    {RockBossAnimType::HIT_STUN_UP, {{
        {0.20f, rockBossUV[30]},
        {0.20f, rockBossUV[31]},
    }}},

    // Move P2
    {RockBossAnimType::P2_MOVE_DOWN, {{
        {0.20f, rockBossUV[32]},
        {0.20f, rockBossUV[33]},
    }}},
    {RockBossAnimType::P2_MOVE_RIGHT, {{
        {0.20f, rockBossUV[34]},
        {0.20f, rockBossUV[35]},
    }}},
    {RockBossAnimType::P2_MOVE_LEFT, {{
        {0.20f, rockBossUV[36]},
        {0.20f, rockBossUV[37]},
    }}},
    {RockBossAnimType::P2_MOVE_UP, {{
        {0.20f, rockBossUV[38]},
        {0.20f, rockBossUV[39]},
    }}},

    // Roll P2
    {RockBossAnimType::P2_ROLL_DOWN, {{
        {0.20f, rockBossUV[40]},
        {0.20f, rockBossUV[41]},
    }}},
    {RockBossAnimType::P2_ROLL_RIGHT, {{
        {0.20f, rockBossUV[42]},
        {0.20f, rockBossUV[43]},
    }}},
    {RockBossAnimType::P2_ROLL_LEFT, {{
        {0.20f, rockBossUV[44]},
        {0.20f, rockBossUV[45]},
    }}},
    {RockBossAnimType::P2_ROLL_UP, {{
        {0.20f, rockBossUV[46]},
        {0.20f, rockBossUV[47]},
    }}},
});