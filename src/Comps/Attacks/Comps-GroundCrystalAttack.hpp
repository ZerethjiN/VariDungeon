#pragma once

#include <Zerengine.hpp>

class GroundCrystalAttack final: public IComponent {
public:
    GroundCrystalAttack(float newCrossDuration, float newMineralDuration):
        crossDuration(newCrossDuration),
        mineralDuration(newMineralDuration) {
    }

public:
    const float crossDuration;
    const float mineralDuration;
};

struct IsGroundCrystalAttackCross final: public IComponent, public IIsStateDuration {
    IsGroundCrystalAttackCross(float newDuration): IIsStateDuration(newDuration) {}
};