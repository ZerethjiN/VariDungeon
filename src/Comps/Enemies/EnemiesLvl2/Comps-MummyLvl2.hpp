#pragma once

#include <Zerengine.hpp>

class MummyLvl2 final: public IComponent {
public:
    MummyLvl2(float newMoveDuration, float newPreAttackDuration, float newAttackDuration, float newAttackRadius):
        moveDuration(newMoveDuration),
        preAttackDuration(newPreAttackDuration),
        attackDuration(newAttackDuration),
        attackRadius(newAttackRadius) {
    }

public:
    const float moveDuration;
    const float preAttackDuration;
    const float attackDuration;
    const float attackRadius;
};

struct IsMummyLvl2Move final: public IComponent, public IIsTickDuration {
    IsMummyLvl2Move(float newDuration): IIsTickDuration(newDuration) {}
};

struct IsMummyLvl2PreAttack final: public IComponent, public IIsStateDuration {
    IsMummyLvl2PreAttack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsMummyLvl2Attack final: public IComponent, public IIsStateDuration {
    IsMummyLvl2Attack(float newDuration): IIsStateDuration(newDuration) {}
};