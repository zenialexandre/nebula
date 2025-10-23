#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "../Ecs/World.hpp"
#include "../Ecs/Components.hpp"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

namespace nebula {
    namespace graphics {

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float texIndex;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init();
    void begin(ecs::World* world, Camera* camera, Shader* shader);
    void end();
    void flush();

    void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation, Texture* texture = nullptr);

    void drawText(const std::string& text, Font* font, const glm::vec2& position, const glm::vec4& color, const glm::vec2& scale, const float rotation);

    void drawEntity(ecs::EntityId entity);

private:
    bool setupBuffers();

    static const int MAX_QUADS = 10000;
    static const int MAX_VERTICES = MAX_QUADS * 4;
    static const int MAX_INDICES = MAX_QUADS * 6;
    static const int MAX_TEXTURE_SLOTS = 16;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    Vertex* vertices;
    uint32_t vertexCount;
    uint32_t indexCount;

    std::vector<Texture*> textures;
    std::array<uint32_t, MAX_TEXTURE_SLOTS> textureSlots;

    Shader* shader;

    ecs::World* world; // TODO remove this to use ModuleRegistry

    Camera* camera;
};
} // graphics
} // nebula
