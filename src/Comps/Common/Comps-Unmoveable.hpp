#pragma once

#include <Zerengine.hpp>

class Unmoveable final {};

class UnmoveableTimer final {
public:
    UnmoveableTimer(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canStopUnmove(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};