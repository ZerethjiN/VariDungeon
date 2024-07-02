#pragma once

#include <Zerengine.hpp>

class LavaSlime final {
public:
    LavaSlime(float newMoveDuration, float newPreAttackDuration):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration) {
    }

    float getMoveDuration() const {
        return moveDuration;
    }

    float getPreAttackDuration() const {
        return preAttackDuration;
    }

private:
    const float moveDuration;
    const float preAttackDuration;
};

class IsLavaSlimeMove final {
public:
    IsLavaSlimeMove(float newDuration):
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

class IsLavaSlimePreAttack final {
public:
    IsLavaSlimePreAttack(float newDuration):
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