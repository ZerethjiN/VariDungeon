#pragma once

#include <Zerengine.hpp>

class CombatParticleGenerator {
public:
    CombatParticleGenerator(float newDuration, int newNbParticles):
        duration(newDuration),
        curTime(0),
        particleInterval(newDuration / newNbParticles),
        curParticleTime(0),
        nbParticles(newNbParticles),
        curNbParticles(0) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canSpawnParticle(float delta) {
        curParticleTime += delta;
        if (curParticleTime >= particleInterval) {
            curParticleTime -= particleInterval;
            return true;
        }
        return false;
    }

private:
    const float duration;
    float curTime;
    const float particleInterval;
    float curParticleTime;
    const int nbParticles;
    int curNbParticles;
};