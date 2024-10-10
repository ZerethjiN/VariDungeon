#pragma once

#include <Zerengine.hpp>

class PlayerLifeText final: public IComponent {};
class PlayerLifeBarInner final: public IComponent {
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