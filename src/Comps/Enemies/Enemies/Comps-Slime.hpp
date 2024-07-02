#pragma once

#include <Zerengine.hpp>

class Slime final {
public:
    Slime(float newDirectionCooldown):
        directionCooldown(newDirectionCooldown),
        curDirectionCooldown(0) {
    }

    bool canChangeDirection(float delta) {
        curDirectionCooldown += delta;
        if (curDirectionCooldown >= directionCooldown) {
            curDirectionCooldown -= directionCooldown;
            return true;
        }
        return false;
    }

private:
    const float directionCooldown;
    float curDirectionCooldown;
};