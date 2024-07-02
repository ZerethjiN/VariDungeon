#pragma once

#include <Zerengine.hpp>

class CombatParticleGenerator final {
public:
    CombatParticleGenerator(float newDuration, int newNbRepulseParticles, int newNbSmallParticles):
        duration(newDuration),
        curTime(0),
        repulseParticleInterval(newDuration / newNbRepulseParticles),
        curRepulseParticleTime(0),
        smallParticleInterval(newDuration / newNbSmallParticles),
        curSmallParticleTime(0),
        curSmallParticle(0) {
    }

    bool canStop(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canSpawnRepulseParticle(float delta) {
        curRepulseParticleTime += delta;
        if (curRepulseParticleTime >= repulseParticleInterval) {
            curRepulseParticleTime -= repulseParticleInterval;
            return true;
        }
        return false;
    }

    bool canSpawnSmallParticle(float delta) {
        curSmallParticleTime += delta;
        if (curSmallParticleTime >= smallParticleInterval) {
            curSmallParticleTime -= smallParticleInterval;
            curSmallParticle++;
            return true;
        }
        return false;
    }

    int getCurSmallParticle() const {
        return curSmallParticle;
    }

private:
    // Total Duration
    const float duration;
    float curTime;

    // Repulse Particles
    const float repulseParticleInterval;
    float curRepulseParticleTime;

    // Small Particles
    const float smallParticleInterval;
    float curSmallParticleTime;
    int curSmallParticle;
};