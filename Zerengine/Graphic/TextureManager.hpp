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
    [[nodiscard]] std::shared_ptr<Texture> operator[](const std::string& new_filename) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!textures.contains(new_filename)) {
            textures.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(new_filename),
                std::forward_as_tuple(std::make_shared<Texture>(new_filename))
            );
        }
        return textures.at(new_filename);
    }

    void clear(World& world) noexcept; // Define in "Sprite.hpp"

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::mutex mtx;
};