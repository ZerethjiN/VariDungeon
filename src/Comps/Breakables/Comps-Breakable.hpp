#pragma once

#include <Zerengine.hpp>

class Breakable {
public:
    Breakable(const std::string& newNoHitAnimName, const std::string& newOnHitAnimName, const std::string& newDestroyedAnimName):
        noHitAnimName(newNoHitAnimName),
        onHitAnimName(newOnHitAnimName),
        destroyedAnimName(newDestroyedAnimName) {
    }

    const std::string& getNoHitAnimName() const {
        return noHitAnimName;
    }

    const std::string& getOnHitAnimName() const {
        return onHitAnimName;
    }

    const std::string& getDestroyedAnimName() const {
        return destroyedAnimName;
    }

private:
    const std::string noHitAnimName;
    const std::string onHitAnimName;
    const std::string destroyedAnimName;
};

class OnBreakableHit {
public:
    OnBreakableHit(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};