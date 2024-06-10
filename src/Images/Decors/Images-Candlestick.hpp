#pragma once

#include <Zerengine.hpp>

static const ImageAsset candlestickUV("Textures/Candlestick.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Candlestick A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Candlestick B
});

static const AnimationAsset candlestickAnim({
    {"Default", {
        {0.50f, candlestickUV[0]},
        {0.50f, candlestickUV[1]},
    }},
});