#pragma once

#include <Zerengine.hpp>

class MegaSlime {
public:
    MegaSlime(float newMoveDuration, float newBounceDuration, float newFireballDuration, float newSpawnDuration, int nbBounceLvl1, int nbBounceLvl2, float newBounceMoveSpeed, float newBounceGroundDuration, int nbFireballLvl1, int nbFireballLvl2, float newFireballMegaSlimeMoveSpeed, int nbSpawnLvl1, int nbSpawnLvl2):
        moveDuration(newMoveDuration),
        bounceDuration(newBounceDuration),
        fireballDuration(newFireballDuration),
        spawnDuration(newSpawnDuration),
        bounceCooldownLvl1((newBounceDuration / nbBounceLvl1) - newBounceGroundDuration),
        bounceCooldownLvl2((newBounceDuration / nbBounceLvl2) - newBounceGroundDuration),
        bounceMoveSpeed(newBounceMoveSpeed),
        bounceGroundDuration(newBounceGroundDuration),
        fireballCooldownLvl1(newFireballDuration / nbFireballLvl1),
        fireballCooldownLvl2(newFireballDuration / nbFireballLvl2),
        fireballMegaSlimeMoveSpeed(newFireballMegaSlimeMoveSpeed),
        spawnCooldownLvl1(newSpawnDuration / nbSpawnLvl1),
        spawnCooldownLvl2(newSpawnDuration / nbSpawnLvl2),
        lastState(4) {
    }

public:
    const float moveDuration;
    const float bounceDuration;
    const float fireballDuration;
    const float spawnDuration;
    const float bounceCooldownLvl1;
    const float bounceCooldownLvl2;
    const float bounceMoveSpeed;
    const float bounceGroundDuration;
    const float fireballCooldownLvl1;
    const float fireballCooldownLvl2;
    const float fireballMegaSlimeMoveSpeed;
    const float spawnCooldownLvl1;
    const float spawnCooldownLvl2;

    unsigned int lastState;
};

class IsMegaSlimeMove {
public:
    IsMegaSlimeMove(float newMoveDuration, bool newIsP2):
        moveDuration(newMoveDuration),
        curTime(0),
        isP2(newIsP2) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= moveDuration;
    }

    bool getIsP2() const {
        return isP2;
    }

private:
    const float moveDuration;
    float curTime;
    const bool isP2;
};

class IsMegaSlimeBounce {
public:
    IsMegaSlimeBounce(float newBounceDuration, float newBounceCooldownLvl1, float newBounceCooldownLvl2, float newBounceGroundDuration, bool newIsP2):
        bounceDuration(newBounceDuration),
        curTime(0),
        bounceCooldownLvl1(newBounceCooldownLvl1),
        bounceCooldownLvl2(newBounceCooldownLvl2),
        bounceGroundDuration(newBounceGroundDuration),
        bounceCurTime(0),
        isOnGround(false),
        isP2(newIsP2) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= bounceDuration;
    }

    bool canBounce(float delta) {
        bounceCurTime += delta;
        if (isOnGround) {
            if (bounceCurTime >= bounceGroundDuration) {
                bounceCurTime -= bounceGroundDuration;
                isOnGround = false;
                return true;
            }
        } else {
            if (isP2 && bounceCurTime >= bounceCooldownLvl2) {
                bounceCurTime -= bounceCooldownLvl2;
                isOnGround = true;
                return true;
            } else if (!isP2 && bounceCurTime >= bounceCooldownLvl1) {
                bounceCurTime -= bounceCooldownLvl1;
                isOnGround = true;
                return true;
            }
        }
        return false;
    }

    bool isJump() const {
        return !isOnGround;
    }

    bool getIsP2() const {
        return isP2;
    }

private:
    const float bounceDuration;
    float curTime;

    const float bounceCooldownLvl1;
    const float bounceCooldownLvl2;
    const float bounceGroundDuration;
    float bounceCurTime;
    bool isOnGround;
    const bool isP2;
};

class IsMegaSlimeFireball {
public:
    IsMegaSlimeFireball(float newFireballDuration, float newFireballCooldownLvl1, float newFireballCooldownLvl2, bool newIsP2):
        fireballDuration(newFireballDuration),
        curTime(0),
        fireballCooldownLvl1(newFireballCooldownLvl1),
        fireballCooldownLvl2(newFireballCooldownLvl2),
        fireballCurTime(0),
        curFireball(0),
        isP2(newIsP2) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= fireballDuration;
    }

    bool canCastFireball(float delta) {
        fireballCurTime += delta;
        if (isP2 && fireballCurTime >= fireballCooldownLvl2) {
            fireballCurTime -= fireballCooldownLvl2;
            curFireball++;
            curFireball %= 8;
            return true;
        } else if (!isP2 && fireballCurTime >= fireballCooldownLvl1) {
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

    bool getIsP2() const {
        return isP2;
    }

private:
    const float fireballDuration;
    float curTime;

    const float fireballCooldownLvl1;
    const float fireballCooldownLvl2;
    float fireballCurTime;
    unsigned int curFireball;

    const bool isP2;
};

class IsMegaSlimeSpawn {
public:
    IsMegaSlimeSpawn(float newSpawnDuration, float newSpawnCooldownLvl1, float newSpawnCooldownLvl2, bool newIsP2):
        spawnDuration(newSpawnDuration),
        curTime(0),
        spawnCooldownLvl1(newSpawnCooldownLvl1),
        spawnCooldownLvl2(newSpawnCooldownLvl2),
        spawnCurTime(0),
        isP2(newIsP2) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= spawnDuration;
    }

    bool canSpawn(float delta) {
        spawnCurTime += delta;
        if (isP2 && spawnCurTime >= spawnCooldownLvl2) {
            spawnCurTime -= spawnCooldownLvl2;
            return true;
        } else if (!isP2 && spawnCurTime >= spawnCooldownLvl1) {
            spawnCurTime -= spawnCooldownLvl1;
            return true;
        }
        return false;
    }

    bool getIsP2() const {
        return isP2;
    }

private:
    const float spawnDuration;
    float curTime;

    const float spawnCooldownLvl1;
    const float spawnCooldownLvl2;
    float spawnCurTime;

    const bool isP2;
};