#pragma once

#include <Zerengine.hpp>

class Life {
public:
    Life(float newNbLife):
        nbLife(newNbLife),
        curNbLife(newNbLife) {
    }

    Life& operator -=(float damage) {
        curNbLife -= damage;
        if (curNbLife < 0) {
            curNbLife = 0;
        }
        return *this;
    }

    Life& operator +=(float damage) {
        curNbLife += damage;
        if (curNbLife > nbLife) {
            curNbLife = nbLife;
        }
        return *this;
    }

    void increaseMaxLife(float newAmount) {
        curNbLife += newAmount;
        nbLife += newAmount;
    }

    bool isDead() const {
        return curNbLife <= 0;
    }

    float getCurNbLife() const {
        return curNbLife;
    }

    float getNbLife() const {
        return nbLife;
    }

private:
    float nbLife;
    float curNbLife;
};