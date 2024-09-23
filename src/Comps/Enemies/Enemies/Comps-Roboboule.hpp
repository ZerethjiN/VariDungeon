#pragma once

#include <Zerengine.hpp>

class Roboboule final {
public:
    Roboboule(float newPreAttackDuration, float newPreAttackRadius):
        preAttackDuration(newPreAttackDuration),
        preAttackRadius(newPreAttackRadius) {
    }

public:
    const float preAttackDuration;
    const float preAttackRadius;
};

class IsRobobouleMove final {};

class IsRoboboulePreAttack final: public IIsStateDuration {
public:
    IsRoboboulePreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};