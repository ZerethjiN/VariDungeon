#pragma once

#include <Zerengine.hpp>

class Barbarian {};

class IsBarbarianDash {
public:
    IsBarbarianDash(float newDuration, float newSpeedCoeff):
        duration(newDuration),
        curTime(0),
        speedCoeff(newSpeedCoeff) {
    }

    bool canStopDash(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    float getSpeedCoeff() const {
        return speedCoeff;
    }

private:
    const float duration;
    float curTime;
    float speedCoeff;
};

class IsBarbarianAttack {
public:
    IsBarbarianAttack(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canStopAttack(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};