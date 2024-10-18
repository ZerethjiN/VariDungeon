#pragma once

#include <Zerengine.hpp>

class Bomb final: public IComponent {
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

class BombSpread final: public IComponent {
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

public:
    const glm::vec2 direction;
    const float speed;

private:
    const float duration;
    float curTime;
};

class PlayerBomb final: public IComponent {
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

public:
    float cooldown;
    float curTime;
};