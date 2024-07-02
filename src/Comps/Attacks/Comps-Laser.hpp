#pragma once

#include <Zerengine.hpp>

class Laser final {
public:
    Laser(const glm::vec2& newDirection):
        direction(newDirection) {
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

private:
    const glm::vec2 direction;
};

class PlayerLaser final {
public:
    PlayerLaser(float newCooldown):
        cooldown(newCooldown),
        curTime(0) {
    }

    void updateTime(float delta) {
        if (curTime < cooldown) {
            curTime += delta;
        }
    }

    bool canShot() {
        return curTime >= cooldown;
    }

    void resetCurTime() {
        curTime = 0;
    }

private:
    float cooldown;
    float curTime;
};