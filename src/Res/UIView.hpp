#pragma once

#include <Zerengine.hpp>

class UIView final: public ZreView {
public:
    UIView(const glm::vec4& newRect):
        ZreView(newRect) {
    }
};