#pragma once

#include <Zerengine.hpp>

class SmallCrystalRotation final {
public:
    SmallCrystalRotation(float newRotationSpeed, const glm::vec2& newOffset):
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

class SmallCrystalThrow final {
public:
    SmallCrystalThrow(const glm::vec2& newLastPlayerPosition, float newSpeed):
        lastPlayerPosition(newLastPlayerPosition),
        speed(newSpeed) {
    }

public:
    const glm::vec2 lastPlayerPosition;
    const float speed;
};