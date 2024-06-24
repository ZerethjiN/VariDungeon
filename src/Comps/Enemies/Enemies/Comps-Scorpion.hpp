#pragma once

#include <Zerengine.hpp>

class Scorpion {
public:
    Scorpion(float newMoveDuration, float newCastDuration):
        moveDuration(newMoveDuration),
        castDuration(newCastDuration) {
    }

public:
    const float moveDuration;
    const float castDuration;
};

class IsScorpionMove {
public:
    IsScorpionMove(float newDuration):
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

class IsScorpionCast {
public:
    IsScorpionCast(float newDuration):
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