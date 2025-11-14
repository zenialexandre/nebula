#pragma once

#include <glad/glad.h>

#include "data/ImageFile.h"

#include <iostream>
#include <unordered_map>

namespace nebula {
    namespace graphics {


enum TextureFilter {
    LINEAR = GL_LINEAR,
    NEAREST = GL_NEAREST,
    FILTER_UNKNOWN = 0
};

class Texture {
public:
    Texture();
    Texture(const char* texturePath, TextureFilter filter = LINEAR);
    ~Texture();

    int width, height;

    void bind();

    int getId();

    unsigned int id;
};

}// graphics
}// nebula
