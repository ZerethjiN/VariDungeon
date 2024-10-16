#pragma once

#include <Zerengine.hpp>

static const ImageAsset sphereUV("Textures/Sphere.png", {
    {{  0,   0, 32, 48}, {0.5f, 0.5f}}, //  0: Sphere A
    {{ 32,   0, 32, 48}, {0.5f, 0.5f}}, //  1: Sphere B
});

enum class SphereAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset sphereAnim(animEnum<SphereAnimType>, {
    {SphereAnimType::DEFAULT, {{
        {1.00f, sphereUV[0]},
        {1.00f, sphereUV[1]},
    }}},
});