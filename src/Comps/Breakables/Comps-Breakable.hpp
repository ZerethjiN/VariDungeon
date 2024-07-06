#pragma once

#include <Zerengine.hpp>

class Breakable final {
public:
    Breakable(const std::string& newNoHitAnimName, const std::string& newOnHitAnimName, const std::string& newDestroyedAnimName):
        noHitAnimName(newNoHitAnimName),
        onHitAnimName(newOnHitAnimName),
        destroyedAnimName(newDestroyedAnimName) {
    }

public:
    const std::string noHitAnimName;
    const std::string onHitAnimName;
    const std::string destroyedAnimName;
};

struct OnBreakableHit final: public IIsStateDuration {
    OnBreakableHit(float newDuration): IIsStateDuration(newDuration) {}
};

class OnBreakableBreak final {
public:
    OnBreakableBreak(void(*const newOnBreak)(World&, Ent)):
        onBreak(newOnBreak) {
    }

public:
    void(*const onBreak)(World&, Ent);
};