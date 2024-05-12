#pragma once

#include <Zerengine.hpp>

static const ImageAsset tileMapDesertUV("Textures/TileMapDesert.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Void

    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Floor 1
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Sand 1
    {{ 48,   0, 16, 16}, {0.5f, 0.5f}}, //  3: Sand 2
    {{ 64,   0, 16, 16}, {0.5f, 0.5f}}, //  4: Floor
    {{ 80,   0, 16, 16}, {0.5f, 0.5f}}, //  5: Complexe Floor 1
    {{ 96,   0, 16, 16}, {0.5f, 0.5f}}, //  6: Complexe Floor 2
    {{112,   0, 16, 16}, {0.5f, 0.5f}}, //  7: Wet Floor 1
    {{128,   0, 16, 16}, {0.5f, 0.5f}}, //  8: Wet Floor 2
    {{144,   0, 16, 16}, {0.5f, 0.5f}}, //  9: Stair

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, // 10: Cobble Wall North
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, // 11: Cobble Wall East
    {{ 32,  16, 16, 16}, {0.5f, 0.5f}}, // 12: Cobble Wall South
    {{ 48,  16, 16, 16}, {0.5f, 0.5f}}, // 13: Cobble Wall West
    {{  0,  32, 16, 16}, {0.5f, 0.5f}}, // 14: Cobble Wall Corner North West
    {{ 16,  32, 16, 16}, {0.5f, 0.5f}}, // 15: Cobble Wall Corner North East
    {{  0,  48, 16, 16}, {0.5f, 0.5f}}, // 16: Cobble Wall Corner South West
    {{ 16,  48, 16, 16}, {0.5f, 0.5f}}, // 17: Cobble Wall Corner South East
});