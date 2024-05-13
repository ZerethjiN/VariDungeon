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

enum AnimationType: uint8_t {
    LOOP,
    BOOMERANG,
    ONE_SHOT
};

class AnimationData final {
public:
    AnimationData(const std::initializer_list<std::pair<float, ImageData>>& newAnimations, AnimationType newType = AnimationType::LOOP) noexcept:
        animations(newAnimations),
        type(newType) {
        float newTotalDuration = 0;
        for (const auto& pair: newAnimations) {
            newTotalDuration += pair.first;
        }
        totalDuration = newTotalDuration;
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept {
        return animations.size();
    }

    [[nodiscard]] constexpr const std::pair<float, ImageData>& at(size_t index) const noexcept {
        return animations.at(index);
    }

    [[nodiscard]] constexpr AnimationType getAnimationType() const noexcept {
        return type;
    }

    [[nodiscard]] constexpr float getTotalDuration() const noexcept {
        return totalDuration;
    }

private:
    const std::vector<std::pair<float, ImageData>> animations;
    const AnimationType type;
    float totalDuration;
};

class AnimationAsset final {
public:
    [[nodiscard]] AnimationAsset(const std::initializer_list<std::unordered_map<std::string, const AnimationData>::value_type>& newAnims) noexcept:
        anims(newAnims) {
    }

    [[nodiscard]] constexpr const AnimationData& operator [](const std::string& name) const noexcept {
        return anims.at(name);
    }

public:
    const std::unordered_map<std::string, const AnimationData> anims;
};