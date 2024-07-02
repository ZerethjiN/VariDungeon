#pragma once

#include <glm/glm.hpp>

class PointLight final {
public:
    PointLight(const glm::vec4& newColor, float newRadius, float newIntensity):
        color(newColor),
        radius(newRadius),
        intensity(newIntensity) {
    }

public:
    glm::vec4 color;
    float radius;
    float intensity;
};

class AmbientLight final {
public:
    AmbientLight(const glm::vec4& newColor):
        color(newColor) {
    }

public:
    glm::vec4 color;
};