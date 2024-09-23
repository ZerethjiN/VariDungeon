#pragma once

#include <Zerengine.hpp>

class Slime final: public IIsTickDuration {
public:
    Slime(float newDirectionCooldown):
        IIsTickDuration(newDirectionCooldown) {
    }
};