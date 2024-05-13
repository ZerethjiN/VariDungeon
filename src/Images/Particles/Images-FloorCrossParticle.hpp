#pragma once

#include <Zerengine.hpp>

static const ImageAsset floorCrossParticleUV("Textures/FloorCrossParticle.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Floor Cross Particle A
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Floor Cross Particle B
});

static const AnimationAsset floorCrossParticleAnim({
    {"Default", {
        {0.25f, floorCrossParticleUV[0]},
        {0.25f, floorCrossParticleUV[1]},
    }},
});