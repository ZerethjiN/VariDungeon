#pragma once

#include <Zerengine.hpp>
#include <Interfaces.hpp>

class Chest final: public IComponent {};

class ChestOpening final: public IComponent, public IIsStateDuration {
public:
    ChestOpening(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class ChestOpeningLoot final: public IComponent, public IIsTickDuration {
public:
    ChestOpeningLoot(float new_tick_duration):
        IIsTickDuration(new_tick_duration) {
    }
};