#pragma once

#include <Zerengine.hpp>

class Gasterolcan final {
public:
    Gasterolcan(float newMoveDuration, float newPreAttackDuration, float newAttackDuration, float newRollSpeedCoeff):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration),
        attackDuration(newAttackDuration),
        rollSpeedCoeff(newRollSpeedCoeff) {
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

    float getRollSpeedCoeff() const {
        return rollSpeedCoeff;
    }

private:
    const float moveDuration;
    const float preAttackDuration;
    const float attackDuration;
    const float rollSpeedCoeff;
};

class IsGasterolcanMove final {
public:
    IsGasterolcanMove(float newDuration):
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

class IsGasterolcanPreAttack final {
public:
    IsGasterolcanPreAttack(float newDuration):
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

class IsGasterolcanAttack final {
public:
    IsGasterolcanAttack(float newDuration):
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