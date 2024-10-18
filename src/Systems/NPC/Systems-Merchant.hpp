#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void merchantOpenCloseSys(MainFixedSystem, World& world) {
    auto merchants = world.query<const OnCollisionStay>(with<MerchantRadius>);

    auto [time] = world.resource<Time>();

    if (world.query(with<MenuBonus>).empty()) {
        for (auto [merchantRadisuEnt, collisions]: merchants) {
            for (auto othEnt: collisions) {
                if (world.has_components<Player>(othEnt)) {
                    if (vulkanEngine.window.isKeyDown(ButtonNameType::A_BUTTON)) {
                        time.setTimeScale(0);

                        std::unordered_set<std::size_t> bonusesIdx;

                        auto merchantBonuses = world.query<const MerchantBonus>();

                        if (merchantBonuses.empty()) {
                            std::unordered_map<BonusType, std::size_t> typeToIdx;

                            std::unordered_map<BonusType, BonusData> lastBonuses;
                            for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                                for (const auto& bonus: bonusVec) {
                                    if (playerBonuses.getBonusLevel(static_cast<std::size_t>(bonus.type)) < bonus.descriptionCallbackPerLevel.size()) {
                                        lastBonuses.emplace(bonus.type, bonus);
                                    }
                                }
                            }

                            for (std::size_t i = 0; i < (lastBonuses.size() < 3 ? lastBonuses.size() : 3); i++) {
                                std::size_t newBonusIdx;
                                bool alreadyLevelMax;
                                do {
                                    alreadyLevelMax = false;
                                    newBonusIdx = rand() % bonusVec.size();
                                    alreadyLevelMax |= bonusVec[newBonusIdx].descriptionCallbackPerLevel.empty();
                                    for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                                        alreadyLevelMax |= (playerBonuses.getBonusLevel(static_cast<std::size_t>(bonusVec[newBonusIdx].type)) >= bonusVec[newBonusIdx].descriptionCallbackPerLevel.size());
                                    }
                                } while (bonusesIdx.contains(newBonusIdx) || alreadyLevelMax);
                                bonusesIdx.emplace(newBonusIdx);
                                typeToIdx.emplace(bonusVec[newBonusIdx].type, newBonusIdx);
                            }

                            for (auto [merchantEnt]: world.query(with<Merchant>)) {
                                world.add_components(merchantEnt, MerchantBonus(typeToIdx, bonusesIdx));
                            }
                        } else {
                            for (auto [merchantEnt, merchantBonus]: merchantBonuses) {
                                bonusesIdx = merchantBonus.bonusesIdx;
                            }
                        }

                        instantiateMenuBonusMerchantUI(world, glm::vec2(-72, -64), bonusesIdx);

                        break;
                    }
                }
            }
        }
    }
}