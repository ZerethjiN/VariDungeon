#pragma once

#include <Zerengine.hpp>

class PlayerLifeText {};
class PlayerLifeBarInner {
public:
    PlayerLifeBarInner(float newMaxLength):
        maxLength(newMaxLength) {
    }

    float getMaxLength() const {
        return maxLength;
    }

private:
    const float maxLength;
};