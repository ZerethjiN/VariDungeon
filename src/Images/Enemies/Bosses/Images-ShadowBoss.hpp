#pragma once

#include <Zerengine.hpp>

static const ImageAsset shadowBossUV("Textures/ShadowBoss.png", {
    // Movements
    {{  0,   0, 32, 32}, {0.5f, 0.5f}}, //  0: Shadow Boss Move Down A
    {{ 32,   0, 32, 32}, {0.5f, 0.5f}}, //  1: Shadow Boss Move Down B
});
    
static const AnimationAsset shadowBossAnim({
    // Movements
    {"MoveDown", {
        {0.20f, shadowBossUV[0]},
        {0.20f, shadowBossUV[1]},
    }},
});