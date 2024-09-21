#pragma once

#include <Zerengine.hpp>

static const ImageAsset crystalUV("Textures/GroundCrystal.png", {
    {{  0,   0, 16, 16}, {0.5f, 0.5f}}, //  0: Crystal No Hit
    {{ 16,   0, 16, 16}, {0.5f, 0.5f}}, //  1: Crystal Destroyed
    {{ 32,   0, 16, 16}, {0.5f, 0.5f}}, //  2: Crystal Hit
});

enum class CrystalAnimType: std::size_t {
    NO_HIT,
    HIT,
    DESTROYED,
};

static const AnimationAsset crystalAnim(animEnum<CrystalAnimType>, {
    {CrystalAnimType::NO_HIT, {{
        {1.00f, crystalUV[0]},
    }, AnimationType::ONE_SHOT}},
    {CrystalAnimType::HIT, {{
        {1.00f, crystalUV[2]},
    }, AnimationType::ONE_SHOT}},
    {CrystalAnimType::DESTROYED, {{
        {1.00f, crystalUV[1]},
    }, AnimationType::ONE_SHOT}},
});