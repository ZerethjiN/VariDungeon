#pragma once

#include <Zerengine.hpp>

enum class BonusType: std::size_t {
    MAGNIFIER,
    KNOCKBACK,
    ATTACK_SPEED,
    COMBO_DOUBLE_XP,
    COMBO_FRAGMENTATION_BOMB,
    HEALTH,
    // SHIELD,
    SPEED,
    // BONUS_GOLD,
    STRENGTH,
    DAGGER,
    LASER,
    SHURIKEN,
    FLAME,
    STUN,
    COMBO_TORNADO,
    COMBO_FIRE_SWORD,
    COMBO_SAI,
    BOMB,
    LOOT_CHANCE,
    ELECTRICAL_ORB
};

class BonusCallback final {};
static constexpr inline BonusCallback bonusCallback;

struct DescriptionAndCallback {
    std::string description;
    std::function<void(BonusCallback, World&)> callback;
};

class BonusData final: public IComponent {
public:
    BonusData(BonusType newType, std::size_t newImgIconIdx, const std::string& newName, float newCost, const std::vector<DescriptionAndCallback>& newDescriptionCallbackPerLevel):
        type(newType),
        imgIconIdx(newImgIconIdx),
        name(newName),
        cost(newCost),
        descriptionCallbackPerLevel(newDescriptionCallbackPerLevel) {
    }

public:
    BonusType type;
    std::size_t imgIconIdx;
    std::string name;
    float cost;
    std::vector<DescriptionAndCallback> descriptionCallbackPerLevel;
};

void daggerBonusCallbackLvl1(BonusCallback, World&);
void strengthBonusCallbackLvl1(BonusCallback, World&);
void strengthBonusCallbackLvl2(BonusCallback, World&);
void strengthBonusCallbackLvl3(BonusCallback, World&);
void shurikenBonusCallbackLvl1(BonusCallback, World&);
void laserBonusCallbackLvl1(BonusCallback, World&);
void laserBonusCallbackLvl2(BonusCallback, World&);
void laserBonusCallbackLvl3(BonusCallback, World&);
void speedBonusCallbackLvl1(BonusCallback, World&);
void speedBonusCallbackLvl2(BonusCallback, World&);
void speedBonusCallbackLvl3(BonusCallback, World&);
void healthBonusCallbackLvl1(BonusCallback, World&);
void healthBonusCallbackLvl2(BonusCallback, World&);
void healthBonusCallbackLvl3(BonusCallback, World&);
void attackSpeedBonusCallbackLvl1(BonusCallback, World&);
void attackSpeedBonusCallbackLvl2(BonusCallback, World&);
void attackSpeedBonusCallbackLvl3(BonusCallback, World&);
void knockbackBonusCallbackLvl1(BonusCallback, World&);
void knockbackBonusCallbackLvl2(BonusCallback, World&);
void knockbackBonusCallbackLvl3(BonusCallback, World&);
void bombBonusCallbackLvl1(BonusCallback, World&);
void bombBonusCallbackLvl2(BonusCallback, World&);
void bombBonusCallbackLvl3(BonusCallback, World&);
void lightningBallBonusCallbackLvl1(BonusCallback, World&);

static const std::vector<BonusData> bonusVec {
    BonusData(BonusType::STRENGTH, 9, "Strength", 45, {
        {"Increase damage by 25%", strengthBonusCallbackLvl1},
        {"Increase damage by 25%", strengthBonusCallbackLvl2},
        {"Increase damage by 25%", strengthBonusCallbackLvl3}
    }),
    BonusData(BonusType::DAGGER, 10, "Dagger", 30, {
        {"Throw daggers periodically", daggerBonusCallbackLvl1}
    }),
    BonusData(BonusType::SHURIKEN, 12, "Shuriken", 45, {
        {"Create 2 shurikens", shurikenBonusCallbackLvl1}
    }),
    BonusData(BonusType::LASER, 11, "Laser", 30, {
        {"Shoot lasers", laserBonusCallbackLvl1},
        {"Reduce laser cooldown by 0.10 seconds", laserBonusCallbackLvl2},
        {"Reduce laser cooldown by 0.15 seconds", laserBonusCallbackLvl3}
    }),
    BonusData(BonusType::SPEED, 7, "Speed", 30, {
        {"Increase speed by 8%", speedBonusCallbackLvl1},
        {"Increase speed by 8%", speedBonusCallbackLvl2},
        {"Increase speed by 8%", speedBonusCallbackLvl3}
    }),
    BonusData(BonusType::HEALTH, 5, "Health", 45, {
        {"Increase max health by 25%", healthBonusCallbackLvl1},
        {"Increase max health by 25%", healthBonusCallbackLvl2},
        {"Increase max health by 25%", healthBonusCallbackLvl3}
    }),
    BonusData(BonusType::ATTACK_SPEED, 2, "Attack Speed", 30, {
        {"Increase attack and spell speed by 5%", attackSpeedBonusCallbackLvl1},
        {"Increase attack and spell speed by 5%", attackSpeedBonusCallbackLvl2},
        {"Increase attack and spell speed by 5%", attackSpeedBonusCallbackLvl3}
    }),
    BonusData(BonusType::KNOCKBACK, 1, "Knockback", 30, {
        {"Increase knockback by 8%", knockbackBonusCallbackLvl1},
        {"Increase knockback by 8%", knockbackBonusCallbackLvl2},
        {"Increase knockback by 8%", knockbackBonusCallbackLvl3}
    }),
    BonusData(BonusType::BOMB, 18, "Bomb", 30, {
        {"Drop bombs periodically", bombBonusCallbackLvl1},
        {"Reduce bomb cooldown by 0.5 seconds", bombBonusCallbackLvl2},
        {"Reduce bomb cooldown by 0.5 seconds", bombBonusCallbackLvl3},
    }),
    BonusData(BonusType::ELECTRICAL_ORB, 20, "Lightning Ball", 45, {
        {"Throw electrical orbs periodically", lightningBallBonusCallbackLvl1}
    }),
};

class BonusRow final: public IComponent {
public:
    BonusRow(std::size_t new_id, BonusType new_type, float new_cost, std::function<void(BonusCallback, World&)> new_callback):
        id(new_id),
        type(new_type),
        cost(new_cost),
        callback(new_callback) {
    }

    bool hasCallback() const {
        return callback != nullptr;
    }

    void operator()(World& world) const {
        callback(bonusCallback, world);
    }

public:
    const std::size_t id;
    const BonusType type;
    const float cost;
    const std::function<void(BonusCallback, World&)> callback;
};