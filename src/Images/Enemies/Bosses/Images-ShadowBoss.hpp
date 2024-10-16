#pragma once

#include <Zerengine.hpp>

static const ImageAsset shadowBossUV("Textures/ShadowBoss.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Shadow Boss Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Shadow Boss Move Down B
    {{  0,  32, 32, 32}, {0.5f, 0.5f}}, //  2: Shadow Boss Move Right A
    {{ 32,  32, 32, 32}, {0.5f, 0.5f}}, //  3: Shadow Boss Move Right B
    {{  0,  64, 32, 32}, {0.5f, 0.5f}}, //  4: Shadow Boss Move Left A
    {{ 32,  64, 32, 32}, {0.5f, 0.5f}}, //  5: Shadow Boss Move Left B
    {{  0,  96, 32, 32}, {0.5f, 0.5f}}, //  6: Shadow Boss Move Up A
    {{ 32,  96, 32, 32}, {0.5f, 0.5f}}, //  7: Shadow Boss Move Up B

    // Casts
    {{  0, 128, 32, 32}, {0.5f, 0.5f}}, //  8: Shadow Boss Cast Down
    {{  0, 160, 32, 32}, {0.5f, 0.5f}}, //  9: Shadow Boss Cast Right
    {{  0, 192, 32, 32}, {0.5f, 0.5f}}, // 10: Shadow Boss Cast Left
    {{  0, 224, 32, 32}, {0.5f, 0.5f}}, // 11: Shadow Boss Cast Up

    // Vanishs
    {{  0, 256, 32, 32}, {0.5f, 0.5f}}, // 12: Shadow Boss Vanish Down A
    {{ 32, 256, 32, 32}, {0.5f, 0.5f}}, // 13: Shadow Boss Vanish Down B
    {{  0, 288, 32, 32}, {0.5f, 0.5f}}, // 14: Shadow Boss Vanish Right A
    {{ 32, 288, 32, 32}, {0.5f, 0.5f}}, // 15: Shadow Boss Vanish Right B
    {{  0, 320, 32, 32}, {0.5f, 0.5f}}, // 16: Shadow Boss Vanish Left A
    {{ 32, 320, 32, 32}, {0.5f, 0.5f}}, // 17: Shadow Boss Vanish Left B
    {{  0, 352, 32, 32}, {0.5f, 0.5f}}, // 18: Shadow Boss Vanish Up A
    {{ 32, 352, 32, 32}, {0.5f, 0.5f}}, // 19: Shadow Boss Vanish Up B

    // Hits
    {{ 64,   0, 32, 32}, {0.5f, 0.5f}}, // 20: Shadow Boss Hit Down A
    {{ 96,   0, 32, 32}, {0.5f, 0.5f}}, // 21: Shadow Boss Hit Down B
    {{ 64,  32, 32, 32}, {0.5f, 0.5f}}, // 22: Shadow Boss Hit Right A
    {{ 96,  32, 32, 32}, {0.5f, 0.5f}}, // 23: Shadow Boss Hit Right B
    {{ 64,  64, 32, 32}, {0.5f, 0.5f}}, // 24: Shadow Boss Hit Left A
    {{ 96,  64, 32, 32}, {0.5f, 0.5f}}, // 25: Shadow Boss Hit Left B
    {{ 64,  96, 32, 32}, {0.5f, 0.5f}}, // 26: Shadow Boss Hit Up A
    {{ 96,  96, 32, 32}, {0.5f, 0.5f}}, // 27: Shadow Boss Hit Up B

    // Transparency
    {{ 64, 256, 32, 32}, {0.5f, 0.5f}}, // 28: Shadow Boss Vanish Full
});

enum class ShadowBossAnimType: std::size_t {
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    CAST_DOWN,
    CAST_RIGHT,
    CAST_LEFT,
    CAST_UP,
    VANISH_DOWN,
    VANISH_RIGHT,
    VANISH_LEFT,
    VANISH_UP,
    HIT_DOWN,
    HIT_RIGHT,
    HIT_LEFT,
    HIT_UP,
};

static const AnimationAsset shadowBossAnim(animEnum<ShadowBossAnimType>, {
    // Movements
    {ShadowBossAnimType::MOVE_DOWN, {{
        {0.20f, shadowBossUV[0]},
        {0.20f, shadowBossUV[1]},
    }}},
    {ShadowBossAnimType::MOVE_RIGHT, {{
        {0.20f, shadowBossUV[2]},
        {0.20f, shadowBossUV[3]},
    }}},
    {ShadowBossAnimType::MOVE_LEFT, {{
        {0.20f, shadowBossUV[4]},
        {0.20f, shadowBossUV[5]},
    }}},
    {ShadowBossAnimType::MOVE_UP, {{
        {0.20f, shadowBossUV[6]},
        {0.20f, shadowBossUV[7]},
    }}},

    // Casts
    {ShadowBossAnimType::CAST_DOWN, {{
        {0.20f, shadowBossUV[8]},
        {0.20f, shadowBossUV[1]},
    }}},
    {ShadowBossAnimType::CAST_RIGHT, {{
        {0.20f, shadowBossUV[9]},
        {0.20f, shadowBossUV[3]},
    }}},
    {ShadowBossAnimType::CAST_LEFT, {{
        {0.20f, shadowBossUV[10]},
        {0.20f, shadowBossUV[5]},
    }}},
    {ShadowBossAnimType::CAST_UP, {{
        {0.20f, shadowBossUV[11]},
        {0.20f, shadowBossUV[7]},
    }}},

    // Vanishs
    {ShadowBossAnimType::VANISH_DOWN, {{
        {0.20f, shadowBossUV[12]},
        {0.20f, shadowBossUV[13]},
        {0.20f, shadowBossUV[28]},
    }, AnimationType::ONE_SHOT}},
    {ShadowBossAnimType::VANISH_RIGHT, {{
        {0.20f, shadowBossUV[14]},
        {0.20f, shadowBossUV[15]},
        {0.20f, shadowBossUV[28]},
    }, AnimationType::ONE_SHOT}},
    {ShadowBossAnimType::VANISH_LEFT, {{
        {0.20f, shadowBossUV[16]},
        {0.20f, shadowBossUV[17]},
        {0.20f, shadowBossUV[28]},
    }, AnimationType::ONE_SHOT}},
    {ShadowBossAnimType::VANISH_UP, {{
        {0.20f, shadowBossUV[18]},
        {0.20f, shadowBossUV[19]},
        {0.20f, shadowBossUV[28]},
    }, AnimationType::ONE_SHOT}},

    // Hits
    {ShadowBossAnimType::HIT_DOWN, {{
        {0.20f, shadowBossUV[20]},
        {0.20f, shadowBossUV[21]},
    }}},
    {ShadowBossAnimType::HIT_RIGHT, {{
        {0.20f, shadowBossUV[22]},
        {0.20f, shadowBossUV[23]},
    }}},
    {ShadowBossAnimType::HIT_LEFT, {{
        {0.20f, shadowBossUV[24]},
        {0.20f, shadowBossUV[25]},
    }}},
    {ShadowBossAnimType::HIT_UP, {{
        {0.20f, shadowBossUV[26]},
        {0.20f, shadowBossUV[27]},
    }}},
});