#pragma once

#include <Zerengine.hpp>

class LootSpread {
public:
    LootSpread(float newDuration, const glm::vec2& newDirection, float newSpeed):
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

class Lootable {};

class LootAttract {
public:
    LootAttract(float newSpeed, Ent newTargetEnt):
        speed(newSpeed),
        targetEnt(newTargetEnt) {
    }

    float getSpeed() const {
        return speed;
    }

    Ent getTargetEnt() const {
        return targetEnt;
    }

private:
    const float speed;
    const Ent targetEnt;
};