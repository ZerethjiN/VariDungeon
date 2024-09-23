#pragma once

#include <Zerengine.hpp>

class Insect final {
public:
    Insect(float newMoveDuration, float newDirectionCooldown, float newAttackDuration, float newAttackSpeedCoeff):
        moveDuration(newMoveDuration),
        directionCooldown(newDirectionCooldown),
        attackDuration(newAttackDuration),
        attackSpeedCoeff(newAttackSpeedCoeff) {
    }

public:
    const float moveDuration;
    const float directionCooldown;
    const float attackDuration;
    const float attackSpeedCoeff;
};

class IsInsectChangeDirection final: public IIsTickDuration {
public:
    IsInsectChangeDirection(float newDirectionCooldown):
        IIsTickDuration(newDirectionCooldown) {
    }
};

class IsInsectMove final: public IIsStateDuration {
public:
    IsInsectMove(float newDuration):
        IIsStateDuration(newDuration) {
    }
};

class IsInsectAttack final: public IIsStateDuration {
public:
    IsInsectAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};