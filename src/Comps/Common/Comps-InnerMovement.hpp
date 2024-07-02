#pragma once

#include <Zerengine.hpp>

class InnerMovement final {
public:
    InnerMovement(float newDuration, float newSpeed):
        duration(newDuration),
        curTime(0),
        speed(newSpeed) {
    }

    bool canChangeDirection(float delta) {
        curTime += delta;
        if (curTime >= duration) {
            curTime -= duration;
            return true;
        }
        return false;
    }

    float getSpeed() const {
        return speed;
    }

private:
    const float duration;
    float curTime;
    const float speed;
};

class InnerMovementDown final {};
class InnerMovementUp final {};