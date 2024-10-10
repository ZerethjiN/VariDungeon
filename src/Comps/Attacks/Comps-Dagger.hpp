#pragma once

#include <Zerengine.hpp>

class Dagger final: public IComponent {
public:
    Dagger(const glm::vec2& newDirection):
        direction(newDirection) {
    }

public:
    const glm::vec2 direction;
};

class PlayerDagger final: public IComponent {
public:
    PlayerDagger(float newCooldown):
        cooldown(newCooldown),
        curTime(0) {
    }

    bool canSpawnDagger(float delta) {
        curTime += delta;
        if (curTime >= cooldown) {
            curTime -= cooldown;
            return true;
        }
        return false;
    }

private:
    const float cooldown;
    float curTime;
};