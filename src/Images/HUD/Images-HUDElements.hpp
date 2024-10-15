#pragma once

#include <Zerengine.hpp>

static const ImageAsset HUDElementsUV("Textures/HUDElements.png", {
    {{  0,   8, 56, 8}, {0.0f, 0.0f}}, //  0: Bar Outer
    {{  0,  16, 56, 8}, {0.0f, 0.0f}}, //  1: Bar Inner

    {{  0,   0,  8, 8}, {0.0f, 0.0f}}, //  2: Life Icon
    {{  8,   0,  8, 8}, {0.0f, 0.0f}}, //  3: Shield Icon
    {{ 24,   0,  8, 8}, {0.5f, 0.5f}}, //  4: Xp Icon

    {{ 80,   0, 16, 16}, {0.5f, 0.5f}}, // 5: Coin Icon

    {{ 64,   0,  8, 16}, {0.5f, 0.5f}}, // 6: Key Empty
    {{ 72,   0,  8, 16}, {0.5f, 0.5f}}, // 7: Key Full
});