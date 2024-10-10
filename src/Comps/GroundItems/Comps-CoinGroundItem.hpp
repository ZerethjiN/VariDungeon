#pragma once

#include <Zerengine.hpp>

class CoinGroundItem final: public IComponent {
public:
    CoinGroundItem(float newAmount):
        amount(newAmount) {
    }

    float getAmount() const {
        return amount;
    }

private:
    const float amount;
};