#pragma once
#include <Zerengine.hpp>
#include <Res.hpp>
#include <Comps.hpp>
#include <Prefabs.hpp>
#include <Images.hpp>

void mapMenuOpenCloseSys(MainUnscaledFixedSystem, World& world) {
    if (vulkanEngine.window.isKeyDown(ButtonNameType::MAP_MENU)) {
        auto mapMenus = world.view<const Transform2D>(with<MapMenu>);

        auto [time] = world.resource<Time>();

        if (mapMenus.empty()) {
            if (world.view(with<Menu>).empty()) {
                time.setTimeScale(0);
                instantiateMapMenuUI(world, glm::vec2(-72, -64));
            }
        } else if (!world.view<const Transform2D>(with<MapMenu>, without<MapMenuTranslation, MapMenuReverseTranslation>).empty()) {
            for (auto [mapMenuEnt, mapMenuTransform]: mapMenus) {
                world.add_component(mapMenuEnt, MapMenuReverseTranslation(mapMenuTransform.getPosition() + glm::vec2(0, 144), 512.f));
            }
        }
    }
}

void mapMenuTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const MapMenuTranslation>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [menuEnt, transform, mapMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), mapMenuTranslation.finalPosition) <= 4.f) {
            transform.setPositionGlobal(mapMenuTranslation.finalPosition);

            world.remove_component<MapMenuTranslation>(menuEnt);

            // Title:
            world.appendChildren(menuEnt, {
                world.create_entity(
                    TextUICreator("Map:", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(8, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
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
                world.create_entity(
                    TextUICreator("[m]", "Fonts/Zepto-Regular.ttf", 8, UIAnchor::CENTER_CENTER, glm::vec2(8, 8), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_LEFT),
                    Transform2D(
                        glm::vec2(52, -64),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(10)
                )
            });

            for (auto [_, exploration]: world.view<const ChunkExploration>()) {
                for (int y = 0; y < exploration.height; y++) {
                    for (int x = 0; x < exploration.width; x++) {
                        switch (exploration.roomTypes.at(y).at(x)) {
                            case ChunkExploration::ROOM_EXPLORATION_PLAYER:
                                world.appendChildren(menuEnt, {
                                    world.create_entity(
                                        UI(textureManager, mapAssetUV, 2, UIAnchor::CENTER_CENTER),
                                        Transform2D(
                                            glm::vec2((x * 8) - ((exploration.width - 1) * 8 / 2), (y * 8) - ((exploration.height - 1) * 8 / 2) - 8),
                                            0,
                                            glm::vec2(1, 1)
                                        ),
                                        ZIndex(10)
                                    )
                                });
                                break;
                            case ChunkExploration::ROOM_EXPLORATION_UNKNOW:
                                world.appendChildren(menuEnt, {
                                    world.create_entity(
                                        UI(textureManager, mapAssetUV, 0, UIAnchor::CENTER_CENTER),
                                        Transform2D(
                                            glm::vec2((x * 8) - ((exploration.width - 1) * 8 / 2), (y * 8) - ((exploration.height - 1) * 8 / 2) - 8),
                                            0,
                                            glm::vec2(1, 1)
                                        ),
                                        ZIndex(10)
                                    )
                                });
                                break;
                            case ChunkExploration::ROOM_EXPLORATION_KNOW:
                                world.appendChildren(menuEnt, {
                                    world.create_entity(
                                        UI(textureManager, mapAssetUV, 1, UIAnchor::CENTER_CENTER),
                                        Transform2D(
                                            glm::vec2((x * 8) - ((exploration.width - 1) * 8 / 2), (y * 8) - ((exploration.height - 1) * 8 / 2) - 8),
                                            0,
                                            glm::vec2(1, 1)
                                        ),
                                        ZIndex(10)
                                    )
                                });
                                break;
                            default:
                                world.appendChildren(menuEnt, {
                                    world.create_entity(
                                        UI(textureManager, mapAssetUV, 0, UIAnchor::CENTER_CENTER),
                                        Transform2D(
                                            glm::vec2((x * 8) - ((exploration.width - 1) * 8 / 2), (y * 8) - ((exploration.height - 1) * 8 / 2) - 8),
                                            0,
                                            glm::vec2(1, 1)
                                        ),
                                        ZIndex(10)
                                    )
                                });
                                break;
                        }
                    }
                }
            }

        } else {
            transform.move(glm::normalize(mapMenuTranslation.finalPosition - transform.getPosition()) * mapMenuTranslation.translationSpeed * time.unscaledFixedDelta());
        }
    }
}

void mapMenuReverseTranslationSys(MainUnscaledFixedSystem, World& world) {
    auto menus = world.view<Transform2D, const MapMenuReverseTranslation>();

    auto [time] = world.resource<Time>();

    for (auto [menuEnt, transform, mapMenuTranslation]: menus) {
        if (glm::distance(transform.getPosition(), mapMenuTranslation.finalPosition) <= 4.f) {
            transform.setPositionGlobal(mapMenuTranslation.finalPosition);

            world.delete_entity(menuEnt);
            time.setTimeScale(1.0f);
        } else {
            transform.move(glm::normalize(mapMenuTranslation.finalPosition - transform.getPosition()) * mapMenuTranslation.translationSpeed * time.unscaledFixedDelta());
        }
    }
}