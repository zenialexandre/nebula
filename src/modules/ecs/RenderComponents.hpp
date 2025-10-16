#pragma once

#include <string>

#include "../Graphics/Texture.h"
#include "../Graphics/Font.hpp"

struct Position {
    float x, y;
};

struct Scale {
    float x, y;
};

struct Quad {
    float width, height;
};

struct Sprite {
    nebula::graphics::Texture* texture;
};

struct Text {
    nebula::graphics::Font *font;
    std::string value {};
};

struct Color {
    float r, g, b, a;
};

struct Rotation {
    float value;
};

struct CollisionBox {
    float width, height;
    float x, y;
};