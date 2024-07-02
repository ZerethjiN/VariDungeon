#pragma once

#include <Zerengine.hpp>

class VoidSlime final {
public:
    VoidSlime(float newMoveDuration, float newAttractDuration, float newAttractRadius, float newAttractStrength):
        moveDuration(newMoveDuration),
        attractDuration(newAttractDuration),
        attractRadius(newAttractRadius),
        attractStrength(newAttractStrength) {
    }

public:
    const float moveDuration;
    const float attractDuration;
    const float attractRadius;
    const float attractStrength;
};

class IsVoidSlimeMove final {
public:
    IsVoidSlimeMove(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};

class IsVoidSlimeAttract final {
public:
    IsVoidSlimeAttract(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};