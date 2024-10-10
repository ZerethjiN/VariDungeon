#pragma once

#include <Zerengine.hpp>

class AnubisLvl2 final: public IComponent {
public:
    AnubisLvl2(float newAttackDuration, float newVanishDuration):
        attackDuration(newAttackDuration),
        vanishDuration(newVanishDuration),
        tmpCol() {
    }

public:
    const float attackDuration;
    const float vanishDuration;

public:
    glm::vec4 tmpCol;
};

struct IsAnubisLvl2Attack final: public IComponent, IIsStateDuration {
    IsAnubisLvl2Attack(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsAnubisLvl2Vanish final: public IComponent, IIsStateDuration {
    IsAnubisLvl2Vanish(float newDuration): IIsStateDuration(newDuration) {}
};