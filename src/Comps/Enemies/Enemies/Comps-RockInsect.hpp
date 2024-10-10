#pragma once

#include <Zerengine.hpp>

class RockInsect final: public IComponent {
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

class IsRockInsectMove final: public IComponent, public IIsStateDuration {
public:
    IsRockInsectMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsRockInsectPreCast final: public IComponent, public IIsStateDuration {
public:
    IsRockInsectPreCast(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsRockInsectCast final: public IComponent, public IIsStateDuration {
public:
    IsRockInsectCast(float newDuration):
        IIsStateDuration(newDuration) {
    }
};