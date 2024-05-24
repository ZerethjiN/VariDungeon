#pragma once

#include <Zerengine.hpp>

class MenuBonus {};

class MenuBonusReverseTranslation {
public:
    MenuBonusReverseTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

    float getTranslationSpeed() const {
        return translationSpeed;
    }

    const glm::vec2& getFinalPosition() const {
        return finalPosition;
    }

private:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};

class MenuBonusTranslation {
public:
    MenuBonusTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed, const std::unordered_set<std::size_t>& newBonusesIdx):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed),
        bonusesIdx(newBonusesIdx) {
    }

    const glm::vec2& getFinalPosition() const {
        return finalPosition;
    }

    float getTranslationSpeed() const {
        return translationSpeed;
    }

    const std::unordered_set<std::size_t>& getBonusesIdx() const {
        return bonusesIdx;
    }

private:
    const glm::vec2 finalPosition;
    const float translationSpeed;
    const std::unordered_set<std::size_t> bonusesIdx;
};

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

class MenuBonusSelectorMoveDown {
public:
    MenuBonusSelectorMoveDown(const glm::vec2& newDestination, float newSpeed):
        destination(newDestination),
        speed(newSpeed) {
    }

    const glm::vec2& getDestination() const {
        return destination;
    }

    float getSpeed() const {
        return speed;
    }

private:
    const glm::vec2 destination;
    const float speed;
};

class MenuBonusSelectorMoveUp {
public:
    MenuBonusSelectorMoveUp(const glm::vec2& newDestination, float newSpeed):
        destination(newDestination),
        speed(newSpeed) {
    }

    const glm::vec2& getDestination() const {
        return destination;
    }

    float getSpeed() const {
        return speed;
    }

private:
    const glm::vec2 destination;
    const float speed;
};

class MenuBonusCurSelectedRow {
public:
    MenuBonusCurSelectedRow(float newMaxScale, float newMinScale, float newScaleSpeed):
        maxScale(newMaxScale),
        minScale(newMinScale),
        scaleSpeed(newScaleSpeed),
        isIncrease(true) {
    }

    void changeState() {
        isIncrease = !isIncrease;
    }

    float getMaxScale() const {
        return maxScale;
    }

    float getMinScale() const {
        return minScale;
    }

    float getScaleSpeed() const {
        return scaleSpeed;
    }

    bool getIsIncrease() const {
        return isIncrease;
    }

private:
    const float maxScale;
    const float minScale;
    const float scaleSpeed;
    bool isIncrease;
};