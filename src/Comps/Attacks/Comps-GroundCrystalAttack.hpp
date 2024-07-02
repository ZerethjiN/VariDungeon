#pragma once

#include <Zerengine.hpp>

class GroundCrystalAttack final {
public:
    GroundCrystalAttack(float newCrossDuration, float newMineralDuration):
        crossDuration(newCrossDuration),
        mineralDuration(newMineralDuration) {
    }

public:
    const float crossDuration;
    const float mineralDuration;
};

struct IsGroundCrystalAttackCross final: public IIsStateDuration {
    IsGroundCrystalAttackCross(float newDuration): IIsStateDuration(newDuration) {}
};