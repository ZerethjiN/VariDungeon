#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <BonusCallbacks.hpp>

#include "Others/GenerateDungeon.hpp"

void hubScene(SceneSystem, World& world) {
    // Purge
    // auto [textureManager, fontManager, pipelineManager, time] = world.resource<TextureManager, FontManager, PipelineManager, Time>();
    // textureManager.clear();
    // fontManager.clear();
    // pipelineManager.clear();

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


    // Rooms Generation:
    // Create New Table:
    std::vector<std::pair<const std::size_t, Ent>> newTables;
    std::size_t height = 5;
    std::size_t width = 5;

    // Generate Cells:
    std::vector<RoomCellInfo> cellMat(height * width);
    cellMat[12].isActive = true;
    cellMat[12].isPrimary = true;
    cellMat[12].isUpOpen = true;
    cellMat[7].isActive = true;
    cellMat[7].isDownOpen = true;

    auto beginingRoomEnt = instantiateHubBeginingRoom(world, glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat[12].isUpOpen, cellMat[12].isDownOpen, cellMat[12].isLeftOpen, cellMat[12].isRightOpen);
    addDoors(world, beginingRoomEnt, glm::ivec2(2, 2), glm::vec2(2 * 160, 2 * 128), width, height, 12, cellMat, cellMat[12].isUpOpen, cellMat[12].isDownOpen, cellMat[12].isLeftOpen, cellMat[12].isRightOpen);

    newTables.emplace_back(
        12,
        beginingRoomEnt
    );

    auto kingsRoomEnt = instantiateHubKingsRoom(world, glm::vec2(2 * 160, 1 * 128), width, height, 7, cellMat[7].isUpOpen, cellMat[7].isDownOpen, cellMat[7].isLeftOpen, cellMat[7].isRightOpen);
    addDoors(world, kingsRoomEnt, glm::ivec2(2, 1), glm::vec2(2 * 160, 1 * 128), width, height, 7, cellMat, cellMat[7].isUpOpen, cellMat[7].isDownOpen, cellMat[7].isLeftOpen, cellMat[7].isRightOpen);

    newTables.emplace_back(
        7,
        kingsRoomEnt
    );

    world.setInactive(kingsRoomEnt);

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

    // generateDungeon(world, glm::vec2(0, 0));

    instantiateInventoryBarUI(world, glm::vec2(-80, -16));

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
            if (auto opt = world.get_parent(curCameraEnt)) {
                if (auto optTransform = world.get_components<Transform2D>(opt.value())) {
                    auto [parentTransform] = optTransform.value();
                    parentTransform.setPosition(glm::vec2(2 * 160, 2 * 128) + glm::vec2(-8, 0));
                }
            }
        }

        for (auto [cameraEnt]: world.view(with<CameraShake>)) {
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
}