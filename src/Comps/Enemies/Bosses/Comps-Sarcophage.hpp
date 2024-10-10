#pragma once

#include <Zerengine.hpp>

class Sarcophage final: public IComponent {
public:
    Sarcophage(float newPreLaserDuration, float newLaserDuration, float newShadowMarkDuration, float newNbShadowMark, float newObeliskDuration):
        preLaserDuration(newPreLaserDuration),
        laserDuration(newLaserDuration),
        shadowMarkDuration(newShadowMarkDuration),
        nbShadowMark(newNbShadowMark),
        obeliskDuration(newObeliskDuration) {
    }

public:
    const float preLaserDuration;
    const float laserDuration;
    const float shadowMarkDuration;
    const int nbShadowMark;
    const float obeliskDuration;
};

struct IsSarcophagePreLaserAttack final: public IComponent, public IIsStateDuration {
    IsSarcophagePreLaserAttack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSarcophageLaserAttack final: public IComponent, public IIsStateDuration {
    IsSarcophageLaserAttack(float newDuration): IIsStateDuration(newDuration) {}
};

class IsSarcophageShadowMark final: public IComponent, public IIsStateDuration {
public:
    IsSarcophageShadowMark(float newDuration, int newNbShadowMark):
        IIsStateDuration(newDuration),
        shadowMarkCooldown(newDuration / newNbShadowMark),
        curTime(0) {
    }

    bool canSpawnShadowMark(float delta) {
        curTime += delta;
        if (curTime >= shadowMarkCooldown) {
            curTime -= shadowMarkCooldown;
            return true;
        }
        return false;
    }

private:
    const float shadowMarkCooldown;
    float curTime;
};

struct IsSarcophageObelisk final: public IComponent, public IIsStateDuration {
    IsSarcophageObelisk(float newDuration): IIsStateDuration(newDuration) {}
};

class SarcophageObelisk final: public IComponent {};
class SarcophageShockwave final: public IComponent {};