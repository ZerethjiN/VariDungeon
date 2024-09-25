#pragma once

#include <Zerengine.hpp>

static const ImageAsset bonusSphereUV("Textures/BonusSphere.png", {
    {{  0,  16, 16, 16}, {0.5f, 0.5f}}, //  0: Bonus Sphere A
    {{ 16,  16, 16, 16}, {0.5f, 0.5f}}, //  1: Bonus Sphere B
});

enum class BonusSphereAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset bonusSphereAnim(animEnum<BonusSphereAnimType>, {
    {BonusSphereAnimType::DEFAULT, {{
        {0.50f, bonusSphereUV[0]},
        {0.50f, bonusSphereUV[1]},
    }}},
});