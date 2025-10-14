#pragma once

#include <string>

#include "../Graphics/Texture.h"
#include "../Graphics/Font.hpp"

// Built in component
struct Position {
    float x, y;
};

// Built in component
struct Scale {
    float x, y;
};

// Built in component
struct Quad {
    float width, height;
};

// Built in component
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

// Built in component
// TODO Color component
// struct Color { 
// };