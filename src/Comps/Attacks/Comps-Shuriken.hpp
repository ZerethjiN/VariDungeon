#pragma once

#include <Zerengine.hpp>

class Shuriken {
public:
    Shuriken(float newRotationSpeed):
        rotationSpeed(newRotationSpeed) {
    }

    float getRotationSpeed() const {
        return rotationSpeed;
    }

private:
    const float rotationSpeed;
};