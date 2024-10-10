#pragma once

#include <Zerengine.hpp>

class VoidSlime final: public IComponent {
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

class IsVoidSlimeMove final: public IComponent, public IIsStateDuration {
public:
    IsVoidSlimeMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsVoidSlimeAttract final: public IComponent, public IIsStateDuration {
public:
    IsVoidSlimeAttract(float newDuration):
        IIsStateDuration(newDuration) {
    }
};