#pragma once

#include <Zerengine.hpp>

class VoidSphere final: public IComponent {
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

class IsVoidSphereOff final: public IComponent {
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

class IsVoidSphereOn final: public IComponent {
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