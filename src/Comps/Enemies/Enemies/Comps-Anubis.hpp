#pragma once

#include <Zerengine.hpp>

class Anubis final: public IComponent {
public:
    Anubis(float newMoveDuration, float newAttackDuration):
        moveDuration(newMoveDuration),
        attackDuration(newAttackDuration) {
    }

public:
    const float moveDuration;
    const float attackDuration;
};

class IsAnubisMove final: public IComponent, public IIsStateDuration {
public:
    IsAnubisMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsAnubisAttack final: public IComponent, public IIsStateDuration {
public:
    IsAnubisAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};