#pragma once

#include <Zerengine.hpp>

class CoinIconInventoryBar final {};
class XpIconInventoryBar final {};
class ButtonAIconInventoryBar final  {};
class ButtonBIconInventoryBar final {};

class ShrinkIcon final {
public:
    ShrinkIcon(const glm::vec2& newShrink, float newDuration):
        shrink(newShrink),
        duration(newDuration),
        curTime(0) {
    }

    bool canUnshrink(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    const glm::vec2& getShrink() const {
        return shrink;
    }

private:
    const glm::vec2 shrink;
    const float duration;
    float curTime;
};