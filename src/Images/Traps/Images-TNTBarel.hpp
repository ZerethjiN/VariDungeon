#pragma once

#include <Zerengine.hpp>

static const ImageAsset tntBarelUV("Textures/TntBarel.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: TNT Barel No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: TNT Barel Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: TNT Barel Hit
});

static const AnimationAsset tntBarelAnim({
    {"NoHit", {{
        {1.00f, tntBarelUV[0]},
    }, AnimationType::ONE_SHOT}},
    {"Hit", {{
        {1.00f, tntBarelUV[2]},
    }, AnimationType::ONE_SHOT}},
    {"Destroyed", {{
        {1.00f, tntBarelUV[1]},
    }, AnimationType::ONE_SHOT}},
});