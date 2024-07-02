#pragma once

#include <Zerengine.hpp>

class PlayerXp final {
public:
    PlayerXp(float newNbXpForNextLvl):
        nbXpForNextLvl(newNbXpForNextLvl),
        curXp(0) {
    }

    void addXp(float newAmount) {
        curXp += newAmount;
    }

    bool isLevelUp() {
        if (curXp >= nbXpForNextLvl) {
            curXp -= nbXpForNextLvl;
            nbXpForNextLvl *= 1.5;
            return true;
        }
        return false;
    }

    float getNbXpForNextLvl() const {
        return nbXpForNextLvl;
    }

    float getCurXp() const {
        return curXp;
    }

private:
    float nbXpForNextLvl;
    float curXp;
};

class PlayerXpText final {};
class PlayerXpBarInner final {
public:
    PlayerXpBarInner(float newMaxLength):
        maxLength(newMaxLength) {
    }

    float getMaxLength() const {
        return maxLength;
    }

private:
    const float maxLength;
};