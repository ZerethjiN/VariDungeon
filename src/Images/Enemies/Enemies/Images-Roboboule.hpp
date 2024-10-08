#pragma once

#include <Zerengine.hpp>

static const ImageAsset robobouleUV("Textures/Roboboule.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Roboboule Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Roboboule Move Down B
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Roboboule Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Roboboule Move Right B
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Roboboule Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Roboboule Move Left B
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Roboboule Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Roboboule Move Up B

    // Pre Attacks
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, //  8: Roboboule Pre Attack Down A
    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, //  9: Roboboule Pre Attack Right A
    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 10: Roboboule Pre Attack Left A
    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 11: Roboboule Pre Attack Up A

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, // 12: Roboboule Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, // 13: Roboboule Hit Move Down B
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 14: Roboboule Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 15: Roboboule Hit Move Right B
    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 16: Roboboule Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 17: Roboboule Hit Move Left B
    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 18: Roboboule Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 19: Roboboule Hit Move Up B

    // Hit Pre Attacks
    {{ 32,  64, 16, 16}, {0.5f, 0.5f}}, // 20: Roboboule Hit Pre Attack Down A
    {{ 32,  80, 16, 16}, {0.5f, 0.5f}}, // 21: Roboboule Hit Pre Attack Right A
    {{ 32,  96, 16, 16}, {0.5f, 0.5f}}, // 22: Roboboule Hit Pre Attack Left A
    {{ 32, 112, 16, 16}, {0.5f, 0.5f}}, // 23: Roboboule Hit Pre Attack Up A
});

enum class RobobouleAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    PRE_ATTACK_DOWN,
    PRE_ATTACK_RIGHT,
    PRE_ATTACK_LEFT,
    PRE_ATTACK_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
    HIT_PRE_ATTACK_DOWN,
    HIT_PRE_ATTACK_RIGHT,
    HIT_PRE_ATTACK_LEFT,
    HIT_PRE_ATTACK_UP,
};

static const AnimationAsset robobouleAnim(animEnum<RobobouleAnimType>, {
    // Movements
    {RobobouleAnimType::MOVE_DOWN, {{
        {0.20f, robobouleUV[0]},
        {0.20f, robobouleUV[1]},
    }}},
    {RobobouleAnimType::MOVE_RIGHT, {{
        {0.20f, robobouleUV[2]},
        {0.20f, robobouleUV[3]},
    }}},
    {RobobouleAnimType::MOVE_LEFT, {{
        {0.20f, robobouleUV[4]},
        {0.20f, robobouleUV[5]},
    }}},
    {RobobouleAnimType::MOVE_UP, {{
        {0.20f, robobouleUV[6]},
        {0.20f, robobouleUV[7]},
    }}},

    // Pre Attacks
    {RobobouleAnimType::PRE_ATTACK_DOWN, {{
        {0.20f, robobouleUV[8]},
        {0.20f, robobouleUV[1]},
    }}},
    {RobobouleAnimType::PRE_ATTACK_RIGHT, {{
        {0.20f, robobouleUV[9]},
        {0.20f, robobouleUV[3]},
    }}},
    {RobobouleAnimType::PRE_ATTACK_LEFT, {{
        {0.20f, robobouleUV[10]},
        {0.20f, robobouleUV[5]},
    }}},
    {RobobouleAnimType::PRE_ATTACK_UP, {{
        {0.20f, robobouleUV[11]},
        {0.20f, robobouleUV[7]},
    }}},

    // Hit Movements
    {RobobouleAnimType::HIT_MOVE_DOWN, {{
        {0.20f, robobouleUV[12]},
        {0.20f, robobouleUV[13]},
    }}},
    {RobobouleAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, robobouleUV[14]},
        {0.20f, robobouleUV[15]},
    }}},
    {RobobouleAnimType::HIT_MOVE_LEFT, {{
        {0.20f, robobouleUV[16]},
        {0.20f, robobouleUV[17]},
    }}},
    {RobobouleAnimType::HIT_MOVE_UP, {{
        {0.20f, robobouleUV[18]},
        {0.20f, robobouleUV[19]},
    }}},

    // Hit Pre Attacks
    {RobobouleAnimType::HIT_PRE_ATTACK_DOWN, {{
        {0.20f, robobouleUV[20]},
        {0.20f, robobouleUV[13]},
    }}},
    {RobobouleAnimType::HIT_PRE_ATTACK_RIGHT, {{
        {0.20f, robobouleUV[21]},
        {0.20f, robobouleUV[15]},
    }}},
    {RobobouleAnimType::HIT_PRE_ATTACK_LEFT, {{
        {0.20f, robobouleUV[22]},
        {0.20f, robobouleUV[17]},
    }}},
    {RobobouleAnimType::HIT_PRE_ATTACK_UP, {{
        {0.20f, robobouleUV[23]},
        {0.20f, robobouleUV[19]},
    }}},
});