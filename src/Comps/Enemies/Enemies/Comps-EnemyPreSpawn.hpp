#pragma once

#include <Zerengine.hpp>

class EnemyPreSpawn final: public IComponent {
public:
    EnemyPreSpawn(float newDuration, int newNbParticles):
        curNbParticle(0),
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

public:
    std::size_t curNbParticle;

private:
    const float duration;
    float curTime;

    const float spawnParticleTime;
    float curSpawnParticleTime;
};