#pragma once

#include <Zerengine.hpp>

class XpGroundItem final: public IComponent {
public:
    XpGroundItem(float newAmount):
        amount(newAmount) {
    }

    float getAmount() const {
        return amount;
    }

private:
    const float amount;
};