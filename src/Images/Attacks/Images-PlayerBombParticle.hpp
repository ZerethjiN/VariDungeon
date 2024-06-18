#pragma once

#include <Zerengine.hpp>

static const ImageAsset playerBombUV("Textures/Bomb.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Bomb Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Bomb Particle B
});

static const AnimationAsset playerBombAnim({
    {"Default", {
        {0.2f, playerBombUV[0]},
        {0.2f, playerBombUV[1]},
    }},
});