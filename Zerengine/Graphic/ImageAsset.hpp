#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

struct ImageData final {
public:
    constexpr ImageData(const std::string& newFilename, const std::tuple<glm::uvec4, glm::vec2>& newAsset) noexcept:
        filename(newFilename),
        spriteRect(std::get<0>(newAsset)),
        origin(std::get<1>(newAsset)) {
    }

public:
    const std::string filename;
    const glm::uvec4 spriteRect;
    const glm::vec2 origin;
};

class ImageAsset final {
public:
    [[nodiscard]] constexpr ImageAsset(const std::string& newFilename, const std::initializer_list<std::tuple<glm::uvec4, glm::vec2>>& newAssets) noexcept:
        filename(newFilename) {
        for (const auto& newAsset: newAssets) {
            assets.emplace_back(newFilename, newAsset);
        }
    }

    [[nodiscard]] constexpr const ImageData& operator [](int idx) const noexcept {
        return assets.at(idx);
    }

public:
    const std::string filename;
    std::vector<ImageData> assets;
};

enum class AnimationType: uint8_t {
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

    [[nodiscard]] constexpr const std::pair<float, ImageData>& at(std::size_t index) const noexcept {
        return animations[index];
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

template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
constexpr inline std::in_place_type_t<E> animEnum {};

class AnimationAsset final {
public:
    template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
    [[nodiscard]] AnimationAsset(std::in_place_type_t<E>, const std::initializer_list<std::pair<E, const AnimationData>>& newAnims) noexcept:
        anims(reinterpret_cast<const std::initializer_list<std::unordered_map<std::size_t, const AnimationData>::value_type>&>(newAnims)) {
    }

    template <typename E> requires (std::is_enum_v<E> && std::is_same_v<std::underlying_type_t<E>, std::size_t> && std::is_scoped_enum_v<E>)
    [[nodiscard]] constexpr const AnimationData& operator[](const E& name) const noexcept {
        if (!anims.contains(static_cast<std::size_t>(name))) {
            printf("Nik, L'erreur c'est le numero: %zu\n", static_cast<std::size_t>(name));
        }

        return anims.at(static_cast<std::size_t>(name));
    }

public:
    const std::unordered_map<std::size_t, const AnimationData> anims;
};