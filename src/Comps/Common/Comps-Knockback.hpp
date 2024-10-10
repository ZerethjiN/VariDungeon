#pragma once

#include <Zerengine.hpp>

class Knockback final: public IComponent {
public:
    Knockback(float newDuration, const glm::vec2& newDirection, float newSpeed):
        duration(newDuration),
        curTime(0),
        direction(newDirection),
        speed(newSpeed) {
    }

    bool canStopKnockback(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

    float getSpeed() const {
        return speed;
    }

    [[nodiscard]] constexpr float getDuration() const noexcept {
        return duration;
    }

    [[nodiscard]] constexpr float getCurTime() const noexcept {
        return curTime;
    }

private:
    const float duration;
    float curTime;
    const glm::vec2 direction;
    const float speed;
};

class UnKnockbackable final: public IComponent {};