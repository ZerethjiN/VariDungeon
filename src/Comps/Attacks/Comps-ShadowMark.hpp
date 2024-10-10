#pragma once

#include <Zerengine.hpp>

class ShadowMark final: public IComponent {
public:
    ShadowMark(float newPreExplosionDuration, float newExplosionDuration):
        preExplosionDuration(newPreExplosionDuration),
        explosionDuration(newExplosionDuration) {
    }

public:
    const float preExplosionDuration;
    const float explosionDuration;
};

struct IsShadowMarkPreExplosion final: public IComponent, public IIsStateDuration {
    IsShadowMarkPreExplosion(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsShadowMarkExplosion final: public IComponent, public IIsStateDuration {
    IsShadowMarkExplosion(float newDuration): IIsStateDuration(newDuration) {}
};