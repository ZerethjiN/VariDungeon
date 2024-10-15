#pragma once

#include <Zerengine.hpp>

static const ImageAsset spikeUV("Textures/Spike.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Spike A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Spike B
});

enum class SpikeAnimType: std::size_t {
    DOWN,
    UP,
};

static const AnimationAsset spikeAnim(animEnum<SpikeAnimType>, {
    {SpikeAnimType::DOWN, {{
        {1.00f, spikeUV[0]},
    }, AnimationType::ONE_SHOT}},
    {SpikeAnimType::UP, {{
        {1.00f, spikeUV[1]},
    }, AnimationType::ONE_SHOT}},
});