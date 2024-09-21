#pragma once

#include <Zerengine.hpp>

static const ImageAsset jarUV("Textures/Jar.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Jar No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Jar Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Jar Hit
});

enum class JarAnimType: std::size_t {
    NO_HIT,
    HIT,
    DESTROYED,
};

static const AnimationAsset jarAnim(animEnum<JarAnimType>, {
    {JarAnimType::NO_HIT, {{
        {1.00f, jarUV[0]},
    }, AnimationType::ONE_SHOT}},
    {JarAnimType::HIT, {{
        {1.00f, jarUV[2]},
    }, AnimationType::ONE_SHOT}},
    {JarAnimType::DESTROYED, {{
        {1.00f, jarUV[1]},
    }, AnimationType::ONE_SHOT}},
});