#pragma once

#include <Zerengine.hpp>

class LootSpread final: public IComponent {
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

class Lootable final: public IComponent {};

class LootAttract final: public IComponent {
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

class LootCallback final: public IComponent {
public:
    LootCallback(std::function<void(World&, const Ent&, const Ent&)> new_callback):
        callback(new_callback) {
    }

public:
    std::function<void(World&, const Ent&, const Ent&)> callback;
};