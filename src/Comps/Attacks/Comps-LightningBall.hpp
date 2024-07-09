#pragma once

#include <Zerengine.hpp>

class LightningBall final {
public:
    LightningBall(const glm::vec2& newDirection):
        direction(newDirection) {
    }

public:
    const glm::vec2 direction;
};

class PlayerLightningBall final {
public:
    PlayerLightningBall(float newCooldown):
        cooldown(newCooldown),
        curTime(0) {
    }

    bool canSpawnLightningBall(float delta) {
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