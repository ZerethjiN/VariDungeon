#pragma once

#include <Zerengine.hpp>

class Golem final: public IComponent {
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

struct IsGolemPreLaserAttackCardinal final: public IComponent, public IIsStateDuration {
public:
    IsGolemPreLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemPreLaserAttackDiagonal final: public IComponent, public IIsStateDuration {
public:
    IsGolemPreLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackCardinal final: public IComponent, public IIsStateDuration {
public:
    IsGolemLaserAttackCardinal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemLaserAttackDiagonal final: public IComponent, public IIsStateDuration {
public:
    IsGolemLaserAttackDiagonal(float newDuration, int newCurLasers):
        IIsStateDuration(newDuration),
        curLasers(newCurLasers) {
    }

public:
    const int curLasers;
};

struct IsGolemRockAttack final: public IComponent, public IIsStateDuration {
    IsGolemRockAttack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsGolemFootAttack final: public IComponent, public IIsStateDuration {
    IsGolemFootAttack(float newDuration): IIsStateDuration(newDuration) {}
};

class GolemRock final: public IComponent {
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