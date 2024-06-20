#pragma once

#include <Zerengine.hpp>

class EnemyPreSpawn {
public:
    EnemyPreSpawn(float newDuration, int newNbParticles):
        duration(newDuration),
        curTime(0),
        spawnParticleTime(newDuration / newNbParticles),
        curSpawnParticleTime(newDuration / newNbParticles) {
    }

    bool canRemovePreSpawn(float delta) {
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