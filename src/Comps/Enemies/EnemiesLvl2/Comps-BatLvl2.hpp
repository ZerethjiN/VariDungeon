#pragma once

#include <Zerengine.hpp>

class BatLvl2 {
public:
    BatLvl2(float newMoveDuration, float newAttackDuration, float newAttackRadius):
        moveDuration(newMoveDuration),
        attackDuration(newAttackDuration),
        attackRadius(newAttackRadius) {
    }

public:
    const float moveDuration;
    const float attackDuration;
    const float attackRadius;
};

struct IsBatLvl2Move: public IIsStateDuration {
    IsBatLvl2Move(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsBatLvl2Attack: public IIsStateDuration {
    IsBatLvl2Attack(float newDuration): IIsStateDuration(newDuration) {}
};