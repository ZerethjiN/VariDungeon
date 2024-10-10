#pragma once

#include <Zerengine.hpp>

class LavaSlime final: public IComponent {
public:
    LavaSlime(float newMoveDuration, float newPreAttackDuration):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration) {
    }

public:
    const float moveDuration;
    const float preAttackDuration;
};

class IsLavaSlimeMove final: public IComponent, public IIsStateDuration {
public:
    IsLavaSlimeMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsLavaSlimePreAttack final: public IComponent, public IIsStateDuration {
public:
    IsLavaSlimePreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};