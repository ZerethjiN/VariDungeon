#pragma once

#include <Zerengine.hpp>

static const ImageAsset turretUV("Textures/Turret.png", {
    {{  0,   0, 16, 32}, {0.5f, 0.5f}}, //  0: Turret Cardinal A
    {{ 16,   0, 16, 32}, {0.5f, 0.5f}}, //  1: Turret Cardinal B

    {{  0,  32, 16, 32}, {0.5f, 0.5f}}, //  2: Turret Diagonal A
    {{ 16,  32, 16, 32}, {0.5f, 0.5f}}, //  3: Turret Diagonal B

    {{  0,  64, 16, 32}, {0.5f, 0.5f}}, //  4: Turret Off
});

static const AnimationAsset turretAnim({
    {"TurretCardinal", {
        {1.00f, turretUV[0]},
        {1.00f, turretUV[1]},
    }},
    {"TurretDiagonal", {
        {1.00f, turretUV[2]},
        {1.00f, turretUV[3]},
    }},
    {"TurretOff", {{
        {1.00f, turretUV[4]},
    }, AnimationType::ONE_SHOT}},
});