#pragma once

#include <Zerengine.hpp>

class SlimeLvl2 {
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

struct IsSlimeLvl2Move: public IIsStateDuration {
    IsSlimeLvl2Move(float newDuration): IIsStateDuration(newDuration) {}
};

struct IsSlimeLvl2Jump: public IIsStateDuration {
    IsSlimeLvl2Jump(float newDuration): IIsStateDuration(newDuration) {}
};