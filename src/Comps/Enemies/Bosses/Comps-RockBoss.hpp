#pragma once

#include <Zerengine.hpp>

class RockBoss {
public:
    RockBoss(float newStunDuration, float newSmallCrystalsDuration, float newGroundCrystalsCooldown, float newGroundCrystalsCooldownP2, float newRollSpeedCoeff):
        stunDuration(newStunDuration),
        smallCrystalsDuration(newSmallCrystalsDuration),
        curSmallCrystalTime(0),
        groundCrystalsCooldown(newGroundCrystalsCooldown),
        groundCrystalsCooldownP2(newGroundCrystalsCooldownP2),
        rollSpeedCoeff(newRollSpeedCoeff),
        lastState(3) {
    }
    
    bool canThrowSmallCrystal(float delta) {
        curSmallCrystalTime += delta;
        if (curSmallCrystalTime >= smallCrystalsDuration) {
            curSmallCrystalTime -= smallCrystalsDuration;
            return true;
        }
        return false;
    }

public:
    const float stunDuration;
    const float smallCrystalsDuration;
    float curSmallCrystalTime;
    const float groundCrystalsCooldown;
    const float groundCrystalsCooldownP2;

    const float rollSpeedCoeff;

    unsigned int lastState;
};

class IsRockBossRoll {};
class IsRockBossRollP2 {};

class IsRockBossStun {
public:
    IsRockBossStun(float newStunDuration):
        stunDuration(newStunDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= stunDuration;
    }

private:
    const float stunDuration;
    float curTime;
};

class IsRockBossGroundCrystals {
public:
    IsRockBossGroundCrystals(float newGroundCrystalDuration):
        groundCrystalDuration(newGroundCrystalDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= groundCrystalDuration;
    }

private:
    const float groundCrystalDuration;
    float curTime;
};

class IsRockBossGroundCrystalsP2 {
public:
    IsRockBossGroundCrystalsP2(float newGroundCrystalDuration):
        groundCrystalDuration(newGroundCrystalDuration),
        curTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= groundCrystalDuration;
    }

private:
    const float groundCrystalDuration;
    float curTime;
};