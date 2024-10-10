#pragma once

#include <Zerengine.hpp>

class Mummy final: public IComponent {
public:
    Mummy(float newMoveDuration, float newPreAttackDuration, float newAttackDuration, float newAttackRadius):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration),
        attackDuration(newAttackDuration),
        attackRadius(newAttackRadius) {
    }

public:
    const float moveDuration;
    const float preAttackDuration;
    const float attackDuration;
    const float attackRadius;
};

class IsMummyMove final: public IComponent, public IIsStateDuration {
public:
    IsMummyMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsMummyPreAttack final: public IComponent, public IIsStateDuration {
public:
    IsMummyPreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsMummyAttack final: public IComponent, public IIsStateDuration {
public:
    IsMummyAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};