#pragma once

#include <Zerengine.hpp>

class LavaSlime final {
public:
    LavaSlime(float newMoveDuration, float newPreAttackDuration):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration) {
    }

public:
    const float moveDuration;
    const float preAttackDuration;
};

class IsLavaSlimeMove final: public IIsStateDuration {
public:
    IsLavaSlimeMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsLavaSlimePreAttack final: public IIsStateDuration {
public:
    IsLavaSlimePreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};