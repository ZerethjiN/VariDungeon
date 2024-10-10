#pragma once

#include <Zerengine.hpp>

class HomeMenuBackgroundSlide final: public IComponent {
public:
    HomeMenuBackgroundSlide(const glm::vec2& newDestination, const glm::vec2& newRollbackDestination, float newSpeed):
        destination(newDestination),
        rollbackDestination(newRollbackDestination),
        speed(newSpeed) {
    }

public:
    const glm::vec2 destination;
    const glm::vec2 rollbackDestination;
    const float speed;
};

class HomeMenuButtonId final: public IComponent {
public:
    HomeMenuButtonId(std::size_t newButtonId):
        buttonId(newButtonId) {
    }

public:
    const std::size_t buttonId;
};

class HomeMenuButtonCallback final: public IComponent {
public:
    HomeMenuButtonCallback(void(*const newCallback)(World&, Ent)):
        callback(newCallback) {
    }

public:
    void(*const callback)(World&, Ent);
};

class HomeMenuSelectedButton final: public IComponent {};

class HomeMenuSelector final: public IComponent {
public:
    HomeMenuSelector(std::size_t newNbElements, std::size_t newCurElement = 0):
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

class HomeMenuSelectorMoveDown final: public IComponent {
public:
    HomeMenuSelectorMoveDown(const glm::vec2& newDestination, float newSpeed):
        destination(newDestination),
        speed(newSpeed) {
    }

public:
    const glm::vec2 destination;
    const float speed;
};

class HomeMenuSelectorMoveUp final: public IComponent {
public:
    HomeMenuSelectorMoveUp(const glm::vec2& newDestination, float newSpeed):
        destination(newDestination),
        speed(newSpeed) {
    }

public:
    const glm::vec2 destination;
    const float speed;
};