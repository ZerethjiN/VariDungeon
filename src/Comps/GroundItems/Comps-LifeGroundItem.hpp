#pragma once

#include <Zerengine.hpp>

class LifeGroundItem final: public IComponent {
public:
    LifeGroundItem(float newAmount):
        amount(newAmount) {
    }

    float getAmount() const {
        return amount;
    }

private:
    const float amount;
};