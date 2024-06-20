#pragma once

#include <Zerengine.hpp>

static const ImageAsset slimeLvl2UV("Textures/SlimeLvl2.png", {
    // Movements
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Slime Lvl2 Move Down A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Slime Lvl2 Move Down B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Slime Lvl2 Move Right A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Slime Lvl2 Move Right B

    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, //  4: Slime Lvl2 Move Left A
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, //  5: Slime Lvl2 Move Left B

    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, //  6: Slime Lvl2 Move Up A
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, //  7: Slime Lvl2 Move Up B

    // Hit Movements
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  8: Slime Lvl2 Hit Move Down A
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  9: Slime Lvl2 Hit Move Down B

    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 10: Slime Lvl2 Hit Move Right A
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 11: Slime Lvl2 Hit Move Right B

    {{ 32,  32, 16, 16}, {0.5f, 0.5f}}, // 12: Slime Lvl2 Hit Move Left A
    {{ 48,  32, 16, 16}, {0.5f, 0.5f}}, // 13: Slime Lvl2 Hit Move Left B

    {{ 32,  48, 16, 16}, {0.5f, 0.5f}}, // 14: Slime Lvl2 Hit Move Up A
    {{ 48,  48, 16, 16}, {0.5f, 0.5f}}, // 15: Slime Lvl2 Hit Move Up B

    // Shadow
    {{  0,  64, 16, 16}, {0.5f, 0.5f}}, // 16: Slime Lvl2 Shadow A
    {{ 16,  64, 16, 16}, {0.5f, 0.5f}}, // 17: Slime Lvl2 Shadow B
});

static const AnimationAsset slimeLvl2Anim({
    // Movements
    {"MoveDown", {
        {0.20f, slimeLvl2UV[0]},
        {0.20f, slimeLvl2UV[1]},
    }},
    {"MoveRight", {
        {0.20f, slimeLvl2UV[2]},
        {0.20f, slimeLvl2UV[3]},
    }},
    {"MoveLeft", {
        {0.20f, slimeLvl2UV[4]},
        {0.20f, slimeLvl2UV[5]},
    }},
    {"MoveUp", {
        {0.20f, slimeLvl2UV[6]},
        {0.20f, slimeLvl2UV[7]},
    }},

    // Hit Movements
    {"HitMoveDown", {
        {0.20f, slimeLvl2UV[8]},
        {0.20f, slimeLvl2UV[9]},
    }},
    {"HitMoveRight", {
        {0.20f, slimeLvl2UV[10]},
        {0.20f, slimeLvl2UV[11]},
    }},
    {"HitMoveLeft", {
        {0.20f, slimeLvl2UV[12]},
        {0.20f, slimeLvl2UV[13]},
    }},
    {"HitMoveUp", {
        {0.20f, slimeLvl2UV[14]},
        {0.20f, slimeLvl2UV[15]},
    }},

    // Shadow
    {"Shadow", {
        {0.50f, slimeLvl2UV[16]},
        {0.50f, slimeLvl2UV[17]},
    }},
});