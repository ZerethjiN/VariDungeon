#pragma once

#include <Zerengine.hpp>

class PlayerLifeText final {};
class PlayerLifeBarInner final {
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