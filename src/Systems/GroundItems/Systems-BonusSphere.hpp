#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void getBonusSphereSys(MainFixedSystem, World& world) {
    auto spheres = world.view<const OnCollisionEnter>(with<BonusSphere>);

    for (auto [sphereEnt, collisions]: spheres) {
        for (auto othEnt: collisions) {
            if (world.has_components<Player>(othEnt)) {
                world.delete_entity(sphereEnt);

                // Stop Time:
                auto [time] = world.resource<Time>();
                time.setTimeScale(0.0f);

                // Menu Bonus:
                std::unordered_map<std::size_t, BonusData> lastBonuses;
                for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
                    for (const auto& bonus: bonusVec) {
                        if (playerBonuses.getBonusLevel(bonus.type) < bonus.descriptionCallbackPerLevel.size()) {
                            lastBonuses.emplace(bonus.type, bonus);
                        }
                    }
                }

                std::unordered_set<std::size_t> bonusesIdx;
                for (std::size_t i = 0; i < (lastBonuses.size() < 3 ? lastBonuses.size() : 3); i++) {
                    std::size_t newBonusIdx;
                    bool alreadyLevelMax;
                    do {
                        alreadyLevelMax = false;
                        newBonusIdx = rand() % bonusVec.size();
                        alreadyLevelMax |= bonusVec[newBonusIdx].descriptionCallbackPerLevel.empty();
                        for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
                            alreadyLevelMax |= (playerBonuses.getBonusLevel(bonusVec[newBonusIdx].type) >= bonusVec[newBonusIdx].descriptionCallbackPerLevel.size());
                        }
                    } while (bonusesIdx.contains(newBonusIdx) || alreadyLevelMax);
                    bonusesIdx.emplace(newBonusIdx);
                }

                instantiateMenuBonusUI(world, glm::vec2(-72, -64), bonusesIdx);
            }
        }
    }
}