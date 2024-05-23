#pragma once

#include <Zerengine.hpp>

class Dagger {
public:
    Dagger(const glm::vec2& newDirection):
        direction(newDirection) {
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

private:
    const glm::vec2 direction;
};

class PlayerDagger {
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