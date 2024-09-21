#pragma once

#include <Zerengine.hpp>

class Breakable final {};

struct OnBreakableHitDuration final: public IIsStateDuration {
    OnBreakableHitDuration(float newDuration): IIsStateDuration(newDuration) {}
};

class OnBreakableHit final {
public:
    OnBreakableHit(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};

class OnBreakableNoHit final {
public:
    OnBreakableNoHit(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};

class OnBreakableBreak final {
public:
    OnBreakableBreak(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};