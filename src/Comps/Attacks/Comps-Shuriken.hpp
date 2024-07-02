#pragma once

#include <Zerengine.hpp>

class Shuriken final {
public:
    Shuriken(float newRotationSpeed, const glm::vec2& newOffset):
        rotationSpeed(newRotationSpeed),
        offset(newOffset) {
    }

    float getRotationSpeed() const {
        return rotationSpeed;
    }

    const glm::vec2& getOffset() const {
        return offset;
    }

private:
    const float rotationSpeed;
    const glm::vec2 offset;
};