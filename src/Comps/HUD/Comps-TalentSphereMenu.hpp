#pragma once

#include <Zerengine.hpp>

class TalentSphereMenu final: public IComponent {};

class TalentSphereMenuReverseTranslation final: public IComponent {
public:
    TalentSphereMenuReverseTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};

class TalentSphereMenuTranslation final: public IComponent {
public:
    TalentSphereMenuTranslation(const glm::vec2& newFinalPosition, float newTranslationSpeed):
        finalPosition(newFinalPosition),
        translationSpeed(newTranslationSpeed) {
    }

public:
    const glm::vec2 finalPosition;
    const float translationSpeed;
};