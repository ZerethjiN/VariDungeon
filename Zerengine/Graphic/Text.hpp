#pragma once

#include "Font.hpp"
#include "Sprite.hpp"

enum TextAlignementType: uint8_t {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
};

class TextUI {
public:
    TextUI(const std::string& newText, ZreFont& newFont, unsigned int newSize, const glm::vec2& newOrigin, const UIAnchor newAnchor, const glm::vec2& newTextBoxSize, const TextAlignementType newAlignement, const glm::vec4& newColor = glm::vec4(242, 214, 136, 255)):
        text(newText),
        font(&newFont),
        size(newSize),
        textBoxSize(newTextBoxSize),
        origin(newOrigin),
        color(newColor),
        alignement(newAlignement),
        anchor(newAnchor) {
        needRefreshVertices = true;
    }

public:
    void setFont(ZreFont& newFont) {
        font = &newFont;
        needRefreshVertices = true;
    }

    void setString(const std::string& newText) {
        text = newText;
        needRefreshVertices = true;
    }

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

public:
    void updateVertices() {
        if (alignement == TextAlignementType::ALIGN_CENTER) {
            updateVerticesCenter();
        } else if (alignement == TextAlignementType::ALIGN_RIGHT) {
            updateVerticesAlignRight();
        } else {
            updateVerticesAlignLeft();
        }
    }

private:
    void updateVerticesAlignLeft() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float x = 0;
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    x = 0;
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = 0;
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void updateVerticesCenter() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float lineX = 0;

            std::vector<std::size_t> lineAdjusts;
            for (const auto& word: words) {
                auto futurX = lineX;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    lineAdjusts.push_back((textBoxSize.x - lineX) / 2);
                    lineX = futurX - lineX;
                } else {
                    lineX = futurX;
                    const auto& spaceGlyph = font->getGlyph(' ', size);
                    lineX += (spaceGlyph.advance >> 6);
                }
            }

            lineAdjusts.push_back((textBoxSize.x - lineX) / 2);

            std::size_t nLine = 0;

            float x = lineAdjusts[nLine];
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    nLine++;
                    x = lineAdjusts[nLine];
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = lineAdjusts[nLine];
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void updateVerticesAlignRight() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float lineX = 0;

            std::vector<std::size_t> lineAdjusts;
            for (const auto& word: words) {
                auto futurX = lineX;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    lineAdjusts.push_back((textBoxSize.x - lineX));
                    lineX = futurX - lineX;
                } else {
                    lineX = futurX;
                    const auto& spaceGlyph = font->getGlyph(' ', size);
                    lineX += (spaceGlyph.advance >> 6);
                }
            }

            lineAdjusts.push_back((textBoxSize.x - lineX));

            std::size_t nLine = 0;

            float x = lineAdjusts[nLine];
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    nLine++;
                    x = lineAdjusts[nLine];
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = lineAdjusts[nLine];
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void splitText() noexcept {
        std::string delimiter = " ";
        std::string token;
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        words.clear();

        while ((pos_end = text.find(delimiter, pos_start)) != std::string::npos) {
            token = text.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            words.push_back(token);
        }

        words.push_back(text.substr(pos_start));
    }

public:
    std::string text;
    std::vector<std::string> words;
    std::vector<const Texture*> textures;
    std::vector<SSBOVertex> vertices;
    ZreFont* font = nullptr;
    unsigned int size = 30;
    bool needRefreshVertices = true;
    glm::vec2 textBoxSize;
    glm::vec4 color;
    glm::vec2 origin;
    TextAlignementType alignement;

public:
    UIAnchor anchor;
};

class Text {
public:
    Text(const std::string& newText, ZreFont& newFont, unsigned int newSize, const glm::vec2& newOrigin, const glm::vec2& newTextBoxSize, const TextAlignementType newAlignement, const glm::vec4& newColor = glm::vec4(242, 214, 136, 255)):
        text(newText),
        font(&newFont),
        size(newSize),
        textBoxSize(newTextBoxSize),
        color(newColor),
        origin(newOrigin),
        alignement(newAlignement) {
        needRefreshVertices = true;
    }

public:
    void setFont(ZreFont& newFont) {
        font = &newFont;
        needRefreshVertices = true;
    }

    void setString(const std::string& newText) {
        text = newText;
        needRefreshVertices = true;
    }

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

public:
    void updateVertices() {
        if (alignement == TextAlignementType::ALIGN_CENTER) {
            updateVerticesCenter();
        } else if (alignement == TextAlignementType::ALIGN_RIGHT) {
            updateVerticesAlignRight();
        } else {
            updateVerticesAlignLeft();
        }
    }

private:
    void updateVerticesAlignLeft() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float x = 0;
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    x = 0;
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = 0;
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void updateVerticesCenter() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float lineX = 0;

            std::vector<std::size_t> lineAdjusts;
            for (const auto& word: words) {
                auto futurX = lineX;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    lineAdjusts.push_back((textBoxSize.x - lineX) / 2);
                    lineX = futurX - lineX;
                } else {
                    lineX = futurX;
                    const auto& spaceGlyph = font->getGlyph(' ', size);
                    lineX += (spaceGlyph.advance >> 6);
                }
            }

            lineAdjusts.push_back((textBoxSize.x - lineX) / 2);

            std::size_t nLine = 0;

            float x = lineAdjusts[nLine];
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    nLine++;
                    x = lineAdjusts[nLine];
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = lineAdjusts[nLine];
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void updateVerticesAlignRight() {
        if (needRefreshVertices) {
            splitText();
            vertices.clear();
            textures.clear();

            float lineX = 0;

            std::vector<std::size_t> lineAdjusts;
            for (const auto& word: words) {
                auto futurX = lineX;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    lineAdjusts.push_back((textBoxSize.x - lineX));
                    lineX = futurX - lineX;
                } else {
                    lineX = futurX;
                    const auto& spaceGlyph = font->getGlyph(' ', size);
                    lineX += (spaceGlyph.advance >> 6);
                }
            }

            lineAdjusts.push_back((textBoxSize.x - lineX));

            std::size_t nLine = 0;

            float x = lineAdjusts[nLine];
            float y = 0;

            for (const auto& word: words) {
                auto futurX = x;
                for (auto& c: word) {
                    const auto& glyph = font->getGlyph(c, size);
                    futurX += (glyph.advance >> 6);
                }

                if (futurX >= textBoxSize.x) {
                    nLine++;
                    x = lineAdjusts[nLine];
                    y = y + size;
                }

                for (auto& c: word) {
                    if (c == '\n') {
                        x = lineAdjusts[nLine];
                        y = y + size;
                        continue;
                    }

                    const auto& glyph = font->getGlyph(c, size);

                    float posX = x + glyph.bearing.x;
                    float posY = y - glyph.bearing.y + size;

                    float w = glyph.size.x;
                    float h = glyph.size.y;

                    textures.emplace_back(
                        glyph.texture
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, ((1 - origin.y) * h) + (posY)),
                        glm::vec2(0.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2((-origin.x * w) + posX, (-origin.y * h) + posY),
                        glm::vec2(0.0f, 0.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), ((1 - origin.y) * h) + (posY)),
                        glm::vec2(1.0f, 1.0f)
                    );

                    vertices.emplace_back(
                        glm::vec2(((1 - origin.x) * w) + (posX), (-origin.y * h) + posY),
                        glm::vec2(1.0f, 0.0f)
                    );

                    x += (glyph.advance >> 6);
                }
                const auto& spaceGlyph = font->getGlyph(' ', size);
                x += (spaceGlyph.advance >> 6);
            }

            needRefreshVertices = false;
        }
    }

    void splitText() noexcept {
        std::string delimiter = " ";
        std::string token;
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        words.clear();

        while ((pos_end = text.find(delimiter, pos_start)) != std::string::npos) {
            token = text.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            words.push_back(token);
        }

        words.push_back(text.substr(pos_start));
    }

public:
    std::string text;
    std::vector<std::string> words;
    std::vector<const Texture*> textures;
    std::vector<SSBOVertex> vertices;
    ZreFont* font = nullptr;
    unsigned int size = 30;
    bool needRefreshVertices = true;
    glm::vec2 textBoxSize;
    glm::vec4 color;
    glm::vec2 origin;
    TextAlignementType alignement;
};

///////////////////////////////////////////////////////////////////////////////////

class TextUICreator {
public:
    TextUICreator(const std::string& newStr, const std::string& newFilename, unsigned int newSize, const UIAnchor newAnchor, const glm::vec2& newTextBoxSize, const glm::vec4& newColor, const glm::vec2& newOrigin, const TextAlignementType newAlignement):
        str(newStr),
        filename(newFilename),
        size(newSize),
        textBoxSize(newTextBoxSize),
        color(newColor),
        anchor(newAnchor),
        origin(newOrigin),
        alignement(newAlignement) {
    }

public:
    std::string str;
    std::string filename;
    unsigned int size;
    glm::vec2 textBoxSize;
    glm::vec4 color;
    UIAnchor anchor;
    glm::vec2 origin;
    TextAlignementType alignement;
};

void textUICreatorSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [fontManager] = world.resource<FontManager>();
    for (auto [entUI, creator]: world.view<const TextUICreator>()) {
        world.add(entUI, TextUI(creator.str, fontManager.get(creator.filename), creator.size, creator.origin, creator.anchor, creator.textBoxSize, creator.alignement, creator.color));
        world.del<TextUICreator>(entUI);
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////

class TextCreator {
public:
    TextCreator(const std::string& newStr, const std::string& newFilename, unsigned int newSize, const glm::vec2& newTextBoxSize, const glm::vec4& newColor, const glm::vec2& newOrigin, const TextAlignementType newAlignement):
        str(newStr),
        filename(newFilename),
        size(newSize),
        textBoxSize(newTextBoxSize),
        color(newColor),
        origin(newOrigin),
        alignement(newAlignement) {
    }

public:
    std::string str;
    std::string filename;
    unsigned int size;
    glm::vec2 textBoxSize;
    glm::vec4 color;
    glm::vec2 origin;
    TextAlignementType alignement;
};

void textCreatorSys(LateFixedSystem, World& world) {
#ifdef ZER_DEBUG_INTEGRITY
    try {
#endif
    auto [fontManager] = world.resource<FontManager>();
    for (auto [ent, creator]: world.view<const TextCreator>()) {
        world.add(ent, Text(creator.str, fontManager.get(creator.filename), creator.size, creator.origin, creator.textBoxSize, creator.alignement, creator.color));
        world.del<TextCreator>(ent);
    }
#ifdef ZER_DEBUG_INTEGRITY
    } catch(const std::exception& except) {
        printf("%s: %s\n", __func__, except.what());
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////////
