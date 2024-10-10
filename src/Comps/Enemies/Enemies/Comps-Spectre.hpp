#pragma once

#include <Zerengine.hpp>

class Spectre final: public IComponent {
public:
    Spectre(float newMoveDuration, float newVanishDuration, float newCastDuration):
        moveDuration(newMoveDuration),
        vanishDuration(newVanishDuration),
        castDuration(newCastDuration) {
    }

public:
    const float moveDuration;
    const float vanishDuration;
    const float castDuration;
};

struct IsSpectreMove final: public IComponent, public IIsStateDuration {
    IsSpectreMove(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSpectreVanish final: public IComponent, public IIsStateDuration {
    IsSpectreVanish(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSpectreCast final: public IComponent, public IIsStateDuration {
    IsSpectreCast(float newDuration): IIsStateDuration(newDuration) {}
};