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

    float getMoveDuration() const {
        return moveDuration;
    }

    float getDirectionCooldown() const {
        return directionCooldown;
    }

    float getAttackDuration() const {
        return attackDuration;
    }

    float getAttackSpeedCoeff() const {
        return attackSpeedCoeff;
    }

private:
    const float moveDuration;
    const float directionCooldown;
    const float attackDuration;
    const float attackSpeedCoeff;
};

class IsInsectMove final {
public:
    IsInsectMove(float newDuration, float newDirectionCooldown):
        duration(newDuration),
        curTime(0),
        directionCooldown(newDirectionCooldown),
        curDirectionCooldown(directionCooldown) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canChangeDirection(float delta) {
        curDirectionCooldown += delta;
        if (curDirectionCooldown >= directionCooldown) {
            curDirectionCooldown -= directionCooldown;
            return true;
        }
        return false;
    }

private:
    const float duration;
    float curTime;

    const float directionCooldown;
    float curDirectionCooldown;
};

class IsInsectAttack final {
public:
    IsInsectAttack(float newDuration):
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