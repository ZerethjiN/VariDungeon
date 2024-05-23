#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>

Ent instantiateMenuBonusUI(World& world, const glm::vec2& position, const std::unordered_set<std::size_t>& bonusesIdx) {
    auto backgroundEnt = world.newEnt(
        MenuBonus(),
        UICreator(menuBonusHUDUV, UIAnchor::CENTER_CENTER),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        ),
        ZIndex(0)
    );

    world.appendChildren(backgroundEnt, {
        world.newEnt(
            MenuBonusSelector(bonusesIdx.size()),
            UICreator(menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
            Animation(menuBonusHUDAnim, "MediumSelector", AnimType::UNSCALED),
            Transform(
                position + glm::vec2(8, 8),
                0,
                glm::vec2(1, 1)
            ),
            ZIndex(1)
        )
    });

    // Ajout des bonus:
    int i = 0;
    for (auto bonusIdx: bonusesIdx) {
        std::size_t bonusLevel = 0;
        for (auto [_, playerBonuses]: world.view<const PlayerBonuses>()) {
            bonusLevel = playerBonuses.getBonusLevel(bonusVec[bonusIdx].type);
        }

        if (bonusVec[bonusIdx].descriptionCallbackPerLevel.empty()) {
            continue;
        }

        world.appendChildren(backgroundEnt, {
            world.newEnt(
                BonusRow(i, bonusVec[bonusIdx].type, bonusVec[bonusIdx].descriptionCallbackPerLevel[bonusLevel].callback),
                UICreator(menuBonusIconsUV, bonusVec[bonusIdx].imgIconIdx, UIAnchor::CENTER_CENTER),
                Transform(
                    position + glm::vec2(8, 8 + i * 32),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            ),
            world.newEnt(
                TextUICreator(bonusVec[bonusIdx].name, "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                Transform(
                    position + glm::vec2(40, 12 + i * 32),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(1)
            )
        });
        i++;
    }

    return backgroundEnt;
}