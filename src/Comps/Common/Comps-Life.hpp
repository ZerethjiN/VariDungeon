#pragma once

#include <Zerengine.hpp>

class Life final: public IComponent {
public:
    Life(float newNbLife):
        nbLife(newNbLife),
        curNbLife(newNbLife),
        curNbShield(0) {
    }

    Life& operator -=(float damage) {
        if (curNbShield > 0) {
            curNbShield -= damage;
            if (curNbShield < 0) {
                // curNbLife += curNbShield;
                curNbShield = 0;
            }
        } else {
            curNbLife -= damage;
            if (curNbLife < 0) {
                curNbLife = 0;
            }
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

    void addShield(float newShield) {
        curNbShield += newShield;
        if (curNbShield > nbLife) {
            curNbShield = nbLife;
        }
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

    float getCurNbShield() const {
        return curNbShield;
    }

private:
    float nbLife;
    float curNbLife;

    float curNbShield;
};