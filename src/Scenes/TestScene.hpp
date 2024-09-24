#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

#include "Others/GenerateDungeon.hpp"

void testScene(SceneSystem, World& world) {
    // Purge
    // auto [textureManager, fontManager, pipelineManager, time] = world.resource<TextureManager, FontManager, PipelineManager, Time>();
    // textureManager.clear();
    // fontManager.clear();
    // pipelineManager.clear();

    auto [textureManager] = world.resource<TextureManager>();

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
    bool canLoadMerchantRoom = false;
    for (auto [_, playerFloor]: world.view<const PlayerFloor>()) {
        curFloor = playerFloor.curFloor;
        canLoadMerchantRoom = playerFloor.canLoadMerchantRoom;
    }

    if (canLoadMerchantRoom) {
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
        // addDoors(world, beginingRoomEnt, glm::ivec2(2, 2), glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat, cellMat[12].isUpOpen, cellMat[12].isDownOpen, cellMat[12].isLeftOpen, cellMat[12].isRightOpen);

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
        auto players = world.view<Transform2D>(with<Player>);
        if (players.empty()) {
            auto playerEnt = instantiateBarbarian(world, glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            world.addDontDestroyOnLoad(playerEnt);
        } else {
            for (auto [_, playerTransform]: players) {
                playerTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, -8));
            }
        }

        auto cameras = world.view(with<CurCamera>);
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
                if (auto opt = world.getParent(curCameraEnt)) {
                    if (auto optTransform = world.get<Transform2D>(opt.value())) {
                        auto [parentTransform] = optTransform.value();
                        parentTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0));
                    }
                }
            }

            for (auto [cameraEnt]: world.view(with<CameraShake>)) {
                if (world.has<CameraShake>(cameraEnt)) {
                    world.remove_component<CameraShake>(cameraEnt);
                }
                if (world.has<CameraShakeLeft>(cameraEnt)) {
                    world.remove_component<CameraShakeLeft>(cameraEnt);
                }
                if (world.has<CameraShakeRight>(cameraEnt)) {
                    world.remove_component<CameraShakeRight>(cameraEnt);
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