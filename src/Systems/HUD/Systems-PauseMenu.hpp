#pragma once
#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void pauseMenuOpenCloseSys(MainFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::EXIT)) {
        auto pauseMenus = world.view<const Transform>(with<PauseMenu>);

        auto [time] = world.resource<Time>();

        if (pauseMenus.empty()) {
            time.setTimeScale(0);
            auto menuEnt = instantiatePauseMenuUI(world, glm::vec2(-72, -64));
            printf("Ouverture Menu Pause: %zu\n", menuEnt);
        } else if (!world.view<const Transform>(with<PauseMenu>, without<PauseMenuTranslation, PauseMenuReverseTranslation>).empty()) {
            for (auto [pauseMenuEnt, pauseMenuTransform]: pauseMenus) {
                world.add(pauseMenuEnt, PauseMenuReverseTranslation(pauseMenuTransform.getPosition() + glm::vec2(0, 144), 512.f));
            }
        }
    }
}

void pauseMenuTranslationSys(MainFixedSystem, World& world) {
    auto menus = world.view<Transform, const PauseMenuTranslation>();

    auto [time] = world.resource<const Time>();

    for (auto [menuEnt, transform, pauseMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), pauseMenuTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(pauseMenuTranslation.getFinalPosition());

            world.remove<PauseMenuTranslation>(menuEnt);

            world.appendChildren(menuEnt, {
                // Selector
                world.newEnt(
                    PauseMenuSelector(1),
                    UICreator(menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
                    Animation(menuBonusHUDAnim, "MediumSelector", AnimType::UNSCALED),
                    Transform(
                        pauseMenuTranslation.getFinalPosition() + glm::vec2(8, 8),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(1)
                ),
                // Text Exit
                world.newEnt(
                    TextUICreator("Exit", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                    Transform(
                        pauseMenuTranslation.getFinalPosition() + glm::vec2(48, 12),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(1)
                )
            });
        } else {
            transform.move(glm::normalize(pauseMenuTranslation.getFinalPosition() - transform.getPosition()) * pauseMenuTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void pauseMenuSelectorSys(MainFixedSystem, World& world) {
    auto selectors = world.view<PauseMenuSelector, const Transform>(without<PauseMenuSelectorMoveDown, PauseMenuSelectorMoveUp>);

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        // if (vulkanEngine.window.isKeyDown(MOVE_DOWN)) {
        //     if (selector.nextElement()) {
        //         world.add(selectorEnt, MenuBonusSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 32), 384.f));
        //         for (auto [bonusRowEnt, transform, selectedRow]: world.view<Transform, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
        //             transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
        //             world.remove<MenuBonusCurSelectedRow>(bonusRowEnt);
        //         }
        //         for (auto [bonusRowEnt, bonusRow]: world.view<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
        //             if (bonusRow.id == selector.getCurElement()) {
        //                 world.add(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
        //                 break;
        //             }
        //         }
        //     }
        // } else if (vulkanEngine.window.isKeyDown(MOVE_UP)) {
        //     if (selector.previousElement()) {
        //         world.add(selectorEnt, MenuBonusSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -32), 384.f));
        //         for (auto [bonusRowEnt, transform, selectedRow]: world.view<Transform, const MenuBonusCurSelectedRow>(with<BonusRow>)) {
        //             transform.setScale(selectedRow.getMinScale(), selectedRow.getMinScale());
        //             world.remove<MenuBonusCurSelectedRow>(bonusRowEnt);
        //         }
        //         for (auto [bonusRowEnt, bonusRow]: world.view<const BonusRow>(without<MenuBonusCurSelectedRow>)) {
        //             if (bonusRow.id == selector.getCurElement()) {
        //                 world.add(bonusRowEnt, MenuBonusCurSelectedRow(1.1f, 1.0f, 0.25f));
        //                 break;
        //             }
        //         }
        //     }
        // } else
        if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_UP)) {
            selector.secretkeys.emplace_back(ButtonNameType::MOVE_UP);
            if (selector.secretkeys.size() > 9) {
                selector.secretkeys.erase(selector.secretkeys.begin());
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_DOWN)) {
            selector.secretkeys.emplace_back(ButtonNameType::MOVE_DOWN);
            if (selector.secretkeys.size() > 9) {
                selector.secretkeys.erase(selector.secretkeys.begin());
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_LEFT)) {
            selector.secretkeys.emplace_back(ButtonNameType::MOVE_LEFT);
            if (selector.secretkeys.size() > 9) {
                selector.secretkeys.erase(selector.secretkeys.begin());
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_RIGHT)) {
            selector.secretkeys.emplace_back(ButtonNameType::MOVE_RIGHT);
            if (selector.secretkeys.size() > 9) {
                selector.secretkeys.erase(selector.secretkeys.begin());
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::B_BUTTON)) {
            selector.secretkeys.emplace_back(ButtonNameType::B_BUTTON);
            if (selector.secretkeys.size() > 9) {
                selector.secretkeys.erase(selector.secretkeys.begin());
            }
        }

        if (vulkanEngine.window.isKeyDown(ButtonNameType::VALIDATE)) {
            if (
                selector.secretkeys[0] == MOVE_UP &&
                selector.secretkeys[1] == MOVE_UP &&
                selector.secretkeys[2] == MOVE_DOWN &&
                selector.secretkeys[3] == MOVE_DOWN &&
                selector.secretkeys[4] == MOVE_LEFT &&
                selector.secretkeys[5] == MOVE_RIGHT &&
                selector.secretkeys[6] == MOVE_LEFT &&
                selector.secretkeys[7] == MOVE_RIGHT &&
                selector.secretkeys[8] == B_BUTTON
            ) {
                printf("BRAVO!!!\n");
            }
            vulkanEngine.window.close();
            world.stopRun();
        }
    }
}

void pauseMenuReverseTranslationSys(MainFixedSystem, World& world) {
    auto menus = world.view<Transform, const PauseMenuReverseTranslation>();

    auto [time] = world.resource<Time>();

    for (auto [menuEnt, transform, pauseMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), pauseMenuTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(pauseMenuTranslation.getFinalPosition());

            world.destroy(menuEnt);
            printf("Fermeture Menu Pause: %zu\n", menuEnt);
            time.setTimeScale(1.0f);
        } else {
            transform.move(glm::normalize(pauseMenuTranslation.getFinalPosition() - transform.getPosition()) * pauseMenuTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}