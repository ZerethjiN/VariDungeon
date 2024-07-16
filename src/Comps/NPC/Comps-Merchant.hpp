#pragma once

#include <Zerengine.hpp>

class Merchant final {};

class MerchantBonus final {
public:
    MerchantBonus(const std::unordered_map<BonusType, std::size_t>& newTypeToIdx, const std::unordered_set<std::size_t>& newBonusesIdx):
        typeToIdx(newTypeToIdx),
        bonusesIdx(newBonusesIdx) {
    }

public:
    const std::unordered_map<BonusType, std::size_t> typeToIdx;
    std::unordered_set<std::size_t> bonusesIdx;
};

class MerchantRadius final {};