#pragma once

#include "Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

class Glyph final: public IComponent {
public:
    Glyph(std::shared_ptr<Texture> newTexture, unsigned int newAdvance, const glm::ivec2& newSize, const glm::ivec2& newbearing):
        texture(newTexture),
        advance(newAdvance),
        size(newSize),
        bearing(newbearing) {
    }

public:
    std::shared_ptr<Texture> texture;
    unsigned int advance;
    glm::ivec2 size;
    glm::ivec2 bearing;
};

class ZreFont final: public IComponent {
public:
    ZreFont(const std::string& new_filename) {
        loadFromFile(new_filename);
    }

    ~ZreFont() {
        FT_Done_Face(ftFace);
        FT_Done_FreeType(ftLibrary);
    }

    void loadFromFile(const std::string& newFilename) {
        if (filename != newFilename) {
            filename = newFilename;
            FT_Init_FreeType(&ftLibrary);
            FT_New_Face(ftLibrary, newFilename.c_str(), 0, &ftFace);
        }
    }

    const Glyph& getGlyph(unsigned char letter, unsigned int characterSize) {
        if (!glyphs.contains(letter)) {
            glyphs.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(letter),
                std::forward_as_tuple()
            );
        }
        if (!glyphs.at(letter).contains(characterSize)) {
            FT_Set_Pixel_Sizes(ftFace, 0, characterSize);

            FT_Load_Char(ftFace, letter, FT_LOAD_RENDER);

            std::shared_ptr<Texture> newTexture;

            if (ftFace->glyph->bitmap.buffer != nullptr) {
                std::vector<unsigned char> newBuffer(ftFace->glyph->bitmap.width * ftFace->glyph->bitmap.rows * 4);
                for (std::size_t i = 0; i < ftFace->glyph->bitmap.width * ftFace->glyph->bitmap.rows * 4; i += 4) {
                    newBuffer[i + 0] = ftFace->glyph->bitmap.buffer[(i / 4)];
                    newBuffer[i + 1] = ftFace->glyph->bitmap.buffer[(i / 4)];
                    newBuffer[i + 2] = ftFace->glyph->bitmap.buffer[(i / 4)];
                    newBuffer[i + 3] = ftFace->glyph->bitmap.buffer[(i / 4)];
                }

                newTexture = std::make_shared<Texture>(newBuffer.data(), ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows, 4);
            }

            glyphs.at(letter).emplace(
                std::piecewise_construct,
                std::forward_as_tuple(characterSize),
                std::forward_as_tuple(
                    newTexture,
                    static_cast<unsigned int>(ftFace->glyph->advance.x),
                    glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
                    glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top)
                )
            );
        }
        return glyphs.at(letter).at(characterSize);
    }

private:
    std::string filename;
    FT_Library ftLibrary;
    FT_Face ftFace;
    std::unordered_map<unsigned char, std::unordered_map<unsigned int, Glyph>> glyphs;
};

class FontManager final: public IResource {
public:
    [[nodiscard]] std::shared_ptr<ZreFont> get(const std::string& filename) {
        if (!fonts.contains(filename)) {
            fonts.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(filename),
                std::forward_as_tuple(std::make_shared<ZreFont>(filename))
            );
        }
        return fonts.at(filename);
    }

    void clear() noexcept {
        fonts.clear();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<ZreFont>> fonts;
};