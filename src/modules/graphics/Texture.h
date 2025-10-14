#pragma once

#include <glad/glad.h>

#include "data/ImageFile.h"

#include <iostream>

namespace nebula {
    namespace graphics {

class Texture {
public:
    Texture();
    Texture(const char* texturePath);
    ~Texture();

    int width, height;

    void bind();

    int getId();

    unsigned int id;
};

}// graphics
}// nebula
