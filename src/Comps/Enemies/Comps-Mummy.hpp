#pragma once

#include <Zerengine.hpp>

class Mummy {
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

class IsMummyMove {
public:
    IsMummyMove(float newDuration):
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

class IsMummyPreAttack {
public:
    IsMummyPreAttack(float newDuration):
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

class IsMummyAttack {
public:
    IsMummyAttack(float newDuration):
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