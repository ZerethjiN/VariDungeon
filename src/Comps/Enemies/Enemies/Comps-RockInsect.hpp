#pragma once

#include <Zerengine.hpp>

class RockInsect final {
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

class IsRockInsectMove final: public IIsStateDuration {
public:
    IsRockInsectMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsRockInsectPreCast final: public IIsStateDuration {
public:
    IsRockInsectPreCast(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsRockInsectCast final: public IIsStateDuration {
public:
    IsRockInsectCast(float newDuration):
        IIsStateDuration(newDuration) {
    }
};