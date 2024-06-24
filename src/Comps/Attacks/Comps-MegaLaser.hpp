#pragma once

#include <Zerengine.hpp>

class MegaLaser {
public:
    MegaLaser(float newRotationSpeed):
        rotationSpeed(newRotationSpeed) {
    }

public:
    const float rotationSpeed;
};