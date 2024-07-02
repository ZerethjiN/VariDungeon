#pragma once

#include <Zerengine.hpp>

class PlayerCoin final {
public:
    PlayerCoin():
        curCoin(0) {
    }

    PlayerCoin& operator +=(float newAmount) {
        curCoin += newAmount;
        return *this;
    }

    PlayerCoin& operator -=(float newAmount) {
        curCoin -= newAmount;
        return *this;
    }

    float getCurCoin() const {
        return curCoin;
    }

private:
    float curCoin;
};

class PlayerCoinText final {};