#pragma once

#include <Zerengine.hpp>

class CoinGroundItem {
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