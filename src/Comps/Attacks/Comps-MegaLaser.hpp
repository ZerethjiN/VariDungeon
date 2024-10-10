#pragma once

#include <Zerengine.hpp>

class MegaLaser final: public IComponent {
public:
    MegaLaser(float newRotationSpeed):
        rotationSpeed(newRotationSpeed) {
    }

public:
    const float rotationSpeed;
};