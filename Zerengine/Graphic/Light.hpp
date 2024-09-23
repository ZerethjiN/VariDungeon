#pragma once

#include <glm/glm.hpp>
#include "Graphic/Common.hpp"

class PointLight final {
public:
    PointLight(const Color& newColor, float newRadius, float newIntensity):
        color(newColor),
        radius(newRadius),
        intensity(newIntensity) {
    }

public:
    Color color;
    float radius;
    float intensity;
};

class AmbientLight final {
public:
    AmbientLight(const Color& newColor):
        color(newColor) {
    }

public:
    Color color;
};