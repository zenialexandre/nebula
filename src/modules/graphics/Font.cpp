#include "Font.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

namespace nebula {
    namespace graphics {

Font::Font() : lineHeight(0) { }

Font::~Font() {
    for (auto& pair : characters) {
        delete pair.second.texture;
    }
}

bool Font::load(const std::string& path, uint32_t fontSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::GRAPHICS::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        std::cout << "ERROR::GRAPHICS::FREETYPE: Failed to load font" << std::endl;
        FT_Done_FreeType(ft);
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::GRAPHICS::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        Texture* texture = new Texture();
        texture->width = face->glyph->bitmap.width;
        texture->height = face->glyph->bitmap.rows;
        
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<uint32_t>(face->glyph->advance.x)
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    lineHeight = face->size->metrics.height >> 6;
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

const Character &Font::getCharacter(char c) const {
    static Character defaultChar;
    auto it = characters.find(c);
    if (it != characters.end()) {
        return it->second;
    }
    return defaultChar;
}

float Font::getLineHeight() const {
    return lineHeight;
}

} // graphics
} // nebula
