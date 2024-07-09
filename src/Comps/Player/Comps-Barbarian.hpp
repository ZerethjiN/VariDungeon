#pragma once

#include <Zerengine.hpp>

class Barbarian final {};

class IsBarbarianDash final {
public:
    IsBarbarianDash(float newDuration, const glm::vec2& newDirection, float newSpeedCoeff, float newPersistenceCooldown):
        duration(newDuration),
        curTime(0),
        direction(newDirection),
        speedCoeff(newSpeedCoeff),
        persistenceCooldown(newPersistenceCooldown),
        curPersistenceTime(0) {
    }

    bool canStopDash(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canSpawnPersistentImage(float delta) {
        curPersistenceTime += delta;
        if (curPersistenceTime >= persistenceCooldown) {
            curPersistenceTime -= persistenceCooldown;
            return true;
        }
        return false;
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

    const float persistenceCooldown;
    float curPersistenceTime;
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