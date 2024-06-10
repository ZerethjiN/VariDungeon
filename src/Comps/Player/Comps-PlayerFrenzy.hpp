#pragma once

#include <Zerengine.hpp>

class PlayerFrenzy {
public:
    PlayerFrenzy(float newDuration, float newAttackSpeedCoeff, float newSpeedCoeff):
        attackSpeedCoeff(newAttackSpeedCoeff),
        speedCoeff(newSpeedCoeff),
        duration(newDuration),
        curTime(0) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    void reset() {
        curTime = 0;
    }

public:
    const float attackSpeedCoeff;
    const float speedCoeff;

private:
    const float duration;
    float curTime;
};