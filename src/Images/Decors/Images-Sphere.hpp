#pragma once

#include <Zerengine.hpp>

static const ImageAsset sphereUV("Textures/Sphere.png", {
    {{  0,   0, 32, 48}, {0.5f, 0.5f}}, //  0: Sphere A
    {{ 32,   0, 32, 48}, {0.5f, 0.5f}}, //  1: Sphere B
});

static const AnimationAsset sphereAnim({
    {"Default", {
        {1.00f, sphereUV[0]},
        {1.00f, sphereUV[1]},
    }},
});