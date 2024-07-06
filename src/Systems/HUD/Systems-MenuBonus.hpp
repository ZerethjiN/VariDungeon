#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void levelUpKnockbackSys(MainFixedSystem, World& world) {
    auto preMenus = world.view<LevelUpKnockback, Transform>();

    auto [time] = world.resource<Time>();

    for (auto [preMenuEnt, preMenuKnockback, transform]: preMenus) {
        if (preMenuKnockback.canSpawnPreMenu(time.fixedDelta())) {
            time.setTimeScale(0.0f);

            world.destroy(preMenuEnt);

            world.newEnt(
                LevelUpPreMenu(levelUpAnim["Default"].getTotalDuration(), 8),
                UICreator(levelUpUV, UIAnchor::CENTER_CENTER),
                Animation(levelUpAnim, "Default", AnimType::UNSCALED),
                Transform(
                    glm::vec2(0, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(10)
            );
        }

        transform.scale(glm::vec2(32, 32) * time.fixedDelta());
    }
}

void levelUpPreMenuSys(MainFixedSystem, World& world) {
    auto preMenus = world.view<LevelUpPreMenu>();

    auto [time] = world.resource<const Time>();

    for (auto [preMenuEnt, preMenu]: preMenus) {
        if (preMenu.canSpawnStar(time.unscaledFixedDelta())) {
            world.newEnt(
                UICreator(fireworkUV, UIAnchor::CENTER_CENTER),
                Animation(fireworkAnim, "Default", AnimType::UNSCALED),
                Transform(
                    glm::vec2((rand() % 8 - 4) * 16, (rand() % 6 - 3) * 16),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(9),
                UnscaledLifeTime(fireworkAnim["Default"].getTotalDuration())
            );
        }
        
        if (preMenu.canSpawnMenu(time.unscaledFixedDelta())) {
            world.destroy(preMenuEnt);

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

void menuBonusTranslationSys(MainFixedSystem, World& world) {
    auto menus = world.view<Transform, const MenuBonusTranslation>();

    auto [time] = world.resource<const Time>();

    for (auto [menuEnt, transform, menuBonusTranslation]: menus) {
        if (glm::distance(transform.getPosition(), menuBonusTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(menuBonusTranslation.getFinalPosition());

            const auto& bonusesIdx = menuBonusTranslation.getBonusesIdx();

            world.remove<MenuBonusTranslation>(menuEnt);

            world.appendChildren(menuEnt, {
                world.newEnt(
                    MenuBonusSelector(bonusesIdx.size()),
                    UICreator(menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
                    Animation(menuBonusHUDAnim, "MediumSelector", AnimType::UNSCALED),
                    Transform(
                        menuBonusTranslation.getFinalPosition() + glm::vec2(8, 8),
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

                world.appendChildren(menuEnt, {
                    world.newEnt(
                        BonusRow(i, bonusVec[bonusIdx].type, bonusVec[bonusIdx].descriptionCallbackPerLevel[bonusLevel].callback),
                        UICreator(menuBonusIconsUV, bonusVec[bonusIdx].imgIconIdx, UIAnchor::CENTER_CENTER),
                        Transform(
                            menuBonusTranslation.getFinalPosition() + glm::vec2(16 + 16, 8 + i * 32 + 16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        ZIndex(1)
                    ),
                    world.newEnt(
                        TextUICreator(bonusVec[bonusIdx].name, "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                        Transform(
                            menuBonusTranslation.getFinalPosition() + glm::vec2(48, 12 + i * 32),
                            0,
                            glm::vec2(1, 1)
                        ),
                        ZIndex(1)
                    )
                });
                i++;
            }
        } else {
            transform.move(glm::normalize(menuBonusTranslation.getFinalPosition() - transform.getPosition()) * menuBonusTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusReverseTranslationSys(MainFixedSystem, World& world) {
    auto menus = world.view<Transform, const MenuBonusReverseTranslation>();

    auto [time] = world.resource<Time>();

    for (auto [menuEnt, transform, menuBonusTranslation]: menus) {
        if (glm::distance(transform.getPosition(), menuBonusTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(menuBonusTranslation.getFinalPosition());

            world.destroy(menuEnt);
            time.setTimeScale(1.0f);
        } else {
            transform.move(glm::normalize(menuBonusTranslation.getFinalPosition() - transform.getPosition()) * menuBonusTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusSelectorSys(MainFixedSystem, World& world) {
    auto selectors = world.view<MenuBonusSelector, const Transform>(without<MenuBonusSelectorMoveDown, MenuBonusSelectorMoveUp>);

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(MOVE_DOWN)) {
            if (selector.nextElement()) {
                world.add(selectorEnt, MenuBonusSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 32), 384.f));
                for (auto [bonusRowEnt, transform, selectedRow]: world.view<Transform, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
                    transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
                    world.remove<MenuBonusCurSelectedRow>(bonusRowEnt);
                }
                for (auto [bonusRowEnt, bonusRow]: world.view<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
                    if (bonusRow.id == selector.getCurElement()) {
                        world.add(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
                        break;
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(MOVE_UP)) {
            if (selector.previousElement()) {
                world.add(selectorEnt, MenuBonusSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -32), 384.f));
                for (auto [bonusRowEnt, transform, selectedRow]: world.view<Transform, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
                    transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
                    world.remove<MenuBonusCurSelectedRow>(bonusRowEnt);
                }
                for (auto [bonusRowEnt, bonusRow]: world.view<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
                    if (bonusRow.id == selector.getCurElement()) {
                        world.add(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
                        break;
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(VALIDATE)) {
            for (auto [_, bonusRow]: world.view<const BonusRow>()) {
                if (bonusRow.id == selector.getCurElement()) {
                    for (auto [_, playerBonuses]: world.view<PlayerBonuses>()) {
                        playerBonuses.addBonus(bonusRow.type);
                    }
                    if (bonusRow.hasCallback()) {
                        bonusRow(world);
                    }
                    break;
                }
            }
            world.remove<MenuBonusSelector>(selectorEnt);
            for (auto [menuBonusEnt, menuBonusTransform]: world.view<const Transform>(with<MenuBonus>)) {
                world.add(menuBonusEnt, MenuBonusReverseTranslation(menuBonusTransform.getPosition() + glm::vec2(0, 144), 512.f));
            }
        }
    }
}

void menuBonusSelectorMoveDownSys(MainFixedSystem, World& world) {
    auto selectors = world.view<Transform, const MenuBonusSelectorMoveDown>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, menuBonusSelectorMoveDown]: selectors) {
        if (glm::distance(transform.getPosition(), menuBonusSelectorMoveDown.getDestination()) <= 4.f) {
            transform.setPosition(menuBonusSelectorMoveDown.getDestination());
            world.remove<MenuBonusSelectorMoveDown>(selectorEnt);
        } else {
            transform.moveY(menuBonusSelectorMoveDown.getSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusSelectorMoveUpSys(MainFixedSystem, World& world) {
    auto selectors = world.view<Transform, const MenuBonusSelectorMoveUp>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, menuBonusSelectorMoveUp]: selectors) {
        if (glm::distance(transform.getPosition(), menuBonusSelectorMoveUp.getDestination()) <= 4.f) {
            transform.setPosition(menuBonusSelectorMoveUp.getDestination());
            world.remove<MenuBonusSelectorMoveUp>(selectorEnt);
        } else {
            transform.moveY(-menuBonusSelectorMoveUp.getSpeed() * time.unscaledFixedDelta());
        }
    }
}

void MenuBonusCurSelectedRowScaleSys(MainFixedSystem, World& world) {
    auto bonusRows = world.view<Transform, MenuBonusCurSelectedRow>(with<BonusRow>);

    auto [time] = world.resource<const Time>();

    for (auto [_, transform, selectedRow]: bonusRows) {
        auto scale = selectedRow.getScaleSpeed() * time.unscaledFixedDelta();

        if (selectedRow.getIsIncrease()) {
            if (transform.getScale().x >= selectedRow.getMaxScale()) {
                selectedRow.changeState();
            } else {
                transform.scale(scale, scale);
            }
        } else {
            if (transform.getScale().x <= selectedRow.getMinScale()) {
                selectedRow.changeState();
            } else {
                transform.scale(-scale, -scale);
            }
        }
    }
}