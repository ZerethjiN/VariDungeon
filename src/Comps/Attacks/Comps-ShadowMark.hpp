#pragma once

#include <Zerengine.hpp>

class ShadowMark {
public:
    ShadowMark(float newPreExplosionDuration, float newExplosionDuration):
        preExplosionDuration(newPreExplosionDuration),
        explosionDuration(newExplosionDuration) {
    }

public:
    const float preExplosionDuration;
    const float explosionDuration;
};

class IsShadowMarkPreExplosion {
public:
    IsShadowMarkPreExplosion(float newDuration):
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

class IsShadowMarkExplosion {
public:
    IsShadowMarkExplosion(float newDuration):
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