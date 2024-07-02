#pragma once

#include <Zerengine.hpp>

class FireBall final {
public:
    FireBall(const glm::vec2& newDirection):
        direction(newDirection) {
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

private:
    const glm::vec2 direction;
};