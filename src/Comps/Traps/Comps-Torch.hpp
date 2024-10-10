#pragma once

#include <Zerengine.hpp>

class TorchDecor final: public IComponent {};

class Torch final: public IComponent  {
public:
    Torch(float newIdleDuration, float newCastDuration):
        idleDuration(newIdleDuration),
        castDuration(newCastDuration) {
    }

public:
    const float idleDuration;
    const float castDuration;
};

class IsTorchIdle final: public IComponent {
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

class IsTorchCast final: public IComponent {
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