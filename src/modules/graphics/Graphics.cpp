#include "Graphics.h"

namespace nebula {
    namespace graphics {

static const char vertexShaderCode[] =
#include "../../../resources/shaders/vertexShader.glsl"
;

static const char fragShaderCode[] =
#include "../../../resources/shaders/fragShader.glsl"
;

Graphics::Graphics(int width, int height)
            : Module(GRAPHICS, "graphics")
            , defaultShader(nullptr)
            , defaultCamera(nullptr)
            , renderer(nullptr)
            , width(width)
            , height(height) {
}

Graphics::~Graphics() {
    std::cout << "DELETE GRAPHICS" << "\n";
    delete renderer;
    delete defaultCamera;
    delete defaultShader;
    for (const auto& pair : textures) {
        delete pair.second;
    }
}

bool Graphics::initialize() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        return false;
    }
    defaultShader = new Shader(vertexShaderCode, fragShaderCode);
    if (!defaultShader->getId()) {
        return false;
    }

    glEnable(GL_TEXTURE_2D);

    //glEnable(GL_MULTISAMPLE);

    defaultCamera = new Camera(width, height);
    renderer = new Renderer();
    renderer->init();

    //this->getGLVersionInfo();
    //this->getVertexShaderInfo();

    return true;
}

void Graphics::beginScene(ecs::World* world) {
    glViewport(0, 0, width, height);

    // (state-setting function)
    glClearColor(bgColorR, bgColorG, bgColorB, bgColorA);
    // (state-using function) fills the color buffer with the color configured by glClearColor
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    renderer->begin(world, defaultCamera, defaultShader);
}

void Graphics::endScene() {
    renderer->end();
}

Texture* Graphics::newSprite(std::string path) {
    if (textures.count(path) != 0) {
        return textures.at(path);
    }
    Texture* tex = new Texture(path.c_str());
    textures.insert({path, tex});
    return tex;
}

void Graphics::setWindowSize(int width, int height) {
    this->width = width;
    this->height = height;
    this->defaultCamera->setSize(width, height);
}

void Graphics::setBackground(float r, float g, float b, float a) {
    this->bgColorR = r;
    this->bgColorG = g;
    this->bgColorB = b;
    this->bgColorA = a;
}

void Graphics::getGLVersionInfo() {
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

void Graphics::getVertexShaderInfo() {
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported:" << nrAttributes << "\n";
}

void Graphics::draw(ecs::EntityId entity) {
    renderer->drawEntity(entity);
}

}// graphics
}// nebula
