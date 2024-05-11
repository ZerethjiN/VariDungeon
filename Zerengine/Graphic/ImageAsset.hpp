#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

struct ImageData {
public:
    constexpr ImageData(const glm::uvec4& newSpriteRect, const glm::vec2& newOrigin) noexcept:
        spriteRect(newSpriteRect),
        origin(newOrigin) {
    }

public:
    const glm::uvec4 spriteRect;
    const glm::vec2 origin;
};

class ImageAsset final {
public:
    [[nodiscard]] constexpr ImageAsset(const std::string& newFilename, const std::initializer_list<ImageData>& newAssets) noexcept:
        filename(newFilename),
        assets(newAssets) {
    }

    [[nodiscard]] constexpr const ImageData& operator [](int idx) const noexcept {
        return assets[idx];
    }

public:
    const std::string filename;
    const std::vector<ImageData> assets;
};

class AnimationAsset final {
public:
    [[nodiscard]] AnimationAsset(const std::initializer_list<std::unordered_map<std::string, const std::vector<std::pair<float, ImageData>>>::value_type>& newAnims) noexcept:
        anims(newAnims) {
    }

    [[nodiscard]] constexpr const std::vector<std::pair<float, ImageData>>& operator [](const std::string& name) const noexcept {
        return anims.at(name);
    }

public:
    const std::unordered_map<std::string, const std::vector<std::pair<float, ImageData>>> anims;
};