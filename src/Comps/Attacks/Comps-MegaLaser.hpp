#pragma once

#include <Zerengine.hpp>

class MegaLaser final {
public:
    MegaLaser(float newRotationSpeed):
        rotationSpeed(newRotationSpeed) {
    }

public:
    const float rotationSpeed;
};