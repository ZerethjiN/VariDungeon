#pragma once

#include <Zerengine.hpp>

static const ImageAsset playerBombUV("Textures/Bomb.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Bomb Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Bomb Particle B
});

enum class PlayerBombAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset playerBombAnim(animEnum<PlayerBombAnimType>, {
    {PlayerBombAnimType::DEFAULT, {{
        {0.2f, playerBombUV[0]},
        {0.2f, playerBombUV[1]},
    }}},
});