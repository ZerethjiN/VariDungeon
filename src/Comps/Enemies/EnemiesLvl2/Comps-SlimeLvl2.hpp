#pragma once

#include <Zerengine.hpp>

class SlimeLvl2 final: public IComponent {
public:
    SlimeLvl2(float newMoveDuration, float newJumpDuration, float newJumpSpeedCoeff):
        moveDuration(newMoveDuration),
        jumpDuration(newJumpDuration),
        jumpSpeedCoeff(newJumpSpeedCoeff) {
    }

public:
    const float moveDuration;
    const float jumpDuration;
    const float jumpSpeedCoeff;

public:
    glm::vec4 tmpCollider;
};

struct IsSlimeLvl2Move final: public IComponent, public IIsStateDuration {
    IsSlimeLvl2Move(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSlimeLvl2Jump final: public IComponent, public IIsStateDuration {
    IsSlimeLvl2Jump(float newDuration): IIsStateDuration(newDuration) {}
};