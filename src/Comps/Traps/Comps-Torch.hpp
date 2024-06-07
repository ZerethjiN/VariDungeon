#pragma once

#include <Zerengine.hpp>

class Torch {
public:
    Torch(float newIdleDuration, float newCastDuration):
        idleDuration(newIdleDuration),
        castDuration(newCastDuration) {
    }

public:
    const float idleDuration;
    const float castDuration;
};

class IsTorchIdle {
public:
    IsTorchIdle(float newDuration):
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

class IsTorchCast {
public:
    IsTorchCast(float newDuration):
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