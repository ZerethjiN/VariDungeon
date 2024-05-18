#pragma once

#include <Zerengine.hpp>

class Damage {
public:
    Damage(float newDamage):
        damage(newDamage) {
    }

    operator float() const {
        return damage;
    }

    float getDamage() const {
        return damage;
    }

private:
    const float damage;
};

class DamageText {
public:
    DamageText(const glm::vec2& newDirection, float newDuration, float newMaxScale, float newSpeed):
        direction(newDirection),
        duration(newDuration),
        curTime(0),
        maxScale(newMaxScale),
        speed(newSpeed) {
    }

    bool canDestroyText(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

public:
    glm::vec2 direction;
    float duration;
    float curTime;
    float maxScale;
    float speed;
};