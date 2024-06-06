#pragma once

#include <Zerengine.hpp>

class RockBoss {
public:
    RockBoss(float newStunDuration, float newSmallCrystalsDuration, float newGroundCrystalsCooldown, float newRollSpeedCoeff):
        stunDuration(newStunDuration),
        smallCrystalsDuration(newSmallCrystalsDuration),
        groundCrystalsCooldown(newGroundCrystalsCooldown),
        rollSpeedCoeff(newRollSpeedCoeff),
        lastState(3) {
    }

public:
    const float stunDuration;
    const float smallCrystalsDuration;
    const float groundCrystalsCooldown;

    const float rollSpeedCoeff;

    unsigned int lastState;
};

class IsRockBossRoll {};

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

class IsRockBossSmallCrystals {
public:
    IsRockBossSmallCrystals(float newSmallCrystalDuration, int newNbSmallCrystals):
        smallCrystalDuration(newSmallCrystalDuration),
        curTime(0),
        smallCrystalCooldown(newSmallCrystalDuration / newNbSmallCrystals),
        curSmallCrystalTime(0) {
    }

    bool canSwitchState(float delta) {
        curTime += delta;
        return curTime >= smallCrystalDuration;
    }

    bool canThrowSmallCrystal(float delta) {
        curSmallCrystalTime += delta;
        if (curSmallCrystalTime >= smallCrystalCooldown) {
            curSmallCrystalTime -= smallCrystalCooldown;
            return true;
        }
        return false;
    }

private:
    const float smallCrystalDuration;
    float curTime;
    const float smallCrystalCooldown;
    float curSmallCrystalTime;
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