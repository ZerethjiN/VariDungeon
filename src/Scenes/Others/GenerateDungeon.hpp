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

void generateDungeon(World& world, const glm::vec2& dungeonPosition) {
    // Purge Old Table:
    auto chunkTables = world.view<const ChunkTable>();
    for (auto [chunkTableEnt, chunkTable]: chunkTables) {
        for (const auto& chunkPair: chunkTable) {
            world.destroy(chunkPair.second);
        }
        world.destroy(chunkTableEnt);
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
    for (std::size_t roomPosY = 0; roomPosY < height; roomPosY++) {
        for (std::size_t roomPosX = 0; roomPosX < width; roomPosX++) {
            std::size_t curRoomIdx = roomPosY * width + roomPosX;

            if (!cellMat[curRoomIdx].isActive) {
                continue;
            }

            if (cellMat[curRoomIdx].isPrimary) {
                auto newChunkEnt = instantiateDesertRoom1(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                auto players = world.view<Transform>(with<Player>);

                if (players.empty()) {
                    auto playerEnt = instantiateBarbarian(world, glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-48, 0));

                    auto cameraOrigin = world.newEnt(
                        Transform(
                            glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                            0,
                            glm::vec2(1, 1)
                        )
                    );

                    world.appendChildren(cameraOrigin, {
                        // Camera
                        world.newEnt(
                            Transform(
                                glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                                0,
                                glm::vec2(1, 1)
                            ),
                            Camera(),
                            CurCamera()
                        )
                    });
                } else {
                    for (auto [_, playerTransform]: players) {
                        playerTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-48, 0));
                    }
                    for (auto [curCameraEnt]: world.view(with<CurCamera>)) {
                        if (auto opt = world.getParent(curCameraEnt)) {
                            if (auto transformOpt = world.get<Transform>(opt.value())) {
                                auto [parentTransform] = transformOpt.value();
                                parentTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128));
                            }
                        }
                    }
                }
            } else {
                auto newChunkEnt = instantiateDesertRoom1(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            }
        }
    }

    // ChunkTable recreation:
    world.newEnt(
        ChunkTable(width, height, newTables)
    );
}