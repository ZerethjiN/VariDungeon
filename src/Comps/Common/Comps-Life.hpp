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

    bool isDead() const {
        return curNbLife <= 0;
    }

    float getCurNbLife() const {
        return curNbLife;
    }

private:
    float nbLife;
    float curNbLife;
};