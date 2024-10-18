#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void chest_collision_sys(MainFixedSystem, World& world) {
    auto chests = world.query<const OnCollisionEnter, const Transform2D>(with<Chest>, without<ChestOpening, Animation>);

    for (auto [chest_ent, collisions, chest_transform]: chests) {
        for (const auto& oth_ent: collisions) {
            if (world.has_components<Player>(oth_ent)) {
                world.add_components(chest_ent,
                    ChestOpening(chestAnim[ChestAnimType::OPENING].getTotalDuration()),
                    Animation(chestAnim, ChestAnimType::OPENING),
                    ChestOpeningLoot(chestAnim[ChestAnimType::OPENING].getTotalDuration() / 8)
                );
                for (auto i = 0; i < 1; i++) {
                    float rndSpreadDirection = std::rand() % 360;
                    instantiateCoinParticle(
                        world,
                        chest_transform.getPosition(),
                        0.25f,
                        glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                        32.f
                    );
                }
            }
        }
    }
}

void chest_opening_loot_sys(MainFixedSystem, World& world) {
    auto chests = world.query<ChestOpeningLoot, const Transform2D>(with<Chest>);

    auto [time] = world.resource<const Time>();

    for (auto [_, chest_opening_loot, chest_transform]: chests) {
        if (chest_opening_loot.canTick(time.fixedDelta())) {
            for (auto i = 0; i < 1; i++) {
                float rndSpreadDirection = std::rand() % 360;
                instantiateCoinParticle(
                    world,
                    chest_transform.getPosition(),
                    0.25f,
                    glm::normalize(rotateAround(glm::vec2(1, 1), glm::vec2(1, 1), rndSpreadDirection)),
                    32.f
                );
            }
        }
    }
}

void chest_opening_sys(MainFixedSystem, World& world) {
    auto chests = world.query<ChestOpening, const Transform2D>(with<Chest>);

    auto [textureManager, time] = world.resource<TextureManager, Time>();

    for (auto [chestEnt, chest_opening, chestTransform]: chests) {
        if (chest_opening.canSwitchState(time.fixedDelta())) {
            time.setTimeScale(0);

            std::unordered_map<BonusType, BonusData> lastBonuses;
            for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                for (const auto& bonus: bonusVec) {
                    if (playerBonuses.getBonusLevel(static_cast<std::size_t>(bonus.type)) < bonus.descriptionCallbackPerLevel.size()) {
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
                    for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                        alreadyLevelMax |= (playerBonuses.getBonusLevel(static_cast<std::size_t>(bonusVec[newBonusIdx].type)) >= bonusVec[newBonusIdx].descriptionCallbackPerLevel.size());
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
                std::size_t bonusLevel = 0;
                for (auto [_, playerBonuses]: world.query<PlayerBonuses>()) {
                    playerBonuses.addBonus(static_cast<std::size_t>(bonusVec[bonusIdx].type));
                    bonusLevel = playerBonuses.getBonusLevel(static_cast<std::size_t>(bonusVec[bonusIdx].type));
                }
                if (bonusVec[bonusIdx].descriptionCallbackPerLevel[bonusLevel].callback) {
                    bonusVec[bonusIdx].descriptionCallbackPerLevel[bonusLevel].callback(bonusCallback, world);
                }
            }

            for (auto [_, room_transform]: world.query<const Transform2D>(with<ChunkInfos>)) {
                instantiateWarp(world, room_transform.getPosition() + glm::vec2(-8, -8));
            }

            world.delete_entity(chestEnt);
        }
    }
}
