#pragma once

#include <Zerengine.hpp>

class MenuBonus {};

class MenuBonusSelector {
public:
    MenuBonusSelector(int newNbElements):
        nbElements(newNbElements),
        curElement(0) {
    }

    bool nextElement() {
        curElement++;
        if (curElement >= nbElements) {
            curElement = nbElements - 1;
            return false;
        }
        return true;
    }

    bool previousElement() {
        curElement--;
        if (curElement < 0) {
            curElement = 0;
            return false;
        }
        return true;
    }

    int getCurElement() const {
        return curElement;
    }

private:
    const int nbElements;
    int curElement;
};