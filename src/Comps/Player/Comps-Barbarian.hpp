#pragma once

#include <Zerengine.hpp>

class Barbarian final {};

class IsBarbarianDash final {
public:
    IsBarbarianDash(float newDuration, const glm::vec2& newDirection, float newSpeedCoeff):
        duration(newDuration),
        curTime(0),
        direction(newDirection),
        speedCoeff(newSpeedCoeff) {
    }

    bool canStopDash(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

    float getSpeedCoeff() const {
        return speedCoeff;
    }

private:
    const float duration;
    float curTime;
    const glm::vec2 direction;
    float speedCoeff;
};

class IsBarbarianAttack final {
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