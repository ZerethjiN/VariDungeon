#pragma once

#include <Zerengine.hpp>

class Breakable final: public IComponent {};

struct OnBreakableHitDuration final: public IComponent, public IIsStateDuration {
    OnBreakableHitDuration(float newDuration): IIsStateDuration(newDuration) {}
};

class OnBreakableHit final: public IComponent {
public:
    OnBreakableHit(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};

class OnBreakableNoHit final: public IComponent {
public:
    OnBreakableNoHit(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};

class OnBreakableBreak final: public IComponent {
public:
    OnBreakableBreak(const std::function<void(World&, Ent)>& newCallback):
        callback(newCallback) {
    }

public:
    std::function<void(World&, Ent)> callback;
};