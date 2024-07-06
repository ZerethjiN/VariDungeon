#pragma once

#include <Zerengine.hpp>

class FireBall final {
public:
    FireBall(const glm::vec2& newDirection):
        direction(newDirection) {
    }

public:
    const glm::vec2 direction;
};