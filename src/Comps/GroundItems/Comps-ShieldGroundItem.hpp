#pragma once

#include <Zerengine.hpp>

class ShieldGroundItem final: public IComponent {
public:
    ShieldGroundItem(float newAmount):
        amount(newAmount) {
    }

    float getAmount() const {
        return amount;
    }

private:
    const float amount;
};