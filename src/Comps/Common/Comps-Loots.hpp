#pragma once

#include <Zerengine.hpp>

enum LootType: size_t {
    LOOT_TYPE_XP,
    LOOT_TYPE_COIN,
    LOOT_TYPE_HEART
};

struct LootTuple final {
    std::size_t lootType;
    std::size_t minLootDrop;
    std::size_t maxLootDrop;
};

class Loots final {
public:
    [[nodiscard]] constexpr Loots(const std::initializer_list<LootTuple>& newLoots = {}) noexcept:
        loots(newLoots) {
    }

    [[nodiscard]] constexpr std::vector<LootTuple>::const_iterator begin() const noexcept {
        return loots.begin();
    }

    [[nodiscard]] constexpr std::vector<LootTuple>::const_iterator end() const noexcept {
        return loots.end();
    }

    [[nodiscard]] constexpr const LootTuple& operator [](std::size_t index) const noexcept {
        return loots[index];
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept {
        return loots.size();
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return loots.empty();
    }

private:
    const std::vector<LootTuple> loots;
};