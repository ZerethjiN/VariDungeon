#pragma once

#include <Zerengine.hpp>

static const ImageAsset jarUV("Textures/Jar.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Jar No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Jar Destroy
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Jar Hit
});

static const AnimationAsset jarAnim({
    {"NoHit", {
        {1.00f, jarUV[0]},
    }},
    {"Hit", {
        {1.00f, jarUV[2]},
    }},
});