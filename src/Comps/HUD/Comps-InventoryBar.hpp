#pragma once

#include <Zerengine.hpp>

class CoinIconInventoryBar final: public IComponent {};
class LifeIconInventoryBar final: public IComponent {};
class XpIconInventoryBar final: public IComponent {};
class ButtonAIconInventoryBar final: public IComponent  {};
class ButtonBIconInventoryBar final: public IComponent {};

class ShrinkIcon final: public IComponent {
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