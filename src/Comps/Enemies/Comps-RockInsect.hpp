#pragma once

#include <Zerengine.hpp>

class RockInsect {
public:
    RockInsect(float newMoveDuration, float newPreCastDuration, float newCastDuration):
        moveDuration(newMoveDuration),
        preCastDuration(newPreCastDuration),
        castDuration(newCastDuration) {
    }

public:
    const float moveDuration;
    const float preCastDuration;
    const float castDuration;
};

class IsRockInsectMove {
public:
    IsRockInsectMove(float newDuration):
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

class IsRockInsectPreCast {
public:
    IsRockInsectPreCast(float newDuration):
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

class IsRockInsectCast {
public:
    IsRockInsectCast(float newDuration):
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