#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

#include "Others/GenerateDungeon.hpp"

void testScene(SceneSystem, World& world) {
    // Purge
    auto [textureManager, fontManager, pipelineManager] = world.resource<TextureManager, FontManager, PipelineManager>();
    textureManager.clear(world);
    fontManager.clear();
    pipelineManager.clear();

    // auto [textureManager] = world.resource<TextureManager>();

    // AppState
    auto [appstate] = world.resource<AppState>();
    appstate = AppStateType::APP_STATE_IN_GAME;

    auto [spatialHashMap] = world.resource<SpatialHashMap>();
    spatialHashMap.clear();

    // Reset Time
    auto [time] = world.resource<Time>();
    time.setTimeScale(1.0f);

    world.create_entity(
        AmbientLight(Color(255, 255, 255, 255))
    );

    std::size_t curFloor = 0;
    bool can_load_merchant_room = false;
    bool can_load_final_boss_room = false;
    for (auto [_, player_floor]: world.query<const PlayerFloor>()) {
        curFloor = player_floor.cur_floor;
        can_load_merchant_room = player_floor.can_load_merchant_room;
        can_load_final_boss_room = player_floor.can_load_final_boss_room;
    }

    if (can_load_merchant_room) {
        // Rooms Generation:
        // Create New Table:
        std::vector<std::pair<const std::size_t, Ent>> newTables;
        std::size_t height = 5;
        std::size_t width = 5;

        // Generate Cells:
        std::vector<RoomCellInfo> cellMat(height * width);
        cellMat[12].isActive = true;
        cellMat[12].isPrimary = true;

        auto beginingRoomEnt = instantiateMerchantRoom(world, glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat[12].isUpOpen, cellMat[12].isDownOpen, cellMat[12].isLeftOpen, cellMat[12].isRightOpen);
        addDoors(world, beginingRoomEnt, glm::ivec2(2, 2), glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat, false, false, false, false, false);

        newTables.emplace_back(
            12,
            beginingRoomEnt
        );

        // Chunk Exploration Init:
        std::vector<std::vector<ChunkExploration::RoomExplorationType>> roomTypes;
        for (int y = 0; y < height; y++) {
            roomTypes.emplace_back();
            for (int x = 0; x < width; x++) {
                if (cellMat[y * width + x].isPrimary) {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_PLAYER);
                } else if (cellMat[y * width + x].isActive) {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_UNKNOW);
                } else {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_EMPTY);
                }
            }
        }

        // ChunkTable recreation:
        world.create_entity(
            ChunkTable(width, height, newTables),
            ChunkExploration(width, height, roomTypes)
        );

        // Spawn Player + Camera:
        auto players = world.query<Transform2D>(with<Player>);
        if (players.empty()) {
            auto playerEnt = instantiateBarbarian(world, glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            world.addDontDestroyOnLoad(playerEnt);
        } else {
            for (auto [_, playerTransform]: players) {
                playerTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            }
        }

        auto cameras = world.query(with<CurCamera>);
        if (cameras.empty()) {
            auto cameraOrigin = world.create_entity(
                Transform2D(
                    glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                    0,
                    glm::vec2(1, 1)
                )
            );

            world.append_children(cameraOrigin, {
                // Camera
                world.create_entity(
                    Transform2D(
                        glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                        0,
                        glm::vec2(1, 1)
                    ),
                    Camera(),
                    CurCamera(),
                    CameraEffect()
                )
            });

            world.addDontDestroyOnLoad(cameraOrigin);
        } else {
            for (auto [curCameraEnt]: cameras) {
                if (auto opt = world.get_parent(curCameraEnt)) {
                    if (auto optTransform = world.get_components<Transform2D>(opt.value())) {
                        auto [parentTransform] = optTransform.value();
                        parentTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0));
                    }
                }
            }

            for (auto [cameraEnt]: world.query(with<CameraShake>)) {
                if (world.has_components<CameraShake>(cameraEnt)) {
                    world.remove_components<CameraShake>(cameraEnt);
                }
                if (world.has_components<CameraShakeLeft>(cameraEnt)) {
                    world.remove_components<CameraShakeLeft>(cameraEnt);
                }
                if (world.has_components<CameraShakeRight>(cameraEnt)) {
                    world.remove_components<CameraShakeRight>(cameraEnt);
                }
            }
        }
    } else if (can_load_final_boss_room) {
        // Rooms Generation:
        // Create New Table:
        std::vector<std::pair<const std::size_t, Ent>> newTables;
        std::size_t height = 5;
        std::size_t width = 5;

        // Generate Cells:
        std::vector<RoomCellInfo> cellMat(height * width);
        cellMat[12].isActive = true;
        cellMat[12].isPrimary = true;

        auto beginingRoomEnt = instantiateFinalBossRoom(world, glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat[12].isUpOpen, cellMat[12].isDownOpen, cellMat[12].isLeftOpen, cellMat[12].isRightOpen);
        addDoors(world, beginingRoomEnt, glm::ivec2(2, 2), glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat, false, false, false, false, false);

        newTables.emplace_back(
            12,
            beginingRoomEnt
        );

        // Chunk Exploration Init:
        std::vector<std::vector<ChunkExploration::RoomExplorationType>> roomTypes;
        for (int y = 0; y < height; y++) {
            roomTypes.emplace_back();
            for (int x = 0; x < width; x++) {
                if (cellMat[y * width + x].isPrimary) {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_PLAYER);
                } else if (cellMat[y * width + x].isActive) {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_UNKNOW);
                } else {
                    roomTypes.at(y).emplace_back(ChunkExploration::ROOM_EXPLORATION_EMPTY);
                }
            }
        }

        // ChunkTable recreation:
        world.create_entity(
            ChunkTable(width, height, newTables),
            ChunkExploration(width, height, roomTypes)
        );

        // Spawn Player + Camera:
        auto players = world.query<Transform2D>(with<Player>);
        if (players.empty()) {
            auto playerEnt = instantiateBarbarian(world, glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            world.addDontDestroyOnLoad(playerEnt);
        } else {
            for (auto [_, playerTransform]: players) {
                playerTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            }
        }

        auto cameras = world.query(with<CurCamera>);
        if (cameras.empty()) {
            auto cameraOrigin = world.create_entity(
                Transform2D(
                    glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                    0,
                    glm::vec2(1, 1)
                )
            );

            world.append_children(cameraOrigin, {
                // Camera
                world.create_entity(
                    Transform2D(
                        glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                        0,
                        glm::vec2(1, 1)
                    ),
                    Camera(),
                    CurCamera(),
                    CameraEffect()
                )
            });

            world.addDontDestroyOnLoad(cameraOrigin);
        } else {
            for (auto [curCameraEnt]: cameras) {
                if (auto opt = world.get_parent(curCameraEnt)) {
                    if (auto optTransform = world.get_components<Transform2D>(opt.value())) {
                        auto [parentTransform] = optTransform.value();
                        parentTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0));
                    }
                }
            }

            for (auto [cameraEnt]: world.query(with<CameraShake>)) {
                if (world.has_components<CameraShake>(cameraEnt)) {
                    world.remove_components<CameraShake>(cameraEnt);
                }
                if (world.has_components<CameraShakeLeft>(cameraEnt)) {
                    world.remove_components<CameraShakeLeft>(cameraEnt);
                }
                if (world.has_components<CameraShakeRight>(cameraEnt)) {
                    world.remove_components<CameraShakeRight>(cameraEnt);
                }
            }
        }
    } else {
        generateDungeon(world, glm::vec2(0, 0), curFloor);
    }

    instantiateInventoryBarUI(world, glm::vec2(-80, -16));

    world.append_children(
        world.create_entity(
            UI(textureManager, blackBackgroundUV, UIAnchor::CENTER_CENTER),
            Transform2D(
                glm::vec2(-80, -72),
                0,
                glm::vec2(1, 1)
            ),
            LifeTime(1.5f),
            ZIndex(999)
        ),
        {
            world.create_entity(
                TextUICreator(std::string("Floor ") + std::to_string(curFloor), "Fonts/Zepto-Regular.ttf", 16, UIAnchor::BOTTOM_CENTER, glm::vec2(160, 16), glm::vec4(242, 214, 136, 255), glm::vec2(0.0, 0.0), TextAlignementType::ALIGN_CENTER),
                Transform2D(
                    glm::vec2(-80, -88),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(999)
            )
        }
    );
}