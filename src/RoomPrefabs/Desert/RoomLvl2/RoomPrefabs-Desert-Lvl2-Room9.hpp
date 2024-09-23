#pragma once

#include <Zerengine.hpp>
#include <Comps.hpp>
#include <Images.hpp>
#include <Res.hpp>
#include <Prefabs.hpp>

Ent instantiateDesertLvl2Room9(World& world, const glm::vec2& position, std::size_t width, std::size_t height, std::size_t chunkIdx, bool isDoorOpenUp, bool isDoorOpenDown, bool isDoorOpenLeft, bool isDoorOpenRight) {
    auto [textureManager] = world.resource<TextureManager>();
    
    auto chunkHolderEnt = world.create_entity(
        ChunkInfos(chunkIdx),
        Transform2D(
            position,
            0,
            glm::vec2(1, 1)
        )
    );

    // Background Tiles:
    std::vector<TileMapTileInfo> backgroundTiles {
        tileMapDesertUV[ 14], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[  6], tileMapDesertUV[  6], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 10], tileMapDesertUV[ 15],
        tileMapDesertUV[ 13], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  2], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  6], tileMapDesertUV[ 11],
        tileMapDesertUV[ 13], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[  5], tileMapDesertUV[  6], tileMapDesertUV[ 11],
        tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  2], tileMapDesertUV[ 30], tileMapDesertUV[  2], tileMapDesertUV[  2], tileMapDesertUV[  6], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5],
        tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  6], tileMapDesertUV[  2], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[ 30], tileMapDesertUV[  6], tileMapDesertUV[  5], tileMapDesertUV[  5],
        tileMapDesertUV[ 13], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[ 30], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[ 11],
        tileMapDesertUV[ 13], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[  6], tileMapDesertUV[  6], tileMapDesertUV[  6], tileMapDesertUV[  5], tileMapDesertUV[ 11],
        tileMapDesertUV[ 16], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[  5], tileMapDesertUV[  5], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 12], tileMapDesertUV[ 17],
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

    // Adjust Door:
    if (!isDoorOpenUp) {
        backgroundTiles[4] = backgroundTiles[1];
        backgroundTiles[5] = backgroundTiles[1];
        foregroundTiles[4] = foregroundTiles[0];
        foregroundTiles[5] = foregroundTiles[0];
    }

    if (!isDoorOpenLeft) {
        backgroundTiles[30] = backgroundTiles[10];
        backgroundTiles[40] = backgroundTiles[10];
        foregroundTiles[30] = foregroundTiles[0];
        foregroundTiles[40] = foregroundTiles[0];
    }

    if (!isDoorOpenRight) {
        backgroundTiles[39] = backgroundTiles[19];
        backgroundTiles[49] = backgroundTiles[19];
        foregroundTiles[39] = foregroundTiles[0];
        foregroundTiles[49] = foregroundTiles[0];
    }

    if (!isDoorOpenDown) {
        backgroundTiles[74] = backgroundTiles[71];
        backgroundTiles[75] = backgroundTiles[71];
        foregroundTiles[74] = foregroundTiles[0];
        foregroundTiles[75] = foregroundTiles[0];
    }

    world.appendChildren(chunkHolderEnt, {
        // Background + Foregound:
        world.create_entity(
            TileMap(textureManager, backgroundTiles, glm::uvec2(10, 8), glm::uvec2(16, 16)),
            ZIndex(-50),
            Transform2D(
                position - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                0,
                glm::vec2(1, 1)
            )
        ),
        world.create_entity(
            TileMap(textureManager, foregroundTiles, glm::uvec2(10, 8), glm::uvec2(16, 16)),
            ZIndex(-49),
            Transform2D(
                position - glm::vec2(16 * 10 / 2, 16 * 8 / 2),
                0,
                glm::vec2(1, 1)
            )
        ),

        // Decors
        instantiateColumnBanner(world, position + glm::vec2(-32, -8)),
        instantiateColumnBanner(world, position + glm::vec2(16, -8)),

        // Enemies:
        instantiateVoidSlime(world, position + glm::vec2(-8, -8)),
        instantiateLavaSlime(world, position + glm::vec2(-48, 16)),
        instantiateLavaSlime(world, position + glm::vec2(32, -32)),
        instantiateSlimeLvl2(world, position + glm::vec2(-48, -32)),
        instantiateSlimeLvl2(world, position + glm::vec2(32, 16)),
    });

    return chunkHolderEnt;
}