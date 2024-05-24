#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

#include "Others/GenerateDungeon.hpp"

void testScene(World& world) {
    // Purge
    auto [textureManager, fontManager, pipelineManager, time] = world.resource<TextureManager, FontManager, PipelineManager, Time>();
    textureManager.clear();
    fontManager.clear();
    pipelineManager.clear();

    // Reset Time
    time.setTimeScale(1.0f);

    world.newEnt(
        AmbientLight(glm::vec4(255, 255, 255, 255))
    );

    generateDungeon(world, glm::vec2(0, 0));

    instantiateInventoryBarUI(world, glm::vec2(-80, -16));

    // Alimentation des Bonus:
    // std::unordered_map<std::size_t, BonusData> lastBonuses;
    // // for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
    //     for (const auto& bonus: bonusVec) {
    //         // if (playerBonuses.getBonusLevel(bonus.type) < bonus.descriptionCallbackPerLevel.size()) {
    //             lastBonuses.emplace(bonus.type, bonus);
    //         // }
    //     }
    // // }

    // std::unordered_set<std::size_t> bonusesIdx;
    // for (int i = 0; i < (lastBonuses.size() < 3 ? lastBonuses.size() : 3); i++) {
    //     std::size_t newBonusIdx;
    //     bool alreadyLevelMax;
    //     do {
    //         alreadyLevelMax = false;
    //         newBonusIdx = rand() % bonusVec.size();
    //         alreadyLevelMax |= bonusVec[newBonusIdx].descriptionCallbackPerLevel.empty();
    //         for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
    //             alreadyLevelMax |= (playerBonuses.getBonusLevel(bonusVec[newBonusIdx].type) >= bonusVec[newBonusIdx].descriptionCallbackPerLevel.size());
    //         }
    //     } while (bonusesIdx.contains(newBonusIdx) || alreadyLevelMax);
    //     bonusesIdx.emplace(newBonusIdx);
    // }

    // instantiateMenuBonusUI(world, glm::vec2(-72, -64), bonusesIdx);
}