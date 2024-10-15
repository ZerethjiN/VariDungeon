#pragma once

#include <Zerengine.hpp>

class MegaSlime final: public IComponent {
public:
    MegaSlime(float newMoveDuration, float newBounceDuration, float newFireballDuration, float newSpawnDuration, int nbBounceLvl1, float newBounceMoveSpeed, float newBounceGroundDuration, int nbFireballLvl1, float newFireballMegaSlimeMoveSpeed):
        moveDuration(newMoveDuration),
        bounceDuration(newBounceDuration),
        fireballDuration(newFireballDuration),
        spawnDuration(newSpawnDuration),
        bounceCooldown((newBounceDuration / nbBounceLvl1) - newBounceGroundDuration),
        nbBounce(nbBounceLvl1),
        bounceMoveSpeed(newBounceMoveSpeed),
        bounceGroundDuration(newBounceGroundDuration),
        fireballCooldownLvl1(newFireballDuration / nbFireballLvl1),
        fireballMegaSlimeMoveSpeed(newFireballMegaSlimeMoveSpeed),
        lastState(4) {
    }

public:
    const float moveDuration;
    const float bounceDuration;
    const float fireballDuration;
    const float spawnDuration;
    const float bounceCooldown;
    const std::size_t nbBounce;
    const float bounceMoveSpeed;
    const float bounceGroundDuration;
    const float fireballCooldownLvl1;
    const float fireballMegaSlimeMoveSpeed;

    unsigned int lastState;
};

class IsMegaSlimeMove final: public IComponent, public IIsStateDuration {
public:
    IsMegaSlimeMove(float newMoveDuration):
        IIsStateDuration(newMoveDuration) {
    }
};

class IsMegaSlimeBounceTotal final: public IComponent, public IIsStateDuration {
public:
    IsMegaSlimeBounceTotal(float newBounceDuration):
        IIsStateDuration(newBounceDuration) {
    }
};

class IsMegaSlimeBounce final: public IComponent {
public:
    IsMegaSlimeBounce(float newBounceCooldown, float newBounceGroundDuration, std::size_t newNbBounce):
        bounceCooldown(newBounceCooldown),
        bounceGroundDuration(newBounceGroundDuration),
        bounceCurTime(0),
        isOnGround(false),
        nbBounce(newNbBounce) {
    }

    bool canBounce(float delta) {
        bounceCurTime += delta;
        if (isOnGround) {
            if (bounceCurTime >= bounceGroundDuration) {
                bounceCurTime -= bounceGroundDuration;
                isOnGround = false;
                nbBounce--;
                return true;
            }
        } else {
            if (bounceCurTime >= bounceCooldown) {
                bounceCurTime -= bounceCooldown;
                isOnGround = true;
                return true;
            }
        }
        return false;
    }

    bool isJump() const {
        return !isOnGround;
    }

private:
    const float bounceCooldown;
    const float bounceGroundDuration;
    float bounceCurTime;
    bool isOnGround;

public:
    std::size_t nbBounce;
};

class IsMegaSlimeFireball final: public IComponent {
public:
    IsMegaSlimeFireball(float newFireballDuration, float newFireballCooldownLvl1):
        fireballDuration(newFireballDuration),
        curTime(0),
        fireballCooldownLvl1(newFireballCooldownLvl1),
        fireballCurTime(0),
        curFireball(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= fireballDuration;
    }

    bool canCastFireball(float delta) {
        fireballCurTime += delta;
        if (fireballCurTime >= fireballCooldownLvl1) {
            fireballCurTime -= fireballCooldownLvl1;
            curFireball++;
            curFireball %= 8;
            return true;
        }
        return false;
    }

    unsigned int getCurFireball() const {
        return curFireball;
    }

private:
    const float fireballDuration;
    float curTime;

    const float fireballCooldownLvl1;
    float fireballCurTime;
    unsigned int curFireball;
};

class IsMegaSlimePreSpawn final: public IComponent, public IIsStateDuration {
public:
    IsMegaSlimePreSpawn(float newSpawnDuration):
        IIsStateDuration(newSpawnDuration) {
    }
};