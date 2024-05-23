#pragma once

#include <Zerengine.hpp>

enum BonusType: std::size_t {
    BONUS_MAGNIFIER,
    BONUS_KNOCKBACK,
    BONUS_ATTACK_SPEED,
    BONUS_COMBO_DOUBLE_XP,
    BONUS_COMBO_FRAGMENTATION_BOMB,
    BONUS_HEALTH,
    BONUS_SHIELD,
    BONUS_SPEED,
    BONUS_GOLD,
    BONUS_STRENGTH,
    BONUS_DAGGER,
    BONUS_LASER,
    BONUS_SHURIKEN,
    BONUS_FLAME,
    BONUS_STUN,
    BONUS_COMBO_TORNADO,
    BONUS_COMBO_FIRE_SWORD,
    BONUS_COMBO_SAI,
    BONUS_BOMB,
    BONUS_LOOT_CHANCE,
    BONUS_ELECTRICAL_ORB
};

struct DescriptionAndCallback {
    std::string description;
    void(*callback)(World&);
};

class BonusData final {
public:
    BonusData(BonusType newType, std::size_t newImgIconIdx, const std::string& newName, const std::vector<DescriptionAndCallback>& newDescriptionCallbackPerLevel):
        type(newType),
        imgIconIdx(newImgIconIdx),
        name(newName),
        descriptionCallbackPerLevel(newDescriptionCallbackPerLevel) {
    }

public:
    BonusType type;
    std::size_t imgIconIdx;
    std::string name;
    std::vector<DescriptionAndCallback> descriptionCallbackPerLevel;
};

void daggerBonusCallbackLvl1(World& world);
void strengthBonusCallbackLvl1(World& world);
void shurikenBonusCallbackLvl1(World& world);

static const std::vector<const BonusData> bonusVec {
    BonusData(BONUS_STRENGTH, 9, "Strength", {{"", strengthBonusCallbackLvl1}}),
    BonusData(BONUS_DAGGER, 10, "Dagger", {{"", daggerBonusCallbackLvl1}}),
    BonusData(BONUS_SHURIKEN, 12, "Shuriken", {{"", shurikenBonusCallbackLvl1}}),
    BonusData(BONUS_LASER, 11, "Laser", {}),
};

class BonusRow {
public:
    BonusRow(std::size_t newId, BonusType newType, void(*newCallback)(World&)):
        id(newId),
        type(newType),
        callback(newCallback) {
    }

    std::size_t getId() const {
        return id;
    }

    bool hasCallback() const {
        return callback != nullptr;
    }

    BonusType getType() const {
        return type;
    }

    void operator()(World& world) const {
        callback(world);
    }

private:
    const std::size_t id;
    const BonusType type;
    void(*const callback)(World&);
};