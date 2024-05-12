#pragma once

#include <Zerengine.hpp>

class DustParticleGenerator {
public:
    DustParticleGenerator(float newDuration, int newNbParticles):
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

    int getCurNbParticle() const {
        return curNbParticle;
    }

private:
    const float duration;
    float curTime;

    const float spawnParticleTime;
    float curSpawnParticleTime;
    int curNbParticle;
};