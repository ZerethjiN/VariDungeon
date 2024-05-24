#pragma once

#include <Zerengine.hpp>

class Player {};
class PlayerWeapon {};
class PlayerAttractor {};

class PlayerAttackCooldown {
public:
    PlayerAttackCooldown(float newAttackCooldown):
        attackCooldown(newAttackCooldown) {
    }

    void reduceCooldown(float newAmount) {
        attackCooldown -= newAmount;
    }

    float getAttackCooldown() const {
        return attackCooldown;
    }

private:
    float attackCooldown;
};

class PlayerKnockbackStrength {
public:
    PlayerKnockbackStrength(float newKnockbackStrength):
        knockbackStrength(newKnockbackStrength) {
    }

    void increaseKnockbackStrength(float newAmount) {
        knockbackStrength += newAmount;
    }

    float getKnockbackStrength() const {
        return knockbackStrength;
    }

private:
    float knockbackStrength;
};

class PlayerDamage {
public:
    PlayerDamage(float newCurDamage):
        curDamage(newCurDamage) {
    }

    PlayerDamage& operator +=(float newDamage) {
        curDamage += newDamage;
        return *this;
    }

    PlayerDamage& operator -=(float newDamage) {
        curDamage -= newDamage;
        return *this;
    }

    PlayerDamage& operator *=(float newDamage) {
        curDamage *= newDamage;
        return *this;
    }

    PlayerDamage& operator /=(float newDamage) {
        curDamage /= newDamage;
        return *this;
    }

    operator float() const {
        return curDamage;
    }

    float getDamage() const {
        return curDamage;
    }

private:
    float curDamage;
};

class PlayerAttackWeight {
public:
    PlayerAttackWeight(const glm::vec2& newDirection, float newSpeed, float newForwardDuration):
        direction(newDirection),
        speed(newSpeed),
        forwardDuration(newForwardDuration),
        curTime(0),
        isForward(true) {
    }

    void canGoBackward(float delta) {
        curTime += delta;
        if (curTime >= forwardDuration) {
            curTime -= forwardDuration;
            isForward = false;
        }
    }

    bool canStopBackward(float delta) {
        curTime += delta;
        return curTime >= forwardDuration;
    }

    const glm::vec2& getDirection() const {
        return direction;
    }

    float getSpeed() const {
        return speed;
    }

    bool getIsForward() const {
        return isForward;
    }

private:
    const glm::vec2 direction;
    const float speed;
    const float forwardDuration;
    float curTime;
    bool isForward;
};