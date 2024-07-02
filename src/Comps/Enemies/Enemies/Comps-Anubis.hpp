#pragma once

#include <Zerengine.hpp>

class Anubis final {
public:
    Anubis(float newMoveDuration, float newAttackDuration):
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

class IsAnubisMove final {
public:
    IsAnubisMove(float newDuration):
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

class IsAnubisAttack final {
public:
    IsAnubisAttack(float newDuration):
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