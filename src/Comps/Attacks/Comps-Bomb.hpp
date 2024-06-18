#pragma once

#include <Zerengine.hpp>

class Bomb {
public:
    Bomb(float newCooldown):
        cooldown(newCooldown) {
    }

    bool canExplode(float delta) {
        cooldown -= delta;
        return cooldown <= 0;
    }

private:
    float cooldown;
};

class BombSpread {
public:
    BombSpread(float newDuration, const glm::vec2& newDirection, float newSpeed):
        duration(newDuration),
        curTime(0),
        direction(newDirection),
        speed(newSpeed) {
    }

    bool canStopSpreading(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

    float getSpeed() const {
        return speed;
    }

private:
    const float duration;
    float curTime;
    const glm::vec2 direction;
    const float speed;
};

class PlayerBomb {
public:
    PlayerBomb(float newCooldown):
        cooldown(newCooldown),
        curTime(0) {
    }

    bool canSpawnBomb(float delta) {
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