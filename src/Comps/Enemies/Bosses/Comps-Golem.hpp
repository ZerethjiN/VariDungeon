#pragma once

#include <Zerengine.hpp>

class Golem final {
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

struct IsGolemPreLaserAttackCardinal final: public IIsStateDuration {
public:
    IsGolemPreLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemPreLaserAttackDiagonal final: public IIsStateDuration {
public:
    IsGolemPreLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackCardinal final: public IIsStateDuration {
public:
    IsGolemLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackDiagonal final: public IIsStateDuration {
public:
    IsGolemLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemRockAttack final: public IIsStateDuration {
    IsGolemRockAttack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsGolemFootAttack final: public IIsStateDuration {
    IsGolemFootAttack(float newDuration): IIsStateDuration(newDuration) {}
};

class GolemRock final {
public:
    GolemRock(float newSpawnCooldown):
        spawnCooldown(newSpawnCooldown),
        curTime(0) {
    }

    bool canSpawn(float delta) {
        curTime += delta;
        return curTime >= spawnCooldown;
    }

private:
    const float spawnCooldown;
    float curTime;
};