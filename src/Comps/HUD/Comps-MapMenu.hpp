#pragma once
#include <Zerengine.hpp>

class MapMenu final: public IComponent {};

class MapMenuCell final: public IComponent {};

class MapMenuReverseTranslation final: public IComponent {
public:
    MapMenuReverseTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};

class MapMenuTranslation final: public IComponent {
public:
    MapMenuTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};