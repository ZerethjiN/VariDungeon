#pragma once

#include <Zerengine.hpp>

class Unmoveable {};

class UnmoveableTimer {
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