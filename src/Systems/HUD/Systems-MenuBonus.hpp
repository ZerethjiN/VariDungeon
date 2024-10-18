#pragma once

#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void levelUpKnockbackSys(MainFixedSystem, World& world) {
    auto preMenus = world.query<LevelUpKnockback, Transform2D>();

    auto [textureManager, time] = world.resource<TextureManager, Time>();

    for (auto [preMenuEnt, preMenuKnockback, transform]: preMenus) {
        if (preMenuKnockback.canSpawnPreMenu(time.fixedDelta())) {
            time.setTimeScale(0.0f);

            world.delete_entity(preMenuEnt);

            world.create_entity(
                LevelUpPreMenu(levelUpAnim[LevelUpAnimType::DEFAULT].getTotalDuration(), 8),
                UI(textureManager, levelUpUV, UIAnchor::CENTER_CENTER),
                Animation(levelUpAnim, LevelUpAnimType::DEFAULT, AnimType::UNSCALED),
                Transform2D(
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

void levelUpPreMenuSys(MainUnscaledFixedSystem, World& world) {
    auto preMenus = world.query<LevelUpPreMenu>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [preMenuEnt, preMenu]: preMenus) {
        if (preMenu.canSpawnStar(time.unscaledFixedDelta())) {
            world.create_entity(
                UI(textureManager, fireworkUV, UIAnchor::CENTER_CENTER),
                Animation(fireworkAnim, FireworkAnimType::DEFAULT, AnimType::UNSCALED),
                Transform2D(
                    glm::vec2((rand() % 8 - 4) * 16, (rand() % 6 - 3) * 16),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(9),
                UnscaledLifeTime(fireworkAnim[FireworkAnimType::DEFAULT].getTotalDuration())
            );
        }

        if (preMenu.canSpawnMenu(time.unscaledFixedDelta())) {
            world.delete_entity(preMenuEnt);

            std::unordered_map<std::size_t, BonusData> lastBonuses;
            for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
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
                    for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                        alreadyLevelMax |= (playerBonuses.getBonusLevel(bonusVec[newBonusIdx].type) >= bonusVec[newBonusIdx].descriptionCallbackPerLevel.size());
                    }
                } while (bonusesIdx.contains(newBonusIdx) || alreadyLevelMax);
                bonusesIdx.emplace(newBonusIdx);
            }

            instantiateMenuBonusUI(world, glm::vec2(-72, -64), bonusesIdx);
        }
    }
}

void menuBonusTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.query<Transform2D, const MenuBonusTranslation>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [menuEnt, transform, menuBonusTranslation]: menus) {
        if (glm::distance(transform.getPosition(), menuBonusTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(menuBonusTranslation.getFinalPosition());

            const auto& bonusesIdx = menuBonusTranslation.getBonusesIdx();

            world.remove_components<MenuBonusTranslation>(menuEnt);

            world.append_children(menuEnt, {
                world.create_entity(
                    MenuBonusSelector(bonusesIdx.size()),
                    UI(textureManager, menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
                    Animation(menuBonusHUDAnim, MenuBonusHUDAnimType::MEDIUM_SELECTOR, AnimType::UNSCALED),
                    Transform2D(
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
                for (auto [_, playerBonuses]: world.query<const PlayerBonuses>()) {
                    bonusLevel = playerBonuses.getBonusLevel(bonusVec[bonusIdx].type);
                }

                if (bonusVec[bonusIdx].descriptionCallbackPerLevel.empty()) {
                    continue;
                }

                world.append_children(menuEnt, {
                    world.create_entity(
                        BonusRow(i, bonusVec[bonusIdx].type, bonusVec[bonusIdx].cost, bonusVec[bonusIdx].descriptionCallbackPerLevel[bonusLevel].callback),
                        UI(textureManager, menuBonusIconsUV, bonusVec[bonusIdx].imgIconIdx, UIAnchor::CENTER_CENTER),
                        Transform2D(
                            menuBonusTranslation.getFinalPosition() + glm::vec2(16 + 16, 8 + i * 32 + 16),
                            0,
                            glm::vec2(1, 1)
                        ),
                        ZIndex(1)
                    ),
                    world.create_entity(
                        TextUICreator(bonusVec[bonusIdx].name, "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                        Transform2D(
                            menuBonusTranslation.getFinalPosition() + glm::vec2(48, 12 + i * 32),
                            0,
                            glm::vec2(1, 1)
                        ),
                        ZIndex(1)
                    )
                });

                if (world.has_components<MenuBonusMerchant>(menuEnt)) {
                    world.append_children(menuEnt, {
                        world.create_entity(
                            TextUICreator(std::to_string(bonusVec[bonusIdx].cost) + "$", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_RIGHT),
                            Transform2D(
                                menuBonusTranslation.getFinalPosition() + glm::vec2(0, 12 + i * 32),
                                0,
                                glm::vec2(1, 1)
                            ),
                            ZIndex(1)
                        )
                    });
                }
                i++;
            }
        } else {
            transform.move(glm::normalize(menuBonusTranslation.getFinalPosition() - transform.getPosition()) * menuBonusTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusPreReverseTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.query<MenuBonusPreReverseTranslation, const Transform2D>();

    auto [time] = world.resource<Time>();

    for (auto [menuBonusEnt, menuBonusPreReverse, transform]: menus) {
        if (menuBonusPreReverse.canSwitchState(time.unscaledFixedDelta())) {
            world.remove_components<MenuBonusPreReverseTranslation>(menuBonusEnt);
            world.add_components(menuBonusEnt, MenuBonusReverseTranslation(transform.getPosition() + glm::vec2(0, 144), 512.f));
        }
    }
}

void menuBonusReverseTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.query<Transform2D, const MenuBonusReverseTranslation>();

    auto [time] = world.resource<Time>();

    for (auto [menuEnt, transform, menuBonusTranslation]: menus) {
        if (glm::distance(transform.getPosition(), menuBonusTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(menuBonusTranslation.getFinalPosition());

            world.delete_entity(menuEnt);
            time.setTimeScale(1.0f);
        } else {
            transform.move(glm::normalize(menuBonusTranslation.getFinalPosition() - transform.getPosition()) * menuBonusTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusSelectorSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.query<MenuBonusSelector, const Transform2D>(without<MenuBonusSelectorMoveDown, MenuBonusSelectorMoveUp>);

    auto [textureManager] = world.resource<TextureManager>();

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_DOWN)) {
            if (selector.nextElement()) {
                world.add_components(selectorEnt, MenuBonusSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 32), 384.f));
                for (auto [bonusRowEnt, transform, selectedRow]: world.query<Transform2D, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
                    transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
                    world.remove_components<MenuBonusCurSelectedRow>(bonusRowEnt);
                }
                for (auto [bonusRowEnt, bonusRow]: world.query<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
                    if (bonusRow.id == selector.getCurElement()) {
                        world.add_components(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
                        break;
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_UP)) {
            if (selector.previousElement()) {
                world.add_components(selectorEnt, MenuBonusSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -32), 384.f));
                for (auto [bonusRowEnt, transform, selectedRow]: world.query<Transform2D, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
                    transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
                    world.remove_components<MenuBonusCurSelectedRow>(bonusRowEnt);
                }
                for (auto [bonusRowEnt, bonusRow]: world.query<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
                    if (bonusRow.id == selector.getCurElement()) {
                        world.add_components(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
                        break;
                    }
                }
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::EXIT) && !world.query(with<MenuBonusMerchant>).empty()) { 
            world.remove_components<MenuBonusSelector, UI, Animation>(selectorEnt);
            for (auto [menuBonusEnt]: world.query(with<MenuBonus>)) {
                world.add_components(menuBonusEnt, MenuBonusPreReverseTranslation(menuBonusHUDAnim[MenuBonusHUDAnimType::VALIDATION_MOTIF].getTotalDuration()));
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::VALIDATE)) {
            for (auto [bonusRowEnt, bonusRowIconTransform, bonusRow]: world.query<Transform2D, const BonusRow>()) {
                if (bonusRow.id == selector.getCurElement()) {
                    bool canBuy = false;
                    if (!world.query(with<MenuBonusMerchant>).empty()) {
                        for (auto [_, playerCoin]: world.query<PlayerCoin>()) {
                            if (playerCoin >= bonusRow.cost) {
                                playerCoin -= bonusRow.cost;
                                canBuy = true;
                                for (auto [_, coinTextUI]: world.query<TextUI>(with<PlayerCoinText>)) {
                                    coinTextUI.setString("" + std::to_string(static_cast<int>(playerCoin.getCurCoin())));
                                }
                            }
                            break;
                        }
                    } else {
                        canBuy = true;
                    }

                    if (canBuy) {
                        for (auto [_, playerBonuses]: world.query<PlayerBonuses>()) {
                            playerBonuses.addBonus(bonusRow.type);
                            if (!world.query(with<MenuBonusMerchant>).empty()) {
                                for (auto [_, merchantBonus]: world.query<MerchantBonus>()) {
                                    merchantBonus.bonusesIdx.erase(merchantBonus.typeToIdx.at(bonusRow.type));
                                }
                            }
                        }
                        if (bonusRow.hasCallback()) {
                            bonusRow(world);
                        }
                        world.remove_components<MenuBonusCurSelectedRow>(bonusRowEnt);
                        bonusRowIconTransform.setScale(0.75f, 0.75f);
                        if (auto optSelectorParent = world.get_parent(selectorEnt)) {
                            auto parentMenuEnt = optSelectorParent.value();
                            world.append_children(parentMenuEnt, {
                                world.create_entity(
                                    UI(textureManager, menuBonusHUDUV, 7, UIAnchor::CENTER_CENTER),
                                    Animation(menuBonusHUDAnim, MenuBonusHUDAnimType::VALIDATION_MOTIF, AnimType::UNSCALED),
                                    Transform2D(
                                        selectorTransform.getPosition(),
                                        0,
                                        glm::vec2(1, 1)
                                    ),
                                    ZIndex(-1)
                                )
                            });
                        }
                    }
                    break;
                }
            }
            world.remove_components<MenuBonusSelector, UI, Animation>(selectorEnt);
            for (auto [menuBonusEnt]: world.query(with<MenuBonus>)) {
                world.add_components(menuBonusEnt, MenuBonusPreReverseTranslation(menuBonusHUDAnim[MenuBonusHUDAnimType::VALIDATION_MOTIF].getTotalDuration()));
            }
        }
    }
}

void menuBonusSelectorMoveDownSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.query<Transform2D, const MenuBonusSelectorMoveDown>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, menuBonusSelectorMoveDown]: selectors) {
        if (glm::distance(transform.getPosition(), menuBonusSelectorMoveDown.getDestination()) <= 4.f) {
            transform.setPosition(menuBonusSelectorMoveDown.getDestination());
            world.remove_components<MenuBonusSelectorMoveDown>(selectorEnt);
        } else {
            transform.moveY(menuBonusSelectorMoveDown.getSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusSelectorMoveUpSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.query<Transform2D, const MenuBonusSelectorMoveUp>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, menuBonusSelectorMoveUp]: selectors) {
        if (glm::distance(transform.getPosition(), menuBonusSelectorMoveUp.getDestination()) <= 4.f) {
            transform.setPosition(menuBonusSelectorMoveUp.getDestination());
            world.remove_components<MenuBonusSelectorMoveUp>(selectorEnt);
        } else {
            transform.moveY(-menuBonusSelectorMoveUp.getSpeed() * time.unscaledFixedDelta());
        }
    }
}

void menuBonusCurSelectedRowScaleSys(MainUnscaledFixedSystem, World& world) {
    auto bonusRows = world.query<Transform2D, MenuBonusCurSelectedRow>(with<BonusRow>);

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