#pragma once

#include <Zerengine.hpp>

class Mummy {
public:
    Mummy(float newMoveDuration, float newPreAttackDuration, float newAttackDuration):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration),
        attackDuration(newAttackDuration) {
    }

    float getMoveDuration() const {
        return moveDuration;
    }

    float getPreAttackDuration() const {
        return preAttackDuration;
    }

    float getAttackDuration() const {
        return attackDuration;
    }

private:
    const float moveDuration;
    const float preAttackDuration;
    const float attackDuration;
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