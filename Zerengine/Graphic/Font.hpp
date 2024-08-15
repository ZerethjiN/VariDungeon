#pragma once

#include "Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

class Glyph final {
public:
    Glyph(const Texture* newTexture, unsigned int newAdvance, const glm::ivec2& newSize, const glm::ivec2& newbearing):
        texture(newTexture),
        advance(newAdvance),
        size(newSize),
        bearing(newbearing) {
    }

    ~Glyph() {
        if (texture) {
            delete texture;
        }
    }

public:
    const Texture* texture;
    unsigned int advance;
    glm::ivec2 size;
    glm::ivec2 bearing;
};

class ZreFont final {
public:
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

            Texture* newTexture = nullptr;
            if (ftFace->glyph->bitmap.buffer != nullptr) {
                newTexture = new Texture(ftFace->glyph->bitmap.buffer, ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows, 1);
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

class FontManager final {
public:
    ~FontManager() {
        for (auto& pair: fonts) {
            delete pair.second;
        }
    }

public:
    ZreFont& get(const std::string& filename) {
        if (!fonts.contains(filename)) {
            auto* newFont = new ZreFont();
            newFont->loadFromFile(filename);
            fonts.emplace(filename, newFont);
        }
        return *fonts.at(filename);
    }

    void clear() noexcept {
        for (auto& pair: fonts) {
            delete pair.second;
        }
        fonts.clear();
    }

private:
    std::unordered_map<std::string, ZreFont*> fonts;
};