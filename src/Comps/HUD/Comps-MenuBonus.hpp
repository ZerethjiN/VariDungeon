#pragma once

#include <Zerengine.hpp>

class LevelUpKnockback final: public IComponent {
public:
    LevelUpKnockback(float newDuration):
        duration(newDuration),
        curTime(0) {
    }

    bool canSpawnPreMenu(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

private:
    const float duration;
    float curTime;
};

class LevelUpPreMenu final: public IComponent {
public:
    LevelUpPreMenu(float newDuration, int newNbStars):
        duration(newDuration),
        curTime(0),
        starSpawnDuration(newDuration / newNbStars),
        starSpawnCurTime(0) {
    }

    bool canSpawnMenu(float delta) {
        curTime += delta;
        return curTime >= duration;
    }

    bool canSpawnStar(float delta) {
        starSpawnCurTime += delta;
        if (starSpawnCurTime >= starSpawnDuration) {
            starSpawnCurTime -= starSpawnDuration;
            return true;
        }
        return false;
    }

private:
    const float duration;
    float curTime;

    const float starSpawnDuration;
    float starSpawnCurTime;
};

class MenuBonus final: public IComponent {};
class MenuBonusMerchant final: public IComponent {};

class MenuBonusPreReverseTranslation final: public IComponent, public IIsStateDuration {
public:
    MenuBonusPreReverseTranslation(float duration):
        IIsStateDuration(duration) {
    }
};

class MenuBonusReverseTranslation final: public IComponent {
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

class MenuBonusTranslation final: public IComponent {
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

class MenuBonusSelector final: public IComponent {
public:
    MenuBonusSelector(std::size_t newNbElements, std::size_t newCurElement = 0):
        nbElements(newNbElements),
        curElement(newCurElement) {
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
        if (curElement >= nbElements) {
            curElement = 0;
            return false;
        }
        return true;
    }

    std::size_t getCurElement() const {
        return curElement;
    }

private:
    const std::size_t nbElements;
    std::size_t curElement;
};

class MenuBonusSelectorMoveDown final: public IComponent {
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

class MenuBonusSelectorMoveUp final: public IComponent {
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

class MenuBonusCurSelectedRow final: public IComponent {
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