#pragma once

#include <Zerengine.hpp>

class Gasterolcan final: public IComponent {
public:
    Gasterolcan(float newMoveDuration, float newPreAttackDuration, float newAttackDuration, float newRollSpeedCoeff):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration),
        attackDuration(newAttackDuration),
        rollSpeedCoeff(newRollSpeedCoeff) {
    }

public:
    const float moveDuration;
    const float preAttackDuration;
    const float attackDuration;
    const float rollSpeedCoeff;
};

class IsGasterolcanMove final: public IComponent, public IIsStateDuration {
public:
    IsGasterolcanMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsGasterolcanPreAttack final: public IComponent, public IIsStateDuration {
public:
    IsGasterolcanPreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsGasterolcanAttack final: public IComponent, public IIsStateDuration {
public:
    IsGasterolcanAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};