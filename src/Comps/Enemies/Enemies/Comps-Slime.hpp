#pragma once

#include <Zerengine.hpp>

class Slime final: public IComponent, public IIsTickDuration {
public:
    Slime(float newDirectionCooldown):
        IIsTickDuration(newDirectionCooldown) {
    }
};