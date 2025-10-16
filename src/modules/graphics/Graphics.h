#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "../Ecs/World.hpp"
#include "../Common/Module.hpp"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"
#include "Font.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

namespace nebula {
    namespace graphics {

class Graphics : public Module {
public:
    Graphics(int width, int height);
    ~Graphics();
    bool initialize();

    void moveCamera(float x, float y);
    void moveCameraTo(float x, float y);
    void pointCameraTo(float x, float y);

    void beginScene(ecs::World* world);
    void endScene();
    void draw(ecs::EntityId entity);

    Texture *newTexture(std::string path);
    Font *newFont(std::string path, uint32_t size = 12);

    void onWindowSizeChange(int width, int height);
    void setBackground(float r, float g, float b, float a  = 1.0f);

private:
    Shader* defaultShader;
    Camera* defaultCamera;
    Renderer* renderer;

    int width, height;
    float bgColorR = 0.0f, bgColorG = 0.0f, bgColorB = 0.0f, bgColorA = 1.0f;
    
    void getGLVersionInfo();
    void getVertexShaderInfo();
    
    std::unordered_map<std::string, Texture*> textures;
}; 

}// graphics
}// nebula