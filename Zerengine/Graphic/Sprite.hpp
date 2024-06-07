#pragma once

#include "Texture.hpp"
#include "ImageAsset.hpp"
#include "TextureManager.hpp"

struct SSBOVertex {
public:
    constexpr SSBOVertex() noexcept = default;

    constexpr SSBOVertex(const glm::vec2& newPosition, const glm::vec2& newTexCoord) noexcept:
        position(newPosition), texCoord(newTexCoord) {
    }

public:
    glm::vec2 position;
    glm::vec2 texCoord;
};

class Sprite {
public:
    Sprite(const Texture& newTexture, const glm::uvec4& newTextureRect, const glm::vec2& newOrigin, const glm::vec4& newColor = glm::vec4(255, 255, 255, 255)):
        texture(newTexture),
        color(newColor),
        origin(newOrigin),
        isMirror(false) {
        setTextureRect(newTextureRect);
    }

public:
    [[nodiscard]] const glm::uvec4& getTextureRect() const noexcept {
        return textureRect;
    }

    void setTextureRect(const ImageData& imageData) {
        origin = imageData.origin;
        setTextureRect(imageData.spriteRect);
    }

    void setColor(const glm::vec4& newColor) noexcept {
        color = newColor;
    }

    [[nodiscard]] const glm::vec4& getColor() const noexcept {
        return color;
    }

    void setMirror(bool val) {
        isMirror = val;
        setTextureRect(textureRect);
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

        if (isMirror == 0) {
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

public:
    std::array<SSBOVertex, 4> vertices;
    const Texture& texture;
    glm::uvec4 textureRect;
    glm::vec2 origin;
    glm::vec4 color;
    bool isMirror;
};

///////////////////////////////////////////////////////////////////////////////////

enum UIAnchor: uint8_t {
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

class UI {
public:
    UI(const Texture& newTexture, const glm::uvec4& newTextureRect, const glm::vec2& newOrigin, const UIAnchor newAnchor, const glm::vec4& newColor = glm::vec4(255, 255, 255, 255)):
        origin(newOrigin),
        color(newColor),
        texture(newTexture),
        anchor(newAnchor) {
        setTextureRect(newTextureRect);
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

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

public:
    std::array<SSBOVertex, 4> vertices;
    glm::uvec4 textureRect;
    glm::vec2 origin;
    glm::vec4 color;
    const Texture& texture;

public:
    UIAnchor anchor;
};

///////////////////////////////////////////////////////////////////////////////////

class ZIndex {
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

class IsUnlit {};

///////////////////////////////////////////////////////////////////////////////////

class SpriteCreator {
public:
    SpriteCreator(const ImageAsset& newImageAsset, int imageDataIndex, const glm::vec4& newColor = glm::ivec4(255, 255, 255, 255)):
        filename(newImageAsset.filename),
        rect(newImageAsset[imageDataIndex].spriteRect),
        rotation(0),
        origin(newImageAsset[imageDataIndex].origin),
        color(newColor) {
    }

    SpriteCreator(const ImageAsset& newImageAsset, const glm::vec4& newColor = glm::ivec4(255, 255, 255, 255)):
        filename(newImageAsset.filename),
        rect(newImageAsset[0].spriteRect),
        rotation(0),
        origin(newImageAsset[0].origin),
        color(newColor) {
    }

public:
    std::string filename;
    glm::ivec4 rect;
    float rotation;
    glm::vec2 origin;
    glm::vec4 color;
};

void spriteCreatorSys(LateFixedSystem, World& world) {
    auto [texManager] = world.resource<TextureManager>();
    for (auto [entSprite, creator]: world.view<const SpriteCreator>()) {
        world.add(entSprite, Sprite(texManager.get(creator.filename), creator.rect, creator.origin, creator.color));
        world.remove<SpriteCreator>(entSprite);
    }
}

///////////////////////////////////////////////////////////////////////////////////

class UICreator {
public:
    UICreator(const ImageAsset& newImageAsset, int imageDataIndex, const UIAnchor newAnchor, const glm::vec4& newColor = glm::ivec4(255, 255, 255, 255)):
        filename(newImageAsset.filename),
        rect(newImageAsset[imageDataIndex].spriteRect),
        anchor(newAnchor),
        origin(newImageAsset[imageDataIndex].origin),
        color(newColor) {
    }

    UICreator(const ImageAsset& newImageAsset, const UIAnchor newAnchor, const glm::vec4& newColor = glm::ivec4(255, 255, 255, 255)):
        filename(newImageAsset.filename),
        rect(newImageAsset[0].spriteRect),
        anchor(newAnchor),
        origin(newImageAsset[0].origin),
        color(newColor) {
    }

public:
    std::string filename;
    glm::ivec4 rect;
    UIAnchor anchor;
    glm::vec2 origin;
    glm::vec4 color;
};

void uiCreatorSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [texManager] = world.resource<TextureManager>();
    for (auto [entUI, creator]: world.view<const UICreator>()) {
        world.add(entUI, UI(texManager.get(creator.filename), creator.rect, creator.origin, creator.anchor, creator.color));
        world.remove<UICreator>(entUI);
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////