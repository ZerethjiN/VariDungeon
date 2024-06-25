#pragma once

#include <Zerengine.hpp>

class Golem {
public:
    Golem(float newPreLaserDuration, float newLaserDuration, float newNbLasers, float newRockDuration, int newNbRocks, float newFootDuration):
        preLaserDuration(newPreLaserDuration),
        laserDuration(newLaserDuration / newNbLasers),
        nbLasers(newNbLasers),
        rockDuration(newRockDuration),
        nbRocks(newNbRocks),
        footDuration(newFootDuration) {
    }

public:
    const float preLaserDuration;
    const float laserDuration;
    const int nbLasers;
    const float rockDuration;
    const int nbRocks;
    const float footDuration;
};

struct IsGolemPreLaserAttackCardinal: public IIsStateDuration {
public:
    IsGolemPreLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemPreLaserAttackDiagonal: public IIsStateDuration {
public:
    IsGolemPreLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackCardinal: public IIsStateDuration {
public:
    IsGolemLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackDiagonal: public IIsStateDuration {
public:
    IsGolemLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemRockAttack: public IIsStateDuration {
    IsGolemRockAttack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsGolemFootAttack: public IIsStateDuration {
    IsGolemFootAttack(float newDuration): IIsStateDuration(newDuration) {}
};