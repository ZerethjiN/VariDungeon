#pragma once

#include <Zerengine.hpp>

class Spectre {
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

struct IsSpectreMove: public IIsStateDuration {
    IsSpectreMove(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSpectreVanish: public IIsStateDuration {
    IsSpectreVanish(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSpectreCast: public IIsStateDuration {
    IsSpectreCast(float newDuration): IIsStateDuration(newDuration) {}
};