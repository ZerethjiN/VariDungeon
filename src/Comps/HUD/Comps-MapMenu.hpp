#pragma once
#include <Zerengine.hpp>

class MapMenu final {};

class MapMenuCell final {};

class MapMenuReverseTranslation final {
public:
    MapMenuReverseTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};

class MapMenuTranslation final {
public:
    MapMenuTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};