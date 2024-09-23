#pragma once

#include <Zerengine.hpp>

class Mummy final {
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

class IsMummyMove final: public IIsStateDuration {
public:
    IsMummyMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsMummyPreAttack final: public IIsStateDuration {
public:
    IsMummyPreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsMummyAttack final: public IIsStateDuration {
public:
    IsMummyAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};