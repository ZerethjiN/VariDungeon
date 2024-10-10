#pragma once

#include <Zerengine.hpp>

class DeathParticleGenerator final: public IComponent {
public:
    DeathParticleGenerator(bool newNeedDestroy, float newDuration, int newNbParticles):
        curNbParticle(0),
        needDestroy(newNeedDestroy),
        duration(newDuration),
        curTime(0),
        spawnParticleTime(newDuration / newNbParticles),
        curSpawnParticleTime(newDuration / newNbParticles) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canSpawnParticle(float delta) {
        curSpawnParticleTime += delta;
        if (curSpawnParticleTime >= spawnParticleTime) {
            curSpawnParticleTime -= spawnParticleTime;
            curNbParticle++;
            return true;
        }
        return false;
    }

    bool getNeedDestroy() const {
        return needDestroy;
    }

public:
    std::size_t curNbParticle;

private:
    const bool needDestroy;

    const float duration;
    float curTime;

    const float spawnParticleTime;
    float curSpawnParticleTime;
};