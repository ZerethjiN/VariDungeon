#pragma once

#include <Zerengine.hpp>

static const ImageAsset gameOverUV("Textures/GameOver.png", {
    {{  0,   0, 64, 48}, {0.5f, 0.5f}}, //  0: Game Over Text A
    {{ 64,   0, 64, 48}, {0.5f, 0.5f}}, //  1: Game Over Text B
    {{128,   0, 64, 48}, {0.5f, 0.5f}}, //  2: Game Over Text C
});

enum class GameOverAnimType: std::size_t {
    DEFAULT,
};

static const AnimationAsset gameOverAnim(animEnum<GameOverAnimType>, {
    {GameOverAnimType::DEFAULT, {{
        {0.50f, gameOverUV[0]},
        {0.50f, gameOverUV[1]},
        {0.50f, gameOverUV[2]},
    }}},
});