#pragma once

#include <Zerengine.hpp>

class InGameView: public ZreView {
public:
    InGameView(const glm::vec4& newRect):
        ZreView(newRect) {
    }
};