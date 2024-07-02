#pragma once

#include <Zerengine.hpp>

class Bat final {
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

class IsBatMove final {
public:
    IsBatMove(float newDuration):
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

class IsBatAttack final {
public:
    IsBatAttack(float newDuration):
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