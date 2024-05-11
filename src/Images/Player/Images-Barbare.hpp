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
});

static const AnimationAsset barbareAnim({
    // Idles
    {"IdleDown", {
        {1.00f, barbareUV[0]},
    }},
    {"IdleRight", {
        {1.00f, barbareUV[2]},
    }},
    {"IdleLeft", {
        {1.00f, barbareUV[4]},
    }},
    {"IdleUp", {
        {1.00f, barbareUV[6]},
    }},

    // Movements
    {"MoveDown", {
        {0.20f, barbareUV[0]},
        {0.20f, barbareUV[1]},
    }},
    {"MoveRight", {
        {0.20f, barbareUV[2]},
        {0.20f, barbareUV[3]},
    }},
    {"MoveLeft", {
        {0.20f, barbareUV[4]},
        {0.20f, barbareUV[5]},
    }},
    {"MoveUp", {
        {0.20f, barbareUV[6]},
        {0.20f, barbareUV[7]},
    }},

    // Attacks
    {"AttackDown", {
        {0.05f, barbareUV[8]},
        {0.10f, barbareUV[9]},
        {0.05f, barbareUV[10]},
    }},
    {"AttackRight", {
        {0.05f, barbareUV[11]},
        {0.10f, barbareUV[12]},
        {0.05f, barbareUV[13]},
    }},
    {"AttackLeft", {
        {0.05f, barbareUV[14]},
        {0.10f, barbareUV[15]},
        {0.05f, barbareUV[16]},
    }},
    {"AttackUp", {
        {0.05f, barbareUV[17]},
        {0.10f, barbareUV[18]},
        {0.05f, barbareUV[19]},
    }},

    // Dashs
    {"DashDown", {
        {1.00f, barbareUV[20]},
    }},
    {"DashRight", {
        {1.00f, barbareUV[21]},
    }},
    {"DashLeft", {
        {1.00f, barbareUV[22]},
    }},
    {"DashUp", {
        {1.00f, barbareUV[23]},
    }},
});