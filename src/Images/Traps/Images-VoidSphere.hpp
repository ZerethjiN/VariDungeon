#pragma once

#include <Zerengine.hpp>

static const ImageAsset voidSphereUV("Textures/VoidSphere.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Void Sphere Off A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Void Sphere Off B

    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  2: Void Sphere On A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  3: Void Sphere On B
});

static const AnimationAsset voidSphereAnim({
    {"Off", {
        {0.50f, voidSphereUV[0]},
        {0.50f, voidSphereUV[1]},
    }},
    {"On", {
        {0.50f, voidSphereUV[2]},
        {0.50f, voidSphereUV[3]},
    }},
});