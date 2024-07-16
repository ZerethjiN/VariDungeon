#pragma once

#include <Zerengine.hpp>

class PlayerCoin final {
public:
    PlayerCoin():
        curCoin(100) {
    }

    PlayerCoin& operator +=(float newAmount) {
        curCoin += newAmount;
        return *this;
    }

    PlayerCoin& operator -=(float newAmount) {
        curCoin -= newAmount;
        return *this;
    }

    operator float() const noexcept {
        return curCoin;
    }

    float getCurCoin() const {
        return curCoin;
    }

private:
    float curCoin;
};

class PlayerCoinText final {};