#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void chestOpenSys(MainFixedSystem, World& world) {
    auto chests = world.view<const Transform2D, const OnCollisionEnter>(with<Chest>);

    auto [textureManager] = world.resource<TextureManager>();

    for (auto [chestEnt, chestTransform, collisions]: chests) {
        for (auto othEnt: collisions) {
            if (world.has_components<Player>(othEnt)) {
                auto [time] = world.resource<Time>();
                time.setTimeScale(0);

                std::unordered_map<std::size_t, BonusData> lastBonuses;
                for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
                    for (const auto& bonus: bonusVec) {
                        if (playerBonuses.getBonusLevel(bonus.type) < bonus.descriptionCallbackPerLevel.size()) {
                            lastBonuses.emplace(bonus.type, bonus);
                        }
                    }
                }

                std::unordered_set<std::size_t> bonusesIdx;
                for (std::size_t i = 0; i < (lastBonuses.size() < 1 ? lastBonuses.size() : 1); i++) {
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

                auto menuChest = instantiateMenuChestUI(world, glm::vec2(-72, -64));

                for (auto bonusIdx: bonusesIdx) {
                    world.append_children(menuChest, {
                        world.create_entity(
                            UI(textureManager, menuBonusIconsUV, bonusVec[bonusIdx].imgIconIdx, UIAnchor::CENTER_CENTER),
                            Transform2D(
                                glm::vec2(0, -32),
                                0,
                                glm::vec2(1, 1)
                            ),
                            ZIndex(1)
                        ),
                        world.create_entity(
                            UI(textureManager, menuBonusHUDUV, 5, UIAnchor::CENTER_CENTER),
                            Animation(menuBonusHUDAnim, MenuBonusHUDAnimType::SMALL_SELECTOR, AnimType::UNSCALED),
                            Transform2D(
                                glm::vec2(-16, -48),
                                0,
                                glm::vec2(1, 1)
                            ),
                            ZIndex(1)
                        ),
                        world.create_entity(
                            TextUICreator(bonusVec[bonusIdx].name, "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(64, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                            Transform2D(
                                glm::vec2(-32, -16),
                                0,
                                glm::vec2(1, 1)
                            ),
                            ZIndex(1)
                        )
                    });

                    // Add Bonus On Player
                    for (auto [_, playerBonuses]: world.view<PlayerBonuses>()) {
                        playerBonuses.addBonus(bonusVec[bonusIdx].type);
                    }
                    if (bonusVec[bonusIdx].descriptionCallbackPerLevel[0].callback) {
                        bonusVec[bonusIdx].descriptionCallbackPerLevel[0].callback(world);
                    }
                }

                instantiateWarp(world, chestTransform.getPosition() + glm::vec2(0, 32));
                world.delete_entity(chestEnt);
            }
        }
    }
}
