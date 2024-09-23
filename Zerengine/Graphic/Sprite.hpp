#pragma once

#include "Texture.hpp"
#include "ImageAsset.hpp"
#include "TextureManager.hpp"

struct SSBOVertex final {
public:
    constexpr SSBOVertex() noexcept = default;

    constexpr SSBOVertex(const glm::vec2& newPosition, const glm::vec2& newTexCoord) noexcept:
        position(newPosition), texCoord(newTexCoord) {
    }

public:
    glm::vec2 position;
    glm::vec2 texCoord;
};

class Sprite final {
public:
    Sprite(TextureManager& textureManager, const ImageAsset& newImageAsset, std::size_t imageDataIndex, const Color& newColor = Color(255, 255, 255, 255)):
        texture(textureManager[newImageAsset.filename]),
        color(newColor),
        isMirror(false) {
        setTextureRect(newImageAsset[imageDataIndex]);
    }

    Sprite(TextureManager& textureManager, const ImageAsset& newImageAsset, const Color& newColor = Color(255, 255, 255, 255)):
        texture(textureManager[newImageAsset.filename]),
        color(newColor),
        isMirror(false) {
        setTextureRect(newImageAsset[0]);
    }

public:
    [[nodiscard]] const glm::uvec4& getTextureRect() const noexcept {
        return textureRect;
    }

    void setTextureRect(const ImageData& imageData) {
        origin = imageData.origin;
        setTextureRect(imageData.spriteRect);
    }

    void setColor(const Color& newColor) noexcept {
        color = newColor;
    }

    [[nodiscard]] const Color& getColor() const noexcept {
        return color;
    }

    void setMirror(bool val) {
        if (isMirror != val) {
            isMirror = val;
            setTextureRect(textureRect);
        }
    }

    [[nodiscard]] constexpr bool getIsMirror() const noexcept {
        return isMirror;
    }

    void setTextureRect(const glm::uvec4& newTextureRect) {
        textureRect = newTextureRect;
        const glm::ivec2 originalTextureSize(texture.size);

        const float left   = static_cast<float>(textureRect.x) / static_cast<float>(originalTextureSize.x);
        const float right  = left + static_cast<float>(textureRect.z) / static_cast<float>(originalTextureSize.x);
        const float top    = static_cast<float>(textureRect.y) / static_cast<float>(originalTextureSize.y);
        const float bottom = top + static_cast<float>(textureRect.w) / static_cast<float>(originalTextureSize.y);

        if (isMirror == false) {
            vertices[0] = {
                glm::vec2(-origin.x * textureRect.z, -origin.y * textureRect.w),
                glm::vec2(left, top)
            };
            vertices[1] = {
                glm::vec2(-origin.x * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(left, bottom)
            };
            vertices[2] = {
                glm::vec2((1 - origin.x) * textureRect.z, -origin.y * textureRect.w),
                glm::vec2(right, top)
            };
            vertices[3] = {
                glm::vec2((1 - origin.x) * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(right, bottom)
            };
        } else {
            vertices[0] = {
                glm::vec2(-origin.x * textureRect.z, -origin.y * textureRect.w),
                glm::vec2(right, top)
            };
            vertices[1] = {
                glm::vec2(-origin.x * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(right, bottom)
            };
            vertices[2] = {
                glm::vec2((1 - origin.x) *  textureRect.z, -origin.y * textureRect.w),
                glm::vec2(left, top)
            };
            vertices[3] = {
                glm::vec2((1 - origin.x) * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(left, bottom)
            };
        }
    }

    std::array<SSBOVertex, 4> getHorizontalMirror() const noexcept {
        const glm::ivec2 originalTextureSize(texture.size);

        const float left   = static_cast<float>(textureRect.x) / static_cast<float>(originalTextureSize.x);
        const float right  = left + static_cast<float>(textureRect.z) / static_cast<float>(originalTextureSize.x);
        const float top    = static_cast<float>(textureRect.y) / static_cast<float>(originalTextureSize.y);
        const float bottom = top + static_cast<float>(textureRect.w) / static_cast<float>(originalTextureSize.y);

        if (isMirror) {
            return std::array<SSBOVertex, 4>({
                {
                    glm::vec2(-origin.x * textureRect.z, -origin.y * textureRect.w),
                    glm::vec2(right, bottom)
                },
                {
                    glm::vec2(-origin.x * textureRect.z, (1 - origin.y) * textureRect.w),
                    glm::vec2(right, top)
                },
                {
                    glm::vec2((1 - origin.x) *  textureRect.z, -origin.y * textureRect.w),
                    glm::vec2(left, bottom)
                },
                {
                    glm::vec2((1 - origin.x) * textureRect.z, (1 - origin.y) * textureRect.w),
                    glm::vec2(left, top)
                }
            });
        }
        return std::array<SSBOVertex, 4>({
            {
                glm::vec2(-origin.x * textureRect.z, -origin.y * textureRect.w),
                glm::vec2(left, bottom)
            },
            {
                glm::vec2(-origin.x * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(left, top)
            },
            {
                glm::vec2((1 - origin.x) *  textureRect.z, -origin.y * textureRect.w),
                glm::vec2(right, bottom)
            },
            {
                glm::vec2((1 - origin.x) * textureRect.z, (1 - origin.y) * textureRect.w),
                glm::vec2(right, top)
            }
        });
    }

public:
    std::array<SSBOVertex, 4> vertices;
    const Texture& texture;
    glm::uvec4 textureRect;
    glm::vec2 origin;
    Color color;
    bool isMirror;
};

///////////////////////////////////////////////////////////////////////////////////

enum class UIAnchor: uint8_t {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER_CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

class UI final  {
public:
    UI(TextureManager& textureManager, const ImageAsset& newImageAsset, std::size_t imageDataIndex, const UIAnchor newAnchor, const Color& newColor = Color(255, 255, 255, 255)):
        texture(textureManager[newImageAsset.filename]),
        color(newColor),
        anchor(newAnchor) {
        setTextureRect(newImageAsset[imageDataIndex]);
    }

    UI(TextureManager& textureManager, const ImageAsset& newImageAsset, const UIAnchor newAnchor, const Color& newColor = Color(255, 255, 255, 255)):
        texture(textureManager[newImageAsset.filename]),
        color(newColor),
        anchor(newAnchor) {
        setTextureRect(newImageAsset[0]);
    }

public:
    void setTextureRect(const ImageData& imageData) {
        origin = imageData.origin;
        setTextureRect(imageData.spriteRect);
    }

    [[nodiscard]] const glm::uvec4& getTextureRect() const noexcept {
        return textureRect;
    }

    void setTextureRect(const glm::uvec4& newTextureRect) {
        textureRect = newTextureRect;
        const glm::ivec2 originalTextureSize(texture.size);

        const float left   = static_cast<float>(textureRect.x) / static_cast<float>(originalTextureSize.x);
        const float right  = left + static_cast<float>(textureRect.z) / static_cast<float>(originalTextureSize.x);
        const float top    = static_cast<float>(textureRect.y) / static_cast<float>(originalTextureSize.y);
        const float bottom = top + static_cast<float>(textureRect.w) / static_cast<float>(originalTextureSize.y);

        vertices[0] = {
            glm::vec2(-origin.x * textureRect.z, -origin.y * textureRect.w),
            glm::vec2(left, top)
        };
        vertices[1] = {
            glm::vec2(-origin.x * textureRect.z, (1 - origin.y) * textureRect.w),
            glm::vec2(left, bottom)
        };
        vertices[2] = {
            glm::vec2((1 - origin.x) *  textureRect.z, -origin.y * textureRect.w),
            glm::vec2(right, top)
        };
        vertices[3] = {
            glm::vec2((1 - origin.x) * textureRect.z, (1 - origin.y) * textureRect.w),
            glm::vec2(right, bottom)
        };
    }

    void setColor(const Color& newColor) {
        color = newColor;
    }

public:
    std::array<SSBOVertex, 4> vertices;
    glm::uvec4 textureRect;
    glm::vec2 origin;
    Color color;
    const Texture& texture;

public:
    UIAnchor anchor;
};

///////////////////////////////////////////////////////////////////////////////////

class ZIndex final {
public:
    constexpr ZIndex(int newlayer) noexcept:
        layer(newlayer) {
    }

    [[nodiscard]] constexpr operator int() const noexcept {
        return layer;
    }

    constexpr ZIndex& operator=(int newValue) noexcept {
        layer = newValue;
        return *this;
    }

public:
    int layer;
};

class IsUnlit final  {};

///////////////////////////////////////////////////////////////////////////////////

// Co Dependency implem

void TextureManager::clear(World& world) noexcept {
    std::unique_lock<std::mutex> lock(mtx);
    std::unordered_set<Texture*> keepedTextures;
    for (auto [_, sprite]: world.view<Sprite>(with<DontDestroyOnLoad>)) {
        keepedTextures.emplace(&const_cast<Texture&>(sprite.texture));
    }
    for (auto& pair: textures) {
        if (!keepedTextures.contains(pair.second)) {
            delete pair.second;
        }
    }
    textures.clear();
    for (auto* reinjectedTexture: keepedTextures) {
        textures.emplace(reinjectedTexture->name, reinjectedTexture);
    }
}