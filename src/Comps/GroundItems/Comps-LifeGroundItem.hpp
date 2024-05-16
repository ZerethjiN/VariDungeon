#pragma once

#include <Zerengine.hpp>

class LifeGroundItem {
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