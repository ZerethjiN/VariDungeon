#pragma once
#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void pauseMenuOpenCloseSys(MainFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::EXIT)) {
        auto pauseMenus = world.view<const Transform2D>(with<PauseMenu>);

        auto [time] = world.resource<Time>();

        if (pauseMenus.empty()) {
            if (world.view(with<Menu>).empty()) {
                time.setTimeScale(0);
                instantiatePauseMenuUI(world, glm::vec2(-72, -64));
            }
        } else if (!world.view<const Transform2D>(with<PauseMenu>, without<PauseMenuTranslation, PauseMenuReverseTranslation>).empty()) {
            for (auto [pauseMenuEnt, pauseMenuTransform]: pauseMenus) {
                world.add(pauseMenuEnt, PauseMenuReverseTranslation(pauseMenuTransform.getPosition() + glm::vec2(0, 144), 512.f));
            }
        }
    }
}

void pauseMenuTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const PauseMenuTranslation>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [menuEnt, transform, pauseMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), pauseMenuTranslation.getFinalPosition()) <= 4.f) {
            transform.setPositionGlobal(pauseMenuTranslation.getFinalPosition());

            world.remove<PauseMenuTranslation>(menuEnt);

            // Title:
            world.appendChildren(menuEnt, {
                world.newEnt(
                    TextUICreator("Pause:", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(8, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                    Transform2D(
                        glm::vec2(-60, -64),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(10)
                )
            });

            // Key:
            world.appendChildren(menuEnt, {
                world.newEnt(
                    TextUICreator("[esc]", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(8, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                    Transform2D(
                        glm::vec2(48, -64),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(10)
                )
            });

            world.appendChildren(menuEnt, {
                // Selector
                world.newEnt(
                    PauseMenuSelector(2),
                    UI(textureManager, menuBonusHUDUV, 1, UIAnchor::CENTER_CENTER),
                    Animation(menuBonusHUDAnim, MenuBonusHUDAnimType::MEDIUM_SELECTOR, AnimType::UNSCALED),
                    Transform2D(
                        pauseMenuTranslation.getFinalPosition() + glm::vec2(8, 8),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(1)
                ),
                // Text Continue
                world.newEnt(
                    TextUICreator("Continue", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                    Transform2D(
                        pauseMenuTranslation.getFinalPosition() + glm::vec2(48, 12),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(1),
                    PauseMenuCallback(0, [](World& world, Ent thisEnt) {
                        auto pauseMenus = world.view<const Transform2D>(with<PauseMenu>, without<PauseMenuReverseTranslation>);

                        for (auto [pauseMenuEnt, pauseMenuTransform]: pauseMenus) {
                            world.add(pauseMenuEnt, PauseMenuReverseTranslation(pauseMenuTransform.getPosition() + glm::vec2(0, 144), 512.f));
                        }
                    })
                ),
                // Text Exit
                world.newEnt(
                    TextUICreator("Exit", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(128, 24), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                    Transform2D(
                        pauseMenuTranslation.getFinalPosition() + glm::vec2(48, 44),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(1),
                    PauseMenuCallback(1, [](World& world, Ent thisEnt) {
                        world.loadScene(testScene2);
                    })
                )
            });
        } else {
            transform.move(glm::normalize(pauseMenuTranslation.getFinalPosition() - transform.getPosition()) * pauseMenuTranslation.getTranslationSpeed() * time.unscaledFixedDelta());
        }
    }
}

void pauseMenuSelectorSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.view<PauseMenuSelector, const Transform2D>(without<PauseMenuSelectorMoveDown, PauseMenuSelectorMoveUp>);

    for (auto [selectorEnt, selector, selectorTransform]: selectors) {
        if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_DOWN)) {
            if (selector.nextElement()) {
                world.add(selectorEnt, PauseMenuSelectorMoveDown(selectorTransform.getPosition() + glm::vec2(0, 32), 384.f));
            }
        } else if (vulkanEngine.window.isKeyDown(ButtonNameType::MOVE_UP)) {
            if (selector.previousElement()) {
                world.add(selectorEnt, PauseMenuSelectorMoveUp(selectorTransform.getPosition() + glm::vec2(0, -32), 384.f));
            }
        }
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
                selector.secretkeys.size() >= 9 &&
                selector.secretkeys[0] == ButtonNameType::MOVE_UP &&
                selector.secretkeys[1] == ButtonNameType::MOVE_UP &&
                selector.secretkeys[2] == ButtonNameType::MOVE_DOWN &&
                selector.secretkeys[3] == ButtonNameType::MOVE_DOWN &&
                selector.secretkeys[4] == ButtonNameType::MOVE_LEFT &&
                selector.secretkeys[5] == ButtonNameType::MOVE_RIGHT &&
                selector.secretkeys[6] == ButtonNameType::MOVE_LEFT &&
                selector.secretkeys[7] == ButtonNameType::MOVE_RIGHT &&
                selector.secretkeys[8] == ButtonNameType::B_BUTTON
            ) {
                printf("BRAVO!!!\n");
            }
            for (auto [callbackEnt, callback]: world.view<const PauseMenuCallback>()) {
                if (callback.id == selector.getCurElement()) {
                    callback.callback(world, callbackEnt);
                    break;
                }
            }
        }
    }
}

void pauseMenuReverseTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const PauseMenuReverseTranslation>();

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

void pauseMenuSelectorMoveDownSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.view<Transform2D, const PauseMenuSelectorMoveDown>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, pauseMenuSelectorMoveDown]: selectors) {
        if (glm::distance(transform.getPosition(), pauseMenuSelectorMoveDown.getDestination()) <= 4.f) {
            transform.setPosition(pauseMenuSelectorMoveDown.getDestination());
            world.remove<PauseMenuSelectorMoveDown>(selectorEnt);
        } else {
            transform.moveY(pauseMenuSelectorMoveDown.getSpeed() * time.unscaledFixedDelta());
        }
    }
}

void pauseMenuSelectorMoveUpSys(MainUnscaledFixedSystem, World& world) {
    auto selectors = world.view<Transform2D, const PauseMenuSelectorMoveUp>();

    auto [time] = world.resource<const Time>();

    for (auto [selectorEnt, transform, pauseMenuSelectorMoveUp]: selectors) {
        if (glm::distance(transform.getPosition(), pauseMenuSelectorMoveUp.getDestination()) <= 4.f) {
            transform.setPosition(pauseMenuSelectorMoveUp.getDestination());
            world.remove<PauseMenuSelectorMoveUp>(selectorEnt);
        } else {
            transform.moveY(-pauseMenuSelectorMoveUp.getSpeed() * time.unscaledFixedDelta());
        }
    }
}