#pragma once

#include <Zerengine.hpp>

class InvincibleFrame final: public IComponent {
public:
    InvincibleFrame(float newDuration, const glm::vec2& newScale = glm::vec2(0, 0)):
        duration(newDuration),
        curTime(0),
        scale(newScale) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    const glm::vec2& getScale() const {
        return scale;
    }

private:
    const float duration;
    float curTime;

    glm::vec2 scale;
};

class Unhittable final: public IComponent {};