#pragma once

#include "ImageAsset.hpp"

class TileMapTileInfo {
public:
    TileMapTileInfo(const ImageData& newImageData):
        imageData(&newImageData),
        anim(nullptr) {
    }

    TileMapTileInfo(const std::vector<std::pair<float, ImageData>>& newAnim):
        imageData(nullptr),
        anim(&newAnim),
        curAnim(0),
        curTime(0) {
    }

public:
    const ImageData& getCurImage(float delta) {
        if (imageData != nullptr) {
            return *imageData;
        }
        curTime += delta;
        if (curTime >= (*anim)[curAnim].first) {
            curTime -= (*anim)[curAnim].first;
            curAnim++;
            if (curAnim >= anim->size()) {
                curAnim = 0;
            }
        }
        return (*anim)[curAnim].second;
    }

private:
    const ImageData* imageData;
    const std::vector<std::pair<float, ImageData>>* anim;
    int curAnim;
    float curTime;
};

class TileMap {
public:
    TileMap(const Texture& newTexture, const std::vector<TileMapTileInfo>& newTiles, const glm::uvec2& newTileMapSize, const glm::uvec2& newTileSize):
        texture(newTexture),
        tiles(newTiles),
        tilemapSize(newTileMapSize),
        tileSize(newTileSize),
        vertices(),
        color(255, 255, 255, 255) {
        load();
    }

public:
    void load() {
        const glm::ivec2 originalTextureSize(texture.size);

        vertices.resize(tilemapSize.x * tilemapSize.y);

        for (unsigned int i = 0; i < tilemapSize.x; ++i) {
            for (unsigned int j = 0; j < tilemapSize.y; ++j) {
                const glm::uvec4& tileRect = tiles[i + j * tilemapSize.x].getCurImage(0).spriteRect;

                auto& quad = vertices[i + j * tilemapSize.x];

                const float left   = static_cast<float>(tileRect.x) / static_cast<float>(originalTextureSize.x);
                const float right  = left + static_cast<float>(tileRect.z) / static_cast<float>(originalTextureSize.x);
                const float top    = static_cast<float>(tileRect.y) / static_cast<float>(originalTextureSize.y);
                const float bottom = top + static_cast<float>(tileRect.w) / static_cast<float>(originalTextureSize.y);

                quad[0] = {
                    glm::vec2((tileSize.x * i) + (-0.5f * tileRect.z), (tileSize.y * j) + (-0.5f * tileRect.w)),
                    glm::vec2(left, top)
                };
                quad[1] = {
                    glm::vec2((tileSize.x * i) + (-0.5f * tileRect.z), (tileSize.y * j) + ((1 - 0.5f) * tileRect.w)),
                    glm::vec2(left, bottom)
                };
                quad[2] = {
                    glm::vec2((tileSize.x * i) + ((1 - 0.5f) *  tileRect.z), (tileSize.y * j) + (-0.5f * tileRect.w)),
                    glm::vec2(right, top)
                };
                quad[3] = {
                    glm::vec2((tileSize.x * i) + ((1 - 0.5f) * tileRect.z), (tileSize.y * j) + ((1 - 0.5f) * tileRect.w)),
                    glm::vec2(right, bottom)
                };
            }
        }
    }

public:
    void update(float delta) {
        const glm::ivec2 originalTextureSize(texture.size);
        for (unsigned int i = 0; i < tilemapSize.x; ++i) {
            for (unsigned int j = 0; j < tilemapSize.y; ++j) {
                const glm::uvec4& tileRect = tiles[i + j * tilemapSize.x].getCurImage(delta).spriteRect;

                auto& quad = vertices[i + j * tilemapSize.x];

                const float left   = static_cast<float>(tileRect.x) / static_cast<float>(originalTextureSize.x);
                const float right  = left + static_cast<float>(tileRect.z) / static_cast<float>(originalTextureSize.x);
                const float top    = static_cast<float>(tileRect.y) / static_cast<float>(originalTextureSize.y);
                const float bottom = top + static_cast<float>(tileRect.w) / static_cast<float>(originalTextureSize.y);

                quad[0] = {
                    glm::vec2((tileSize.x * i) + (-0.5f * tileRect.z), (tileSize.y * j) + (-0.5f * tileRect.w)),
                    glm::vec2(left, top)
                };
                quad[1] = {
                    glm::vec2((tileSize.x * i) + (-0.5f * tileRect.z), (tileSize.y * j) + ((1 - 0.5f) * tileRect.w)),
                    glm::vec2(left, bottom)
                };
                quad[2] = {
                    glm::vec2((tileSize.x * i) + ((1 - 0.5f) *  tileRect.z), (tileSize.y * j) + (-0.5f * tileRect.w)),
                    glm::vec2(right, top)
                };
                quad[3] = {
                    glm::vec2((tileSize.x * i) + ((1 - 0.5f) * tileRect.z), (tileSize.y * j) + ((1 - 0.5f) * tileRect.w)),
                    glm::vec2(right, bottom)
                };
            }
        }
    }

public:
    const Texture& texture;
    std::vector<TileMapTileInfo> tiles;
    glm::uvec2 tilemapSize;
    const glm::uvec2 tileSize;
    std::vector<std::array<SSBOVertex, 4>> vertices;
    glm::vec4 color;
};

///////////////////////////////////////////////////////////////////////////////////

class TileMapCreator {
public:
    TileMapCreator(const std::string& newFilename, const std::vector<TileMapTileInfo>& newTiles, const glm::uvec2& newTileMapSize, const glm::uvec2& newTileSize):
        filename(newFilename),
        tiles(newTiles),
        tileMapSize(newTileMapSize),
        tileSize(newTileSize) {
    }

public:
    const std::string filename;
    const std::vector<TileMapTileInfo> tiles;
    const glm::uvec2 tileMapSize;
    const glm::uvec2 tileSize;
};

void tileMapCreatorSys(LateFixedSystem, World& world) {
    auto [texManager] = world.resource<TextureManager>();
    for (auto [entUI, creator]: world.view<const TileMapCreator>()) {
        world.add(entUI, TileMap(texManager.get(creator.filename), creator.tiles, creator.tileMapSize, creator.tileSize));
        world.del<TileMapCreator>(entUI);
    }
}

///////////////////////////////////////////////////////////////////////////////////

void updateTileMapSys(LateFixedSystem, World& world) {
    auto tilemaps = world.view<TileMap>();

    auto [time] = world.resource<const Time>();

    for (auto [_, tilemap]: tilemaps) {
        tilemap.update(time.fixedDelta());
    }
}