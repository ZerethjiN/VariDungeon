#pragma once

#include "ImageAsset.hpp"

class TileMapTileInfo final {
public:
    TileMapTileInfo(const ImageData& newImageData):
        imageData(&newImageData),
        anim(nullptr) {
    }

    TileMapTileInfo(const AnimationData& newAnim):
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
        if (curTime >= (*anim).at(curAnim).first) {
            curTime -= (*anim).at(curAnim).first;
            curAnim++;
            if (curAnim >= anim->size()) {
                curAnim = 0;
            }
        }
        return (*anim).at(curAnim).second;
    }

    const ImageData& getCurImage() const {
        if (imageData != nullptr) {
            return *imageData;
        }
        return (*anim).at(curAnim).second;
    }

private:
    const ImageData* imageData;
    const AnimationData* anim;
    std::size_t curAnim;
    float curTime;
};

class TileMap final: public IComponent {
public:
    TileMap(TextureManager& textureManager, const std::vector<TileMapTileInfo>& newTiles, const glm::uvec2& newTileMapSize, const glm::uvec2& newTileSize):
        tiles(),
        tilemapSize(newTileMapSize),
        tileSize(newTileSize),
        color(255, 255, 255, 255) {
        for (const auto& newTile: newTiles) {
            tiles.emplace_back(newTile, std::array<SSBOVertex, 4>());
        }
        load(textureManager);
    }

public:
    void load(TextureManager& textureManager) {
        for (unsigned int i = 0; i < tilemapSize.x; ++i) {
            for (unsigned int j = 0; j < tilemapSize.y; ++j) {
                const glm::uvec4& tileRect = tiles[i + j * tilemapSize.x].first.getCurImage().spriteRect;
                const glm::vec2& origin = tiles[i + j * tilemapSize.x].first.getCurImage().origin;

                const std::shared_ptr<Texture> texture = textureManager[tiles[i + j * tilemapSize.x].first.getCurImage().filename];
                const glm::ivec2 originalTextureSize(texture->size);

                auto& quad = tiles[i + j * tilemapSize.x].second;

                const float left   = static_cast<float>(tileRect.x) / static_cast<float>(originalTextureSize.x);
                const float right  = left + static_cast<float>(tileRect.z) / static_cast<float>(originalTextureSize.x);
                const float top    = static_cast<float>(tileRect.y) / static_cast<float>(originalTextureSize.y);
                const float bottom = top + static_cast<float>(tileRect.w) / static_cast<float>(originalTextureSize.y);

                quad[0] = {
                    glm::vec2((tileSize.x * i) + (-origin.x * tileRect.z), (tileSize.y * j) + (-origin.y * tileRect.w)),
                    glm::vec2(left, top)
                };
                quad[1] = {
                    glm::vec2((tileSize.x * i) + (-origin.x * tileRect.z), (tileSize.y * j) + ((1 - origin.y) * tileRect.w)),
                    glm::vec2(left, bottom)
                };
                quad[2] = {
                    glm::vec2((tileSize.x * i) + ((1 - origin.x) *  tileRect.z), (tileSize.y * j) + (-origin.y * tileRect.w)),
                    glm::vec2(right, top)
                };
                quad[3] = {
                    glm::vec2((tileSize.x * i) + ((1 - origin.x) * tileRect.z), (tileSize.y * j) + ((1 - origin.y) * tileRect.w)),
                    glm::vec2(right, bottom)
                };
            }
        }
    }

public:
    void update(TextureManager& textureManager, float delta) {
        for (unsigned int i = 0; i < tilemapSize.x; ++i) {
            for (unsigned int j = 0; j < tilemapSize.y; ++j) {
                const glm::uvec4& tileRect = tiles[i + j * tilemapSize.x].first.getCurImage(delta).spriteRect;

                const std::shared_ptr<Texture> texture = textureManager[tiles[i + j * tilemapSize.x].first.getCurImage().filename];
                const glm::ivec2 originalTextureSize(texture->size);

                auto& quad = tiles[i + j * tilemapSize.x].second;

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
    std::vector<std::pair<TileMapTileInfo, std::array<SSBOVertex, 4>>> tiles;
    glm::uvec2 tilemapSize;
    const glm::uvec2 tileSize;
    glm::vec4 color;
};

///////////////////////////////////////////////////////////////////////////////////

void updateTileMapSys(LateFixedSystem, World& world) {
    auto tilemaps = world.view<TileMap>();

    auto [textureManager, time] = world.resource<TextureManager, const Time>();

    for (auto [_, tilemap]: tilemaps) {
        // tilemap.update(textureManager, time.fixedDelta());
    }
}