#pragma once

#include <Zerengine.hpp>

class PlayerBonuses {
public:
    PlayerBonuses():
        bonusesLevels() {
    }

    void addBonus(std::size_t newBonus) {
        if (auto bonusesLevelsIt = bonusesLevels.find(newBonus); bonusesLevelsIt != bonusesLevels.end()) {
            bonusesLevelsIt->second++;
        } else {
            bonusesLevels.emplace(newBonus, 1);
        }
    }

    std::size_t getBonusLevel(std::size_t newBonus) const {
        if (auto bonusesLevelsIt = bonusesLevels.find(newBonus); bonusesLevelsIt != bonusesLevels.end()) {
            return bonusesLevelsIt->second;
        }
        return 0;
    }

private:
    std::unordered_map<std::size_t, std::size_t> bonusesLevels;
};