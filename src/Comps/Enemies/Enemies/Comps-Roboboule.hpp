#pragma once

#include <Zerengine.hpp>

class Roboboule {
public:
    Roboboule(float newPreAttackDuration, float newPreAttackRadius):
        preAttackDuration(newPreAttackDuration),
        preAttackRadius(newPreAttackRadius) {
    }

    float getPreAttackDuration() const {
        return preAttackDuration;
    }

    float getPreAttackRadius() const {
        return preAttackRadius;
    }

private:
    const float preAttackDuration;
    const float preAttackRadius;
};

class IsRobobouleMove {};

class IsRoboboulePreAttack {
public:
    IsRoboboulePreAttack(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};