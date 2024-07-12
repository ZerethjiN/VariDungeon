#pragma once
#include <Zerengine.hpp>

static const ImageAsset mapAssetUV("Textures/MapAsset.png", {
    {{  0,   0,  8,  8}, {0.5f, 0.5f}}, //  0: Room Unknow
    {{  8,   0,  8,  8}, {0.5f, 0.5f}}, //  1: Room Know
    {{ 16,   0,  8,  8}, {0.5f, 0.5f}}, //  2: Player Room
    {{ 24,   0,  8,  8}, {0.5f, 0.5f}}, //  3: Boss Room
});