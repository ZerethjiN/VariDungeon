#pragma once

#include <Zerengine.hpp>

class Roboboule final: public IComponent {
public:
    Roboboule(float newPreAttackDuration, float newPreAttackRadius):
        preAttackDuration(newPreAttackDuration),
        preAttackRadius(newPreAttackRadius) {
    }

public:
    const float preAttackDuration;
    const float preAttackRadius;
};

class IsRobobouleMove final: public IComponent {};

class IsRoboboulePreAttack final: public IComponent, public IIsStateDuration {
public:
    IsRoboboulePreAttack(float newDuration):
        IIsStateDuration(newDuration) {
    }
};