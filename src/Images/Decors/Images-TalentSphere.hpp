#pragma once

#include <Zerengine.hpp>

static const ImageAsset talentSphereUV("Textures/TalentSphere.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Talent Sphere A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Talent Sphere B
});

enum class TalentSphereAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset talentSphereAnim(animEnum<TalentSphereAnimType>, {
    {TalentSphereAnimType::DEFAULT, {{
        {1.00f, talentSphereUV[0]},
        {1.00f, talentSphereUV[1]},
    }}},
});