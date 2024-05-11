#pragma once

#include <Zerengine.hpp>

class UIView: public ZreView {
public:
    UIView(const glm::vec4& newRect):
        ZreView(newRect) {
    }
};