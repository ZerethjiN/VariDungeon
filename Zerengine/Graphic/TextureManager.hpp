#pragma once
#include <unordered_map>
#include <string>
#include "Texture.hpp"

class TextureManager final: public IResource {
public:
    TextureManager() noexcept:
        textures(),
        mtx() {
    }

    TextureManager(const TextureManager& oth) noexcept:
        textures(oth.textures),
        mtx() {
    }

public:
    ~TextureManager() {
        for (auto& pair: textures) {
            delete pair.second;
        }
    }

public:
    [[nodiscard]] const Texture& operator[](const std::string& newFilename) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!textures.contains(newFilename)) {
            textures.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(newFilename),
                std::forward_as_tuple(new Texture(newFilename))
            );
        }
        return *static_cast<Texture*>(textures.at(newFilename));
    }

    void clear(World& world) noexcept; // Define in "Sprite.hpp"

private:
    std::unordered_map<std::string, Texture*> textures;
    std::mutex mtx;
};