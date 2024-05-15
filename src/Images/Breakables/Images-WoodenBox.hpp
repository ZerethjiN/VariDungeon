#pragma once

#include <Zerengine.hpp>

static const ImageAsset woodenBoxUV("Textures/WoodenBox.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Wooden Box No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Wooden Box Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Wooden Box Hit
});

static const AnimationAsset woodenBoxAnim({
    {"NoHit", {{
        {1.00f, woodenBoxUV[0]},
    }, AnimationType::ONE_SHOT}},
    {"Hit", {{
        {1.00f, woodenBoxUV[2]},
    }, AnimationType::ONE_SHOT}},
    {"Destroyed", {{
        {1.00f, woodenBoxUV[1]},
    }, AnimationType::ONE_SHOT}},
});