#pragma once

#include "Texture.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace nebula {
    namespace graphics {

struct Character {
    Texture *texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    uint32_t advance;
};

class Font {
public:
    Font();
    ~Font();

    bool load(const std::string &path, uint32_t fontSize);

    const Character &getCharacter(char c) const;

    float getLineHeight() const;
private:
    std::unordered_map<char, Character> characters;
    float lineHeight;
};

} // graphics
} // nebula
