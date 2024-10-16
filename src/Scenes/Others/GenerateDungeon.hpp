#pragma once

#include <Zerengine.hpp>
#include <Images.hpp>
#include <Prefabs.hpp>
#include <RoomPrefabs.hpp>

static constexpr std::size_t WIDTH_DUNGEON_WITH_KEY = 5zu;
static constexpr std::size_t HEIGHT_DUNGEON_WITH_KEY = 5zu;
static constexpr std::size_t SIZE_DUNGEON_WITH_KEY = WIDTH_DUNGEON_WITH_KEY * HEIGHT_DUNGEON_WITH_KEY;
static constexpr std::size_t MIN_CELL_DUNGEON_WITH_KEY = 13zu;
static constexpr std::size_t MAX_CELL_DUNGEON_WITH_KEY = 18zu;

static constexpr std::size_t WIDTH_BIG_FLOOR = 8u;
static constexpr std::size_t HEIGHT_BIG_FLOOR = 8u;
static constexpr std::size_t SIZE_BIG_FLOOR = WIDTH_BIG_FLOOR * HEIGHT_BIG_FLOOR;
static constexpr std::size_t MIN_CELL_BIG_FLOOR = 20u;
static constexpr std::size_t MAX_CELL_BIG_FLOOR = 30u;

class RoomCellInfo {
public:
    std::size_t idRoom;
    bool isCellCheck;
    bool isActive;
    bool isLeftOpen;
    bool isRightOpen;
    bool isUpOpen;
    bool isDownOpen;
    bool isPrimary;
    bool isFinal;
    bool isBonusRoom;
    // bool isMerchant = false;
    bool isKeyRoom;
    // bool isJungleAccess = false;
    // bool isSanctuary = false;
    
    constexpr RoomCellInfo() noexcept:
        idRoom(0),
        isCellCheck(false),
        isActive(false),
        isLeftOpen(false),
        isRightOpen(false),
        isUpOpen(false),
        isDownOpen(false),
        isPrimary(false),
        isFinal(false),
        isBonusRoom(false),
        isKeyRoom(false) {
    }
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

void genCellNewDungeonWithKey(const std::size_t width, const std::size_t height, std::vector<RoomCellInfo>& cellMat, std::size_t& nbRoom, const std::size_t curCell) {
    cellMat.at(curCell).idRoom = nbRoom;
    std::println("NbRoom: {}", nbRoom);
    nbRoom++;

    // Init Up
    if (curCell >= width) {
        if (!cellMat.at(curCell - width).isCellCheck) {
            cellMat.at(curCell - width).isCellCheck = true;
            if (rand() % 2) {
                cellMat.at(curCell - width).isActive = true;
                cellMat.at(curCell).isUpOpen = true;
                genCellNewDungeonWithKey(width, height, cellMat, nbRoom, curCell - width);
            } else {
                cellMat.at(curCell - width).isActive = false;
                cellMat.at(curCell).isUpOpen = false;
            }
        } else {
            cellMat.at(curCell).isUpOpen = cellMat.at(curCell - width).isActive;
        }
    }

    // Init Down
    if (curCell < (height * (width - 1))) {
        if (!cellMat.at(curCell + width).isCellCheck) {
            cellMat.at(curCell + width).isCellCheck = true;
            if (rand() % 2) {
                cellMat.at(curCell + width).isActive = true;
                cellMat.at(curCell).isDownOpen = true;
                genCellNewDungeonWithKey(width, height, cellMat, nbRoom, curCell + width);
            } else {
                cellMat.at(curCell + width).isActive = false;
                cellMat.at(curCell).isDownOpen = false;
            }
        } else {
            cellMat.at(curCell).isDownOpen = cellMat.at(curCell + width).isActive;
        }
    }

    // Init Left
    if ((curCell % width) != 0) {
        if (!cellMat.at(curCell - 1).isCellCheck) {
            cellMat.at(curCell - 1).isCellCheck = true;
            if (rand() % 2) {
                cellMat.at(curCell - 1).isActive = true;
                cellMat.at(curCell).isLeftOpen = true;
                genCellNewDungeonWithKey(width, height, cellMat, nbRoom, curCell - 1);
            } else {
                cellMat.at(curCell - 1).isActive = false;
                cellMat.at(curCell).isLeftOpen = false;
            }
        } else {
            cellMat.at(curCell).isLeftOpen = cellMat.at(curCell - 1).isActive;
        }
    }

    // Init Right
    if ((curCell % width) != (width - 1)) {
        if (!cellMat.at(curCell + 1).isCellCheck) {
            cellMat.at(curCell + 1).isCellCheck = true;
            if (rand() % 2) {
                cellMat.at(curCell + 1).isActive = true;
                cellMat.at(curCell).isRightOpen = true;
                genCellNewDungeonWithKey(width, height, cellMat, nbRoom, curCell + 1);
            } else {
                cellMat.at(curCell + 1).isActive = false;
                cellMat.at(curCell).isRightOpen = false;
            }
        } else {
            cellMat.at(curCell).isRightOpen = cellMat.at(curCell + 1).isActive;
        }
    }
}

void preGenCellNewDungeonWithKey(std::vector<RoomCellInfo>& cellMat) {
    std::size_t nbRoom = 0;

    do {
        nbRoom = 0;
        cellMat.clear();
        cellMat.resize(SIZE_DUNGEON_WITH_KEY, RoomCellInfo());
        std::size_t primaryCell = rand() % (SIZE_DUNGEON_WITH_KEY);
        cellMat.at(primaryCell).isCellCheck = true;
        cellMat.at(primaryCell).isActive = true;
        cellMat.at(primaryCell).isPrimary = true;
        genCellNewDungeonWithKey(WIDTH_DUNGEON_WITH_KEY, HEIGHT_DUNGEON_WITH_KEY, cellMat, nbRoom, primaryCell);
        for (std::size_t i = 0; i < SIZE_DUNGEON_WITH_KEY; i++) {
            if (cellMat.at(i).idRoom == nbRoom - 1) {
                cellMat.at(i).isFinal = true;
                break;
            }
        }
    } while ((nbRoom < MIN_CELL_DUNGEON_WITH_KEY) || (nbRoom > MAX_CELL_DUNGEON_WITH_KEY));

    bool bonusRoomReady = false;
    do {
        std::size_t bonusCell = rand() % (SIZE_DUNGEON_WITH_KEY);
        if (cellMat[bonusCell].isActive && !cellMat[bonusCell].isPrimary && !cellMat[bonusCell].isFinal) {
            cellMat[bonusCell].isBonusRoom = true;
            bonusRoomReady = true;
        }
    } while (!bonusRoomReady);

    bool keyRoomReady = false;
    do {
        std::size_t keyCell = rand() % (SIZE_DUNGEON_WITH_KEY);
        if (cellMat[keyCell].isActive && !cellMat[keyCell].isPrimary && !cellMat[keyCell].isFinal && !cellMat[keyCell].isBonusRoom) {
            cellMat[keyCell].isKeyRoom = true;
            keyRoomReady = true;
        }
    } while(!keyRoomReady);
}

void preGenCellNewDungeonBigFloor(std::vector<RoomCellInfo>& cellMat) {
    std::size_t nbRoom = 0;

    do {
        nbRoom = 0;
        cellMat.clear();
        cellMat.resize(SIZE_BIG_FLOOR, RoomCellInfo());
        std::size_t primaryCell = rand() % (SIZE_BIG_FLOOR);
        cellMat.at(primaryCell).isCellCheck = true;
        cellMat.at(primaryCell).isActive = true;
        cellMat.at(primaryCell).isPrimary = true;
        genCellNewDungeonWithKey(WIDTH_BIG_FLOOR, HEIGHT_BIG_FLOOR, cellMat, nbRoom, primaryCell);
        for (std::size_t i = 0; i < SIZE_BIG_FLOOR; i++) {
            if (cellMat.at(i).idRoom == nbRoom - 1) {
                cellMat.at(i).isFinal = true;
                break;
            }
        }
    } while ((nbRoom < MIN_CELL_BIG_FLOOR) || (nbRoom > MAX_CELL_BIG_FLOOR));

    bool bonusRoomReady = false;
    do {
        std::size_t bonusCell = rand() % (SIZE_BIG_FLOOR);
        if (cellMat[bonusCell].isActive && !cellMat[bonusCell].isPrimary && !cellMat[bonusCell].isFinal) {
            cellMat[bonusCell].isBonusRoom = true;
            bonusRoomReady = true;
        }
    } while (!bonusRoomReady);
}

void addDoors(World& world, Ent chunkHolderEnt, const glm::ivec2 newCurRoomXY, const glm::vec2& position, std::size_t width, std::size_t height, std::size_t chunkIdx, const std::vector<RoomCellInfo>& cellMat, bool isDoorOpenUp, bool isDoorOpenDown, bool isDoorOpenLeft, bool isDoorOpenRight, bool isKeyFloor) {
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
        if (isKeyFloor && cellMat.at(chunkIdx - width).isFinal) {
            subEnts.emplace_back(
                world.create_entity(
                    DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(0, -1), chunkIdx - width, DoorTrigger::DOOR_TRIGGER_NORTH),
                    IsDoorLock(),
                    IsDoorWithKey(),
                    Sprite(textureManager, doorUV, 1),
                    Transform2D(
                        position - glm::vec2(8, (16 * 7 / 2) + 8),
                        0,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(-9),
                    Collider(-32 / 2, -16 / 2, 32, 16)
                )
            );
        } else {
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
        }
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
            (cellMat.at(chunkIdx - width).isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-32, -64), 0) :
                instantiateMiniTorch(world, position + glm::vec2(-32, -64), 0)
            )
        );
        subEnts.emplace_back(
            (cellMat.at(chunkIdx - width).isFinal ?
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
        if (isKeyFloor && cellMat.at(chunkIdx - 1).isFinal) {
            subEnts.emplace_back(
                world.create_entity(
                    DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(-1, 0), chunkIdx - 1, DoorTrigger::DOOR_TRIGGER_WEST),
                    IsDoorLock(),
                    IsDoorWithKey(),
                    Sprite(textureManager, doorUV, 1),
                    Transform2D(
                        position - glm::vec2((16 * 9 / 2) + 8, 8),
                        270,
                        glm::vec2(1, 1)
                    ),
                    Collider(-32 / 2, -16 / 2, 32, 16)
                )
            );
        } else {
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
        }
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
            (cellMat.at(chunkIdx - 1).isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-80, -32), 270) :
                instantiateMiniTorch(world, position + glm::vec2(-80, -32), 270)
            )
        );
        subEnts.emplace_back(
            (cellMat.at(chunkIdx - 1).isFinal ?
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
        if (isKeyFloor && cellMat.at(chunkIdx + 1).isFinal) {
            subEnts.emplace_back(
                world.create_entity(
                    DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(1, 0), chunkIdx + 1, DoorTrigger::DOOR_TRIGGER_EAST),
                    IsDoorLock(),
                    IsDoorWithKey(),
                    Sprite(textureManager, doorUV, 1),
                    Transform2D(
                        position + glm::vec2((16 * 9 / 2) - 8, -8),
                        90,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(-9),
                    Collider(-32 / 2, -16 / 2, 32, 16)
                )
            );
        } else {
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
        }
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
            (cellMat.at(chunkIdx + 1).isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(64, -32), 90) :
                instantiateMiniTorch(world, position + glm::vec2(64, -32), 90)
            )
        );
        subEnts.emplace_back(
            (cellMat.at(chunkIdx + 1).isFinal ?
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
        if (isKeyFloor && cellMat.at(chunkIdx + width).isFinal) {
            subEnts.emplace_back(
                world.create_entity(
                    DoorTrigger(newCurRoomXY, newCurRoomXY + glm::ivec2(0, 1), chunkIdx + width, DoorTrigger::DOOR_TRIGGER_SOUTH),
                    IsDoorLock(),
                    IsDoorWithKey(),
                    Sprite(textureManager, doorUV, 1),
                    Transform2D(
                        position + glm::vec2(-8, (16 * 7 / 2) - 8),
                        180,
                        glm::vec2(1, 1)
                    ),
                    ZIndex(-9),
                    Collider(-32 / 2, -16 / 2, 32, 16)
                )
            );
        } else {
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
        }
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
            (cellMat.at(chunkIdx + width).isFinal ?
                instantiateSkullBossRoom(world, position + glm::vec2(-32, 48), 180) :
                instantiateMiniTorch(world, position + glm::vec2(-32, 48), 180)
            )
        );
        subEnts.emplace_back(
            (cellMat.at(chunkIdx + width).isFinal ?
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

    world.append_children(chunkHolderEnt, subEnts);
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
    instantiateDesertBossRoom4,
};

void generateDungeon(World& world, const glm::vec2& dungeonPosition, std::size_t curFloor) {
    std::cout << "Generate Dungeon - Total Ent: " << world.getTotalEntities() << std::endl;

    // Purge Old Table:
    auto chunkTables = world.query<const ChunkTable>();
    for (auto [chunkTableEnt, chunkTable]: chunkTables) {
        for (const auto& chunkPair: chunkTable) {
            world.delete_entity(chunkPair.second);
        }
        world.delete_entity(chunkTableEnt);
    }

    // Create New Table:
    std::vector<std::pair<const std::size_t, Ent>> newTables;
    std::size_t height = 5zu;
    std::size_t width = 5zu;

    // Generate Cells:
    std::vector<RoomCellInfo> cellMat;
    bool isKeyFloor = false;

    switch (rand() % 5) {
        case 0:
            height = HEIGHT_DUNGEON_WITH_KEY;
            width = WIDTH_DUNGEON_WITH_KEY;
            preGenCellNewDungeonWithKey(cellMat);
            break;

        case 1:
            height = HEIGHT_BIG_FLOOR;
            width = WIDTH_BIG_FLOOR;
            preGenCellNewDungeonBigFloor(cellMat);
            break;

        default: {
                height = 5zu;
                width = 5zu;
                bool checkGen;
                do {
                    cellMat.clear();
                    cellMat.resize(height * width, RoomCellInfo());
                    std::size_t primaryCell = rand() % (height * width);
                    cellMat[primaryCell].isActive = true;
                    cellMat[primaryCell].isPrimary = true;
                    checkGen = newGenCell(width, height, primaryCell, 9, 5, cellMat);
                } while(!checkGen);
            }
            break;
    }

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

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen, isKeyFloor);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                auto players = world.query<Transform2D>(with<Player>);

                if (players.empty()) {
                    auto playerEnt = instantiateBarbarian(world, glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, -8));
                    world.addDontDestroyOnLoad(playerEnt);
                } else {
                    for (auto [_, playerTransform]: players) {
                        playerTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, -8));
                    }
                }

                auto cameras = world.query(with<CurCamera>);

                if (cameras.empty()) {
                    auto cameraOrigin = world.create_entity(
                        Transform2D(
                            glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0),// + glm::vec2(160 * 2, 144 * 2),
                            0,
                            glm::vec2(1, 1)
                        )
                    );

                    world.append_children(cameraOrigin, {
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
                        if (auto opt = world.get_parent(curCameraEnt)) {
                            if (auto optTransform = world.get_components<Transform2D>(opt.value())) {
                                auto [parentTransform] = optTransform.value();
                                parentTransform.setPosition(glm::vec2(roomPosX * 160, roomPosY * 128) + glm::vec2(-8, 0));
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
            } else if (cellMat[curRoomIdx].isBonusRoom) {
                auto newRoomPrefab = instantiateDesertBonusRoom;

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen, isKeyFloor);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            } else if (cellMat[curRoomIdx].isKeyRoom) {
                auto newRoomPrefab = instantiateDesertKeyRoom;

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen, isKeyFloor);

                newTables.emplace_back(
                    curRoomIdx,
                    newChunkEnt
                );

                world.setInactive(newChunkEnt);
            } else if (cellMat[curRoomIdx].isFinal) {
                auto newRoomPrefab = prefabBossRoomDeserts[rand() % prefabBossRoomDeserts.size()];

                auto newChunkEnt = newRoomPrefab(world, glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen);

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen, isKeyFloor);

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

                addDoors(world, newChunkEnt, glm::ivec2(roomPosX, roomPosY), glm::vec2(roomPosX * 160, roomPosY * 128), width, height, curRoomIdx, cellMat, cellMat[curRoomIdx].isUpOpen, cellMat[curRoomIdx].isDownOpen, cellMat[curRoomIdx].isLeftOpen, cellMat[curRoomIdx].isRightOpen, isKeyFloor);

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