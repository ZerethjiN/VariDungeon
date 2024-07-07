#pragma once
#include <Zerengine.hpp>

class PauseMenu final {};

class PauseMenuReverseTranslation final {
public:
    PauseMenuReverseTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
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

class PauseMenuTranslation final {
public:
    PauseMenuTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

    const glm::vec2& getFinalPosition() const {
        return finalPosition;
    }

    float getTranslationSpeed() const {
        return translationSpeed;
    }

private:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};

class PauseMenuSelector final {
public:
    PauseMenuSelector(std::size_t newNbElements):
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

class PauseMenuSelectorMoveDown final {
public:
    PauseMenuSelectorMoveDown(const glm::vec2& newDestination, float newSpeed):
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

class PauseMenuSelectorMoveUp final {
public:
    PauseMenuSelectorMoveUp(const glm::vec2& newDestination, float newSpeed):
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