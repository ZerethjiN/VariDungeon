#pragma once

#include <Zerengine.hpp>

class Bat final: public IComponent {
public:
    Bat(float newMoveDuration, float newAttackDuration, float newAttackRadius):
        moveDuration(newMoveDuration),
        attackDuration(newAttackDuration),
        attackRadius(newAttackRadius) {
    }

public:
    const float moveDuration;
    const float attackDuration;
    const float attackRadius;
};

class IsBatMove final: public IComponent, public IIsStateDuration {
public:
    IsBatMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsBatAttack final: public IComponent, public IIsStateDuration {
public:
    IsBatAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};