#pragma once

#include <Zerengine.hpp>

class Player final: public IComponent {};
class PlayerWeapon final: public IComponent {};
class PlayerAttractor final: public IComponent {};

class IsPlayerDead final: public IComponent, public IIsStateDuration {
public:
    IsPlayerDead(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class PlayerAttackCooldown final: public IComponent {
public:
    PlayerAttackCooldown(float newAttackCooldown):
        attackCooldown(newAttackCooldown) {
    }

    PlayerAttackCooldown& operator*=(float newAmount) {
        attackCooldown *= newAmount;
        return *this;
    }

    PlayerAttackCooldown& operator/=(float newAmount) {
        attackCooldown /= newAmount;
        return *this;
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

class PlayerKnockbackStrength final: public IComponent {
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

class PlayerDamage final: public IComponent {
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

class PlayerAttackWeight final: public IComponent {
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

class OnPlayerDeath final: public IComponent {
public:
    OnPlayerDeath(const std::function<void(World&, const Ent&)>& new_callback):
        callback(new_callback) {
    }

public:
    std::function<void(World&, const Ent&)> callback;
};