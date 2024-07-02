#pragma once
#include <unordered_map>
#include <string>
#include "Texture.hpp"

class TextureManager final {
public:
    ~TextureManager() {
        for (auto& pair: textures) {
            delete pair.second;
        }
    }

public:
    [[nodiscard]] const Texture& get(const std::string& newFilename) {
        if (!textures.contains(newFilename)) {
            textures.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(newFilename),
                std::forward_as_tuple(new Texture(newFilename))
            );
        }
        return *static_cast<Texture*>(textures.at(newFilename));
    }

    void clear() noexcept {
        for (auto& pair: textures) {
            delete pair.second;
        }
        textures.clear();
    }

private:
    std::unordered_map<std::string, Texture*> textures;
};