#pragma once

#include <Zerengine.hpp>

class Turret final: public IComponent {
public:
    Turret(float newCardinalDuration, float newDiagonalDuration, float newCardinalPreShotDuration, float newDiagonalPreShotDuration):
        cardinalDuration(newCardinalDuration),
        diagonalDuration(newDiagonalDuration),
        cardinalPreShotDuration(newCardinalPreShotDuration),
        diagonalPreShotDuration(newDiagonalPreShotDuration) {
    }

public:
    const float cardinalDuration;
    const float diagonalDuration;
    const float cardinalPreShotDuration;
    const float diagonalPreShotDuration;
};

class IsTurretCardinal final: public IComponent {
public:
    IsTurretCardinal(float newDuration, float newPreShotDuration):
        duration(newDuration),
        curTime(0),
        preShotDuration(newDuration - newPreShotDuration),
        curPreShotTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canPreShot(float delta) {
        curPreShotTime += delta;
        if (curPreShotTime >= preShotDuration) {
            curPreShotTime = -10000.f;
            return true;
        }
        return false;
    }

private:
    const float duration;
    float curTime;

    const float preShotDuration;
    float curPreShotTime;
};

class IsTurretDiagonal final: public IComponent {
public:
    IsTurretDiagonal(float newDuration, float newPreShotDuration):
        duration(newDuration),
        curTime(0),
        preShotDuration(newDuration - newPreShotDuration),
        curPreShotTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canPreShot(float delta) {
        curPreShotTime += delta;
        if (curPreShotTime >= preShotDuration) {
            curPreShotTime = -10000.f;
            return true;
        }
        return false;
    }

private:
    const float duration;
    float curTime;

    const float preShotDuration;
    float curPreShotTime;
};