#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuBonusUI(World&, const glm::vec2&, const std::unordered_set<std::size_t>&);

Ent instantiateBonusSphere(World& world, const glm::vec2& position) {
    auto [textureManager] = world.resource<TextureManager>();
    return world.append_children(
        // Parent
        world.create_entity(
            BonusSphere(),
            Sprite(textureManager, bonusSphereUV),
            Animation(bonusSphereAnim, BonusSphereAnimType::DEFAULT),
            Transform2D(
                position + glm::vec2(-8, -12),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(-1),
            InnerMovement(/*Duration:*/ 1, /*Speed:*/ 2),
            InnerMovementUp(),
            Lootable(),
            Velocity(),
            Trigger(-8 / 2, (-8 / 2) + 16, 8, 8),
            ParticleGenerator(
                /*Prefab:*/ instantiateParticleEffectStar,
                /*Cooldown:*/ 0.5f,
                /*Radius:*/ 12.f
            ),
            LootCallback([](World& world, const Ent& this_entity, const Ent& target_entity) {
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
            })
        ),
        // Children
        {
            world.create_entity(
                Sprite(textureManager, shadowUV),
                Animation(shadowAnim, ShadowAnimType::SMALL),
                Transform2D(
                    position + glm::vec2(-8, -4),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-2)
            )
        }
    );
}