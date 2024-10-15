#pragma once

#include <Zerengine.hpp>

class RockBoss final: public IComponent {
public:
    RockBoss(float newStunDuration, float newSmallCrystalsDuration, float newGroundCrystalsCooldown, float new_pre_roll_cooldown, float newRollSpeedCoeff):
        stunDuration(newStunDuration),
        smallCrystalsDuration(newSmallCrystalsDuration),
        curSmallCrystalTime(0),
        groundCrystalsCooldown(newGroundCrystalsCooldown),
        pre_roll_cooldown(new_pre_roll_cooldown),
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
    const float pre_roll_cooldown;

    const float rollSpeedCoeff;

    unsigned int lastState;
};

class IsRockBossPreRoll final: public IComponent, public IIsStateDuration {
public:
    IsRockBossPreRoll(float new_duration):
        IIsStateDuration(new_duration) {
    }
};

class IsRockBossRoll final: public IComponent {};

class IsRockBossStun final: public IComponent {
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

class IsRockBossGroundCrystals final: public IComponent {
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