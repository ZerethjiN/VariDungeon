#pragma once

#include <Zerengine.hpp>

class Spectre {
public:
    Spectre(float newMoveDuration, float newVanishDuration, float newCastDuration):
        moveDuration(newMoveDuration),
        vanishDuration(newVanishDuration),
        castDuration(newCastDuration) {
    }

public:
    const float moveDuration;
    const float vanishDuration;
    const float castDuration;
};

class IsSpectreMove {
public:
    IsSpectreMove(float newDuration):
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

class IsSpectreVanish {
public:
    IsSpectreVanish(float newDuration):
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

class IsSpectreCast {
public:
    IsSpectreCast(float newDuration):
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