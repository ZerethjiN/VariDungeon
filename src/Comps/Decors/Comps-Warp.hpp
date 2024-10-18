#pragma once

#include <Zerengine.hpp>
#include <Interfaces.hpp>

class Warp final: public IComponent {};

class WarpOpening final: public IComponent, public IIsStateDuration {
public:
    WarpOpening(float new_duration):
        IIsStateDuration(new_duration) {
    }
};