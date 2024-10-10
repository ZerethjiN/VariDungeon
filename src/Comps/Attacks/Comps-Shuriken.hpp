#pragma once

#include <Zerengine.hpp>

class Shuriken final: public IComponent {
public:
    Shuriken(float newRotationSpeed, const glm::vec2& newOffset):
        rotationSpeed(newRotationSpeed),
        offset(newOffset) {
    }

public:
    const float rotationSpeed;
    const glm::vec2 offset;
};