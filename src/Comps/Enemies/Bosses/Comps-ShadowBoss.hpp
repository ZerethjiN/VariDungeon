#pragma once
#include <Zerengine.hpp>

class ShadowBossHubPattern final {
public:
    ShadowBossHubPattern(const std::initializer_list<glm::vec2>& newMovePoints):
        movePoints(newMovePoints),
        curPoint(0) {
    }

public:
    const std::vector<glm::vec2> movePoints;
    int curPoint;
};