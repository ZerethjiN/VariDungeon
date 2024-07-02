#pragma once

#include <Zerengine.hpp>

class Spike final {
public:
    Spike(float newSpikeUpDuration, float newSpikeDownDuration):
        spikeUpDuration(newSpikeUpDuration),
        spikeDownDuration(newSpikeDownDuration) {
    }

public:
    const float spikeUpDuration;
    const float spikeDownDuration;
};

class IsSpikeUp final {
public:
    IsSpikeUp(float newDuration):
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

class IsSpikeDown final {
public:
    IsSpikeDown(float newDuration):
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