#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>
#include <Prefabs.hpp>

Ent instantiateDesertRoom1(World& world, const glm::vec2& position, std::size_t width, std::size_t height, std::size_t chunkIdx, bool isDoorOpenUp, bool isDoorOpenDown, bool isDoorOpenLeft, bool isDoorOpenRight) {
    auto chunkHolderEnt = world.newEnt(
        ChunkInfos(chunkIdx),
        Transform(
            position,
            0,
            glm::vec2(1, 1)
        )
    );

    std::vector<Ent> subEnts;

    // Background Tiles:
    std::vector<TileMapTileInfo> backgroundTiles {
        tileMapDesertUV[ 14], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 15],
        tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  3], tileMapDesertUV[  2], tileMapDesertUV[ 11],
        tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  4], tileMapDesertUV[ 11],
        tileMapDesertUV[  4], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4],
        tileMapDesertUV[  4], tileMapDesertUV[  3], tileMapDesertUV[  3], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  4],
        tileMapDesertUV[ 13], tileMapDesertUV[  2], tileMapDesertUV[  3], tileMapDesertUV[  3], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[ 11],
        tileMapDesertUV[ 13], tileMapDesertUV[  4], tileMapDesertUV[  2], tileMapDesertUV[  1], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  4], tileMapDesertUV[  5], tileMapDesertUV[  4], tileMapDesertUV[ 11],
        tileMapDesertUV[ 16], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[  4], tileMapDesertUV[  4], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 17],
    };

    std::vector<TileMapTileInfo> foregroundTiles {
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[ 18], tileMapDesertUV[ 19], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
        tileMapDesertUV[ 22], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[ 24],
        tileMapDesertUV[ 23], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[ 25],
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
        tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[ 20], tileMapDesertUV[ 21], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0], tileMapDesertUV[  0],
    };

    // Wall Collisions:
    if (isDoorOpenUp) {
        subEnts.append_range(std::initializer_list<Ent>{
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            ),
            world.newEnt(
                DoorTrigger(chunkIdx - width, DoorTrigger::DOOR_TRIGGER_NORTH),
                IsDoorLock(),
                SpriteCreator(doorUV, 0),
                Transform(
                    position - glm::vec2(8, (16 * 7 / 2) + 8),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            ),
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(96, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            ),
            instantiateMiniTorch(world, position + glm::vec2(-32, -64), 0),
            instantiateMiniTorch(world, position + glm::vec2(16, -64), 0)
        });
    } else {
        subEnts.emplace_back(
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, -8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 160, 32)
            )
        );
        backgroundTiles[4] = tileMapDesertUV[10];
        backgroundTiles[5] = tileMapDesertUV[10];
        foregroundTiles[4] = tileMapDesertUV[0];
        foregroundTiles[5] = tileMapDesertUV[0];
    }

    if (isDoorOpenLeft) {
        subEnts.append_range(std::initializer_list<Ent>{
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            ),
            world.newEnt(
                DoorTrigger(chunkIdx - 1, DoorTrigger::DOOR_TRIGGER_WEST),
                IsDoorLock(),
                SpriteCreator(doorUV, 0),
                Transform(
                    position - glm::vec2((16 * 9 / 2) + 8, 8),
                    270,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 16)
            ),
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(0, 80),
                    0,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 48)
            ),
            instantiateMiniTorch(world, position + glm::vec2(-80, -32), 270),
            instantiateMiniTorch(world, position + glm::vec2(-80, 16), 270)
        });
    } else {
        subEnts.emplace_back(
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(-8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 128)
            )
        );
        backgroundTiles[30] = tileMapDesertUV[13];
        backgroundTiles[40] = tileMapDesertUV[13];
        foregroundTiles[30] = tileMapDesertUV[0];
        foregroundTiles[40] = tileMapDesertUV[0];
    }

    if (isDoorOpenRight) {
        subEnts.append_range(std::initializer_list<Ent>{
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            ),
            world.newEnt(
                DoorTrigger(chunkIdx + 1, DoorTrigger::DOOR_TRIGGER_EAST),
                IsDoorLock(),
                SpriteCreator(doorUV, 0),
                Transform(
                    position + glm::vec2((16 * 9 / 2) - 8, -8),
                    90,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            ),
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(0, 80),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 48)
            ),
            instantiateMiniTorch(world, position + glm::vec2(64, -32), 90),
            instantiateMiniTorch(world, position + glm::vec2(64, 16), 90)
        });
    } else {
        subEnts.emplace_back(
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(16 * 9 + 8, 0) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-32 / 2, -16 / 2, 32, 128)
            )
        );
        backgroundTiles[39] = tileMapDesertUV[11];
        backgroundTiles[49] = tileMapDesertUV[11];
        foregroundTiles[39] = tileMapDesertUV[0];
        foregroundTiles[49] = tileMapDesertUV[0];
    }

    if (isDoorOpenDown) {
        subEnts.append_range(std::initializer_list<Ent>{
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            ),
            world.newEnt(
                DoorTrigger(chunkIdx + width, DoorTrigger::DOOR_TRIGGER_SOUTH),
                IsDoorLock(),
                SpriteCreator(doorUV, 0),
                Transform(
                    position + glm::vec2(-8, (16 * 7 / 2) - 8),
                    180,
                    glm::vec2(1, 1)
                ),
                ZIndex(-9),
                Collider(-32 / 2, -16 / 2, 32, 16)
            ),
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2) + glm::vec2(96, 0),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 64, 32)
            ),
            instantiateMiniTorch(world, position + glm::vec2(-32, 48), 180),
            instantiateMiniTorch(world, position + glm::vec2(16, 48), 180)
        });
    } else {
        subEnts.emplace_back(
            world.newEnt(
                Wall(),
                Transform(
                    position + glm::vec2(0, 16 * 7 + 8) - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                    0,
                    glm::vec2(1, 1)
                ),
                Collider(-16 / 2, -32 / 2, 160, 32)
            )
        );
        backgroundTiles[74] = tileMapDesertUV[12];
        backgroundTiles[75] = tileMapDesertUV[12];
        foregroundTiles[74] = tileMapDesertUV[0];
        foregroundTiles[75] = tileMapDesertUV[0];
    }

    // Background + Foregound:
    subEnts.append_range(std::initializer_list<Ent>{
        world.newEnt(
            TileMapCreator("Textures/TileMapDesert.png", backgroundTiles, glm::uvec2(10, 8), glm::uvec2(16, 16)),
            ZIndex(0),
            Transform(
                position - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                0,
                glm::vec2(1, 1)
            )
        ),
        world.newEnt(
            TileMapCreator("Textures/TileMapDesert.png", foregroundTiles, glm::uvec2(10, 8), glm::uvec2(16, 16)),
            ZIndex(1),
            Transform(
                position - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                0,
                glm::vec2(1, 1)
            )
        )
    });

    subEnts.append_range(std::initializer_list<Ent>{
        // Decors:
        instantiatePylon(world, position + glm::vec2(48, -40)),

        // Enemies:
        instantiateSlime(world, position + glm::vec2(0, 0)),
        // instantiateBat(world, position + glm::vec2(0, 0)),
        // instantiateMummy(world, position + glm::vec2(0, 0)),
        // instantiateInsect(world, position + glm::vec2(0, 0)),
        // instantiateAnubis(world, position + glm::vec2(0, 0)),

        // Breakables:
        instantiateRock(world, position + glm::vec2(-48, -48)),
        instantiateRock(world, position + glm::vec2(-64, -48)),
        instantiateJar(world, position + glm::vec2(-64, -32)),
        instantiateJar(world, position + glm::vec2(48, 32)),
        instantiateWoodenBox(world, position + glm::vec2(32, -48))
    });

    world.appendChildren(chunkHolderEnt, subEnts);

    return chunkHolderEnt;
}