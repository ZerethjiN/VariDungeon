#pragma once

#include <Zerengine.hpp>

class Bat {
public:
    Bat(float newMoveDuration, float newAttackDuration):
        moveDuration(newMoveDuration),
        attackDuration(newAttackDuration) {
    }

    float getMoveDuration() const {
        return moveDuration;
    }

    float getAttackDuration() const {
        return attackDuration;
    }

private:
    const float moveDuration;
    const float attackDuration;
};

class IsBatMove {
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

class IsBatAttack {
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