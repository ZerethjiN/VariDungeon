#pragma once

#include <Zerengine.hpp>

class Scorpion final: public IComponent {
public:
    Scorpion(float newMoveDuration, float newCastDuration):
        moveDuration(newMoveDuration),
        castDuration(newCastDuration) {
    }

public:
    const float moveDuration;
    const float castDuration;
};

class IsScorpionMove final: public IComponent, public IIsStateDuration {
public:
    IsScorpionMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsScorpionCast final: public IComponent, public IIsStateDuration {
public:
    IsScorpionCast(float newDuration):
        IIsStateDuration(newDuration) {
    }
};