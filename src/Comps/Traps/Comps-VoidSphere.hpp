#pragma once

#include <Zerengine.hpp>

class VoidSphere final {
public:
    VoidSphere(float newVoidSphereOffDuration, float newVoidSphereOnDuration, float newAttractStrength):
        voidSphereOffDuration(newVoidSphereOffDuration),
        voidSphereOnDuration(newVoidSphereOnDuration),
        attractStrength(newAttractStrength) {
    }

public:
    const float voidSphereOffDuration;
    const float voidSphereOnDuration;

    const float attractStrength;
};

class IsVoidSphereOff final {
public:
    IsVoidSphereOff(float newDuration):
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

class IsVoidSphereOn final {
public:
    IsVoidSphereOn(float newDuration):
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