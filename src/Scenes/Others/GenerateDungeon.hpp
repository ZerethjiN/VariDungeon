#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <RoomPrefabs.hpp>

struct RoomCellInfo {
    // int idRoom;
    // bool isCellCheck = false;
    bool isActive = false;
    bool isLeftOpen = false;
    bool isRightOpen = false;
    bool isUpOpen = false;
    bool isDownOpen = false;
    bool isPrimary = false;
    bool isFinal = false;
    bool isBonusRoom = false;
    // bool isMerchant = false;
    // bool isKeyRoom = false;
    // bool isJungleAccess = false;
    // bool isSanctuary = false;
};

bool newGenCell(const std::size_t width, const std::size_t height, std::size_t lastCell, std::size_t i, const std::size_t bonusPos, std::vector<RoomCellInfo>& cellMat) {
    if ((lastCell < width || cellMat[lastCell - width].isActive)
        && (lastCell >= width * (height - 1) || cellMat[lastCell + width].isActive)
        && (((lastCell % width) == 0) || cellMat[lastCell - 1].isActive)
        && (((lastCell % width) >= width - 1) || cellMat[lastCell + 1].isActive)) {
        return false;
    }

    switch (rand() % 4) {
        case 0: // Up
            if (lastCell < width || cellMat[lastCell - width].isActive) {
                return newGenCell(width, height, lastCell, i, bonusPos, cellMat);
            } else {
                cellMat[lastCell].isUpOpen = true;
                cellMat[lastCell - width].isActive = true;
                cellMat[lastCell - width].isDownOpen = true;
                if (i > 0) {
                    if (i == bonusPos) {
                        cellMat[lastCell - width].isBonusRoom = true;
                    }
                    return newGenCell(width, height, lastCell - width, i - 1, bonusPos, cellMat);
                } else {
                    cellMat[lastCell - width].isFinal = true;
                }
            }
            break;

        case 1: // Down
            if (lastCell >= width * (height - 1) || cellMat[lastCell + width].isActive) {
                return newGenCell(width, height, lastCell, i, bonusPos, cellMat);
            } else {
                cellMat[lastCell].isDownOpen = true;
                cellMat[lastCell + width].isActive = true;
                cellMat[lastCell + width].isUpOpen = true;
                if (i > 0) {
                    if (i == bonusPos) {
                        cellMat[lastCell + width].isBonusRoom = true;
                    }
                    return newGenCell(width, height, lastCell + width, i - 1, bonusPos, cellMat);
                } else {
                    cellMat[lastCell + width].isFinal = true;
                }
            }
            break;

        case 2: // Left
            if ((lastCell % width) == 0 || cellMat[lastCell - 1].isActive) {
                return newGenCell(width, height, lastCell, i, bonusPos, cellMat);
            } else {
                cellMat[lastCell].isLeftOpen = true;
                cellMat[lastCell - 1].isActive = true;
                cellMat[lastCell - 1].isRightOpen = true;
                if (i > 0) {
                    if (i == bonusPos) {
                        cellMat[lastCell - 1].isBonusRoom = true;
                    }
                    return newGenCell(width, height, lastCell - 1, i - 1, bonusPos, cellMat);
                } else {
                    cellMat[lastCell - 1].isFinal = true;
                }
            }
            break;

        case 3: // Right
            if (((lastCell % width) >= width - 1) || cellMat[lastCell + 1].isActive) {
                return newGenCell(width, height, lastCell, i, bonusPos, cellMat);
            } else {
                cellMat[lastCell].isRightOpen = true;
                cellMat[lastCell + 1].isActive = true;
                cellMat[lastCell + 1].isLeftOpen = true;
                if (i > 0) {
                    if (i == bonusPos) {
                        cellMat[lastCell + 1].isBonusRoom = true;
                    }
                    return newGenCell(width, height, lastCell + 1, i - 1, bonusPos, cellMat);
                } else {
                    cellMat[lastCell + 1].isFinal = true;
                }
            }
            break;
    }

    return true;
}

void addDoors(World& world, Ent chunkHolderEnt, const glm::ivec2 newCurRoomXY, const glm::vec2& position, std::size_t width, std::size_t height, std::size_t chunkIdx, const std::vector<RoomCellInfo>& cellMat, bool isDoorOpenUp, bool isDoorOpenDown, bool isDoorOpenLeft, bool isDoorOpenRight) {
    auto [textureManager] = world.resource<TextureManager>();
    
    std::vector<Ent> subEnts;

    // Wall Collisions:
    if (isDoorOpenUp) {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(0, -1), chunkIdx - width, DoorTrigger::DOOR_TRIGGER_NORTH),
                IsDoorLock(),
                Sprite(textureManager, doorUV, 0),
                Transform2D(
                    position - glm::vec2(8, (16 * 7 / 2) + 8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(96, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx - width].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-32, -64), 0) :
                instantiateMiniTorch(world, position + glm::vec2(-32, -64), 0)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx - width].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(16, -64), 0) :
                instantiateMiniTorch(world, position + glm::vec2(16, -64), 0)
            )
        );
    } else {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 160, 32)
            )
        );
    }

    if (isDoorOpenLeft) {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(-1, 0), chunkIdx - 1, DoorTrigger::DOOR_TRIGGER_WEST),
                IsDoorLock(),
                Sprite(textureManager, doorUV, 0),
                Transform2D(
                    position - glm::vec2((16 * 9 / 2) + 8, 8),
                    270,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 16)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(0, 80),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 48)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx - 1].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-80, -32), 270) :
                instantiateMiniTorch(world, position + glm::vec2(-80, -32), 270)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx - 1].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-80, 16), 270) :
                instantiateMiniTorch(world, position + glm::vec2(-80, 16), 270)
            )
        );
    } else {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 128)
            )
        );
    }

    if (isDoorOpenRight) {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(1, 0), chunkIdx + 1, DoorTrigger::DOOR_TRIGGER_EAST),
                IsDoorLock(),
                Sprite(textureManager, doorUV, 0),
                Transform2D(
                    position + glm::vec2((16 * 9 / 2) - 8, -8),
                    90,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(0, 80),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx + 1].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(64, -32), 90) :
                instantiateMiniTorch(world, position + glm::vec2(64, -32), 90)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx + 1].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(64, 16), 90) :
                instantiateMiniTorch(world, position + glm::vec2(64, 16), 90)
            )
        );
    } else {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 128)
            )
        );
    }

    if (isDoorOpenDown) {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(0, 1), chunkIdx + width, DoorTrigger::DOOR_TRIGGER_SOUTH),
                IsDoorLock(),
                Sprite(textureManager, doorUV, 0),
                Transform2D(
                    position + glm::vec2(-8, (16 * 7 / 2) - 8),
                    180,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            )
        );
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(96, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx + width].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-32, 48), 180) :
                instantiateMiniTorch(world, position + glm::vec2(-32, 48), 180)
            )
        );
        subEnts.emplace_back(
            (cellMat[chunkIdx + width].isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(16, 48), 180) :
                instantiateMiniTorch(world, position + glm::vec2(16, 48), 180)
            )
        );
    } else {
        subEnts.emplace_back(
            world.create_entity(
                Wall(),
                Transform2D(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 160, 32)
            )
        );
    }

    world.appendChildren(chunkHolderEnt, subEnts);
}

static const std::vector<Ent(*)(World&, const glm::vec2&, std::size_t, std::size_t, std::size_t, bool, bool, bool, bool)> prefabRoomDeserts = {
    instantiateDesertRoom1,
    instantiateDesertRoom2,
    instantiateDesertRoom3,
    instantiateDesertRoom4,
    instantiateDesertRoom5,
    instantiateDesertRoom6,
    instantiateDesertRoom7,
    instantiateDesertRoom8,
    instantiateDesertRoom9,
    instantiateDesertRoom10,
    instantiateDesertRoom11,
    instantiateDesertRoom12,
    instantiateDesertRoom13,
    instantiateDesertRoom14,
    instantiateDesertRoom15,
    instantiateDesertRoom16,
    instantiateDesertRoom17,
    instantiateDesertRoom18,
    instantiateDesertRoom19,
};

static const std::vector<Ent(*)(World&, const glm::vec2&, std::size_t, std::size_t, std::size_t, bool, bool, bool, bool)> prefabRoomDesertsLvl2 = {
    instantiateDesertLvl2Room1,
    instantiateDesertLvl2Room2,
    instantiateDesertLvl2Room3,
    instantiateDesertLvl2Room4,
    instantiateDesertLvl2Room5,
    instantiateDesertLvl2Room6,
    instantiateDesertLvl2Room7,
    instantiateDesertLvl2Room8,
    instantiateDesertLvl2Room9,
    instantiateDesertLvl2Room10,
    instantiateDesertLvl2Room11,
    instantiateDesertLvl2Room12,
};

static const std::vector<Ent(*)(World&, const glm::vec2&, std::size_t, std::size_t, std::size_t, bool, bool, bool, bool)> prefabBossRoomDeserts = {
    instantiateDesertBossRoom1,
    instantiateDesertBossRoom2,
    instantiateDesertBossRoom3,
};

void generateDungeon(World& world, const glm::vec2& dungeonPosition, std::size_t curFloor) {
    std::cout << "Generate Dungeon - Total Ent: " << world.getTotalEntities() << std::endl;

    // Purge Old Table:
    auto chunkTables = world.view<const ChunkTable>();
    for (auto [chunkTableEnt, chunkTable]: chunkTables) {
        for (const auto& chunkPair: chunkTable) {
            world.delete_entity(chunkPair.second);
        }
        world.delete_entity(chunkTableEnt);
    }

    // Create New Table:
    std::vector<std::pair<const std::size_t, Ent>> newTables;
    std::size_t height = 5;
    std::size_t width = 5;

    // Generate Cells:
    std::vector<RoomCellInfo> cellMat;
    bool checkGen;
    do {
        cellMat = std::vector<RoomCellInfo>(height * width);
        std::size_t primaryCell = rand() % (height * width);
        cellMat[primaryCell].isActive = true;
        cellMat[primaryCell].isPrimary = true;
        checkGen = newGenCell(width, height, primaryCell, 9, 5, cellMat);
    } while(!checkGen);

    // Instantiate Rooms:
    std::vector<Ent(*)(World&, const glm::vec2&, std::size_t, std::size_t, std::size_t, bool, bool, bool, bool)> newPrefabRooms;
    if (curFloor < 3) {
        newPrefabRooms = prefabRoomDeserts;
    } else {
        newPrefabRooms = prefabRoomDesertsLvl2;
    }

    for (std::size_t roomPosY = 0; roomPosY < height; roomPosY++) {
        for (std::size_t roomPosX = 0; roomPosX < width; roomPosX++) {
            std::size_t curRoomIdx = roomPosY * width + roomPosX;

            if (!cellMat[curRoomIdx].isActive) {
                continue;
            }

            if (cellMat[curRoomIdx].isPrimary) {
                auto newRoomPrefab = instantiateDesertBegininggRoom; //instantiateDesertTestRoom;

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                auto players = world.view<Transform2D>(with<Player>);

                if (players.empty()) {
                    auto playerEnt = instantiateBarbarian(world, glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, -8));
                    world.addDontDestroyOnLoad(playerEnt);
                } else {
                    for (auto [_, playerTransform]: players) {
                        playerTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, -8));
                    }
                }

                auto cameras = world.view(with<CurCamera>);

                if (cameras.empty()) {
                    auto cameraOrigin = world.create_entity(
                        Transform2D(
                            glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                            0,
                            glm::vec2(1, 1)
                        )
                    );

                    world.appendChildren(cameraOrigin, {
                        // Camera
                        world.create_entity(
                            Transform2D(
                                glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
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
                                parentTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0));
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
            } else if (cellMat[curRoomIdx].isBonusRoom) {
                auto newRoomPrefab = instantiateDesertBonusRoom;

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            } else if (cellMat[curRoomIdx].isFinal) {
                auto newRoomPrefab = prefabBossRoomDeserts[rand() % prefabBossRoomDeserts.size()];

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            } else {
                auto rnd = rand() % newPrefabRooms.size();
                auto newRoomPrefab = newPrefabRooms[rnd];
                newPrefabRooms.erase(newPrefabRooms.begin() + rnd);
                if (newPrefabRooms.empty()) {
                    if (curFloor < 3) {
                        newPrefabRooms = prefabRoomDeserts;
                    } else {
                        newPrefabRooms = prefabRoomDesertsLvl2;
                    }
                }
                // auto newRoomPrefab = prefabRoomDesertsLvl2[rand() % prefabRoomDesertsLvl2.size()];

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            }
        }
    }

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
}