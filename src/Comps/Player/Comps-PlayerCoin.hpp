#pragma once

#include <Zerengine.hpp>

class PlayerCoin final: public IComponent {
public:
    PlayerCoin(float new_coins):
        curCoin(new_coins) {
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

class PlayerCoinText final: public IComponent {};