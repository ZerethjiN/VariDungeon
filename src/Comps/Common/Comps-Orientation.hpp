#pragma once

#include <Zerengine.hpp>

class Orientation {
public:
    static constexpr glm::vec2 NORTH = glm::vec2(0, -1);
    static constexpr glm::vec2 SOUTH = glm::vec2(0, 1);
    static constexpr glm::vec2 EAST = glm::vec2(1, 0);
    static constexpr glm::vec2 WEST = glm::vec2(-1, 0);

public:
    Orientation(float x, float y):
        orientation(x, y) {
    }

    Orientation(const glm::vec2& newOrientation):
        orientation(newOrientation) {
    }

    [[nodiscard]] bool operator ==(const glm::vec2& oth) const noexcept {
        return orientation == oth;
    }

    [[nodiscard]] bool operator !=(const glm::vec2& oth) const noexcept {
        return orientation != oth;
    }

    Orientation& operator =(const glm::vec2& newOrientation) noexcept {
        orientation = newOrientation;
        return *this;
    }

public:
    union {
        glm::vec2 orientation;
        struct {
            float x, y;
        };
    };
};

class NoMoveAnimation {};