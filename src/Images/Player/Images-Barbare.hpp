#pragma once

#include <Zerengine.hpp>

static const ImageAsset barbareUV("Textures/Barbare.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Barbare Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Barbare Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Barbare Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Barbare Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Barbare Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Barbare Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Barbare Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Barbare Move Up B

    // Attacks
    {{160,   0, 32, 16}, {0.75f, 0.50f}}, //  8: Barbare Attack Down A
    {{ 96,  32, 32, 32}, {0.75f, 0.25f}}, //  9: Barbare Attack Down B
    {{ 32,   0, 16, 32}, {0.50f, 0.25f}}, // 10: Barbare Attack Down C

    {{192,   0, 16, 32}, {0.50f, 0.75f}}, // 11: Barbare Attack Right A
    {{128,  32, 32, 32}, {0.25f, 0.75f}}, // 12: Barbare Attack Right B
    {{ 48,   0, 32, 16}, {0.25f, 0.50f}}, // 13: Barbare Attack Right C

    {{208,   0, 16, 32}, {0.50f, 0.75f}}, // 14: Barbare Attack Left A
    {{ 96,   0, 32, 32}, {0.75f, 0.75f}}, // 15: Barbare Attack Left B
    {{ 48,  16, 32, 16}, {0.75f, 0.50f}}, // 16: Barbare Attack Left C

    {{160,  16, 32, 16}, {0.25f, 0.50f}}, // 17: Barbare Attack Up A
    {{128,   0, 32, 32}, {0.25f, 0.75f}}, // 18: Barbare Attack Up B
    {{ 80,   0, 16, 32}, {0.50f, 0.75f}}, // 19: Barbare Attack Up C

    // Dashs
    {{ 32,  32, 16, 32}, {0.50f, 0.25f}}, // 20: Barbare Dash Down
    {{ 48,  32, 32, 16}, {0.25f, 0.50f}}, // 21: Barbare Dash Right
    {{ 48,  48, 32, 16}, {0.75f, 0.50f}}, // 22: Barbare Dash Left
    {{ 80,  32, 16, 32}, {0.50f, 0.75f}}, // 23: Barbare Dash Up

    // Hit Movements
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, // 24: Barbare Hit Move Down A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, // 25: Barbare Hit Move Down B

    {{  0,  80, 16, 16}, {0.5f, 0.5f}}, // 26: Barbare Hit Move Right A
    {{ 16,  80, 16, 16}, {0.5f, 0.5f}}, // 27: Barbare Hit Move Right B

    {{  0,  96, 16, 16}, {0.5f, 0.5f}}, // 28: Barbare Hit Move Left A
    {{ 16,  96, 16, 16}, {0.5f, 0.5f}}, // 29: Barbare Hit Move Left B

    {{  0, 112, 16, 16}, {0.5f, 0.5f}}, // 30: Barbare Hit Move Up A
    {{ 16, 112, 16, 16}, {0.5f, 0.5f}}, // 31: Barbare Hit Move Up B

    // Hit Attacks
    {{160,  64, 32, 16}, {0.75f, 0.50f}}, // 32: Barbare Hit Attack Down A
    {{ 96,  96, 32, 32}, {0.75f, 0.25f}}, // 33: Barbare Hit Attack Down B
    {{ 32,  64, 16, 32}, {0.50f, 0.25f}}, // 34: Barbare Hit Attack Down C

    {{192,  64, 16, 32}, {0.50f, 0.75f}}, // 35: Barbare Hit Attack Right A
    {{128,  96, 32, 32}, {0.25f, 0.75f}}, // 36: Barbare Hit Attack Right B
    {{ 48,  64, 32, 16}, {0.25f, 0.50f}}, // 37: Barbare Hit Attack Right C

    {{208,  64, 16, 32}, {0.50f, 0.75f}}, // 38: Barbare Hit Attack Left A
    {{ 96,  64, 32, 32}, {0.75f, 0.75f}}, // 39: Barbare Hit Attack Left B
    {{ 48,  80, 32, 16}, {0.75f, 0.50f}}, // 40: Barbare Hit Attack Left C

    {{160,  80, 32, 16}, {0.25f, 0.50f}}, // 41: Barbare Hit Attack Up A
    {{128,  64, 32, 32}, {0.25f, 0.75f}}, // 42: Barbare Hit Attack Up B
    {{ 80,  64, 16, 32}, {0.50f, 0.75f}}, // 43: Barbare Hit Attack Up C

    // Hit Dashs
    {{ 32,  96, 16, 32}, {0.50f, 0.25f}}, // 44: Barbare Hit Dash Down
    {{ 48,  96, 32, 16}, {0.25f, 0.50f}}, // 45: Barbare Hit Dash Right
    {{ 48, 112, 32, 16}, {0.75f, 0.50f}}, // 46: Barbare Hit Dash Left
    {{ 80,  96, 16, 32}, {0.50f, 0.75f}}, // 47: Barbare Hit Dash Up

    // Persistence Dark
    {{160,  32, 16, 32}, {0.50f, 0.25f}}, // 48: Barbare Hit Dash Down
    {{176,  32, 32, 16}, {0.25f, 0.50f}}, // 49: Barbare Hit Dash Right
    {{176,  48, 32, 16}, {0.75f, 0.50f}}, // 50: Barbare Hit Dash Left
    {{208,  32, 16, 32}, {0.50f, 0.75f}}, // 51: Barbare Hit Dash Up

    // Persistence Light
    {{224,  32, 16, 32}, {0.50f, 0.25f}}, // 52: Barbare Hit Dash Down
    {{240,  32, 32, 16}, {0.25f, 0.50f}}, // 53: Barbare Hit Dash Right
    {{240,  48, 32, 16}, {0.75f, 0.50f}}, // 54: Barbare Hit Dash Left
    {{272,  32, 16, 32}, {0.50f, 0.75f}}, // 55: Barbare Hit Dash Up

    // Dead
    {{224,   0, 16, 16}, {0.50f, 0.50f}}, // 56: Barbare Dead

    // Hit Dead
    {{224,  64, 16, 16}, {0.50f, 0.50f}}, // 57: Barbare Hit Dead
});

enum class BarbareAnimType: std::size_t {
    IDLE_DOWN,
    IDLE_RIGHT,
    IDLE_LEFT,
    IDLE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    ATTACK_DOWN,
    ATTACK_RIGHT,
    ATTACK_LEFT,
    ATTACK_UP,
    DASH_DOWN,
    DASH_RIGHT,
    DASH_LEFT,
    DASH_UP,
    HIT_IDLE_DOWN,
    HIT_IDLE_RIGHT,
    HIT_IDLE_LEFT,
    HIT_IDLE_UP,
    HIT_MOVE_DOWN,
    HIT_MOVE_RIGHT,
    HIT_MOVE_LEFT,
    HIT_MOVE_UP,
    HIT_ATTACK_DOWN,
    HIT_ATTACK_RIGHT,
    HIT_ATTACK_LEFT,
    HIT_ATTACK_UP,
    HIT_DASH_DOWN,
    HIT_DASH_RIGHT,
    HIT_DASH_LEFT,
    HIT_DASH_UP,
    PERSISTENCE_DOWN,
    PERSISTENCE_RIGHT,
    PERSISTENCE_LEFT,
    PERSISTENCE_UP,
    DEAD,
    HIT_DEAD,
};

static const AnimationAsset barbareAnim(animEnum<BarbareAnimType>, {
    // Idles
    {BarbareAnimType::IDLE_DOWN, {{
        {1.00f, barbareUV[0]},
    }}},
    {BarbareAnimType::IDLE_RIGHT, {{
        {1.00f, barbareUV[2]},
    }}},
    {BarbareAnimType::IDLE_LEFT, {{
        {1.00f, barbareUV[4]},
    }}},
    {BarbareAnimType::IDLE_UP, {{
        {1.00f, barbareUV[6]},
    }}},

    // Movements
    {BarbareAnimType::MOVE_DOWN, {{
        {0.20f, barbareUV[0]},
        {0.20f, barbareUV[1]},
    }}},
    {BarbareAnimType::MOVE_RIGHT, {{
        {0.20f, barbareUV[2]},
        {0.20f, barbareUV[3]},
    }}},
    {BarbareAnimType::MOVE_LEFT, {{
        {0.20f, barbareUV[4]},
        {0.20f, barbareUV[5]},
    }}},
    {BarbareAnimType::MOVE_UP, {{
        {0.20f, barbareUV[6]},
        {0.20f, barbareUV[7]},
    }}},

    // Attacks
    {BarbareAnimType::ATTACK_DOWN, {{
        {0.025f, barbareUV[8]},
        {0.10f, barbareUV[9]},
        {0.025f, barbareUV[10]},
        {1.00f, barbareUV[0]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::ATTACK_RIGHT, {{
        {0.025f, barbareUV[11]},
        {0.10f, barbareUV[12]},
        {0.025f, barbareUV[13]},
        {1.00f, barbareUV[2]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::ATTACK_LEFT, {{
        {0.025f, barbareUV[14]},
        {0.10f, barbareUV[15]},
        {0.025f, barbareUV[16]},
        {1.00f, barbareUV[4]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::ATTACK_UP, {{
        {0.025f, barbareUV[17]},
        {0.10f, barbareUV[18]},
        {0.025f, barbareUV[19]},
        {1.00f, barbareUV[6]},
    }, AnimationType::ONE_SHOT}},

    // Dashs
    {BarbareAnimType::DASH_DOWN, {{
        {1.00f, barbareUV[20]},
    }}},
    {BarbareAnimType::DASH_RIGHT, {{
        {1.00f, barbareUV[21]},
    }}},
    {BarbareAnimType::DASH_LEFT, {{
        {1.00f, barbareUV[22]},
    }}},
    {BarbareAnimType::DASH_UP, {{
        {1.00f, barbareUV[23]},
    }}},





    // Hit Idles
    {BarbareAnimType::HIT_IDLE_DOWN, {{
        {1.00f, barbareUV[24]},
    }}},
    {BarbareAnimType::HIT_IDLE_RIGHT, {{
        {1.00f, barbareUV[26]},
    }}},
    {BarbareAnimType::HIT_IDLE_LEFT, {{
        {1.00f, barbareUV[28]},
    }}},
    {BarbareAnimType::HIT_IDLE_UP, {{
        {1.00f, barbareUV[30]},
    }}},

    // Hit Movements
    {BarbareAnimType::HIT_MOVE_DOWN, {{
        {0.20f, barbareUV[24]},
        {0.20f, barbareUV[25]},
    }}},
    {BarbareAnimType::HIT_MOVE_RIGHT, {{
        {0.20f, barbareUV[26]},
        {0.20f, barbareUV[27]},
    }}},
    {BarbareAnimType::HIT_MOVE_LEFT, {{
        {0.20f, barbareUV[28]},
        {0.20f, barbareUV[29]},
    }}},
    {BarbareAnimType::HIT_MOVE_UP, {{
        {0.20f, barbareUV[30]},
        {0.20f, barbareUV[31]},
    }}},

    // Hit Attacks
    {BarbareAnimType::HIT_ATTACK_DOWN, {{
        {0.025f, barbareUV[32]},
        {0.10f, barbareUV[33]},
        {0.025f, barbareUV[34]},
        {1.00f, barbareUV[24]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::HIT_ATTACK_RIGHT, {{
        {0.025f, barbareUV[35]},
        {0.10f, barbareUV[36]},
        {0.025f, barbareUV[37]},
        {1.00f, barbareUV[26]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::HIT_ATTACK_LEFT, {{
        {0.025f, barbareUV[38]},
        {0.10f, barbareUV[39]},
        {0.025f, barbareUV[40]},
        {1.00f, barbareUV[28]},
    }, AnimationType::ONE_SHOT}},
    {BarbareAnimType::HIT_ATTACK_UP, {{
        {0.025f, barbareUV[41]},
        {0.10f, barbareUV[42]},
        {0.025f, barbareUV[43]},
        {1.00f, barbareUV[30]},
    }, AnimationType::ONE_SHOT}},

    // Hit Dashs
    {BarbareAnimType::HIT_DASH_DOWN, {{
        {1.00f, barbareUV[44]},
    }}},
    {BarbareAnimType::HIT_DASH_RIGHT, {{
        {1.00f, barbareUV[45]},
    }}},
    {BarbareAnimType::HIT_DASH_LEFT, {{
        {1.00f, barbareUV[46]},
    }}},
    {BarbareAnimType::HIT_DASH_UP, {{
        {1.00f, barbareUV[47]},
    }}},

    // Persistence
    {BarbareAnimType::PERSISTENCE_DOWN, {{
        {0.15f, barbareUV[48]},
        {0.15f, barbareUV[52]},
    }}},
    {BarbareAnimType::PERSISTENCE_RIGHT, {{
        {0.15f, barbareUV[49]},
        {0.15f, barbareUV[53]},
    }}},
    {BarbareAnimType::PERSISTENCE_LEFT, {{
        {0.15f, barbareUV[50]},
        {0.15f, barbareUV[54]},
    }}},
    {BarbareAnimType::PERSISTENCE_UP, {{
        {0.15f, barbareUV[51]},
        {0.15f, barbareUV[55]},
    }}},

    // Dead
    {BarbareAnimType::DEAD, {{
        {1.00f, barbareUV[56]},
    }, AnimationType::ONE_SHOT}},

    // Hit Dead
    {BarbareAnimType::HIT_DEAD, {{
        {1.00f, barbareUV[57]},
    }, AnimationType::ONE_SHOT}},
});