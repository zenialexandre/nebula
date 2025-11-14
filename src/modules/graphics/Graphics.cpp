#include "Graphics.h"

namespace nebula {
    namespace graphics {

static const char vertexShaderCode[] =
#include "../../../resources/shaders/vertexShader.glsl"
;

static const char fragShaderCode[] =
#include "../../../resources/shaders/fragShader.glsl"
;

static std::unordered_map<std::string, TextureFilter> stringFilterMap = {
    {"nearest", NEAREST}, {"linear", LINEAR}
};

Graphics::Graphics(int width, int height)
            : Module(GRAPHICS, "graphics")
            , defaultShader(nullptr)
            , defaultCamera(nullptr)
            , renderer(nullptr)
            , width(width)
            , height(height) {
}

Graphics::~Graphics() {
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

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

Texture *Graphics::newTexture(std::string path, TextureFilter filter) {
    if (textures.count(path) != 0) {
        return textures.at(path);
    }
    Texture *tex = new Texture(path.c_str(), filter);
    textures.insert({path, tex});
    return tex;
}

Font *Graphics::newFont(std::string path, uint32_t size) {
    Font *font = new Font();
    font->load(path, size);
    return font;
}

void Graphics::onWindowSizeChange(int width, int height) {
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

void Graphics::moveCamera(float x, float y) {
    defaultCamera->moveCamera(x, y);
}

void Graphics::moveCameraTo(float x, float y) {
    defaultCamera->moveCameraTo(x, y);
}

void Graphics::pointCameraTo(float x, float y) {
    defaultCamera->pointCameraTo(x, y);
}

void Graphics::setDefaultFilter(TextureFilter filter) {
    this->defaultTextureFilter = filter;
}

TextureFilter Graphics::mapFilter(std::string filterName) {
    if (stringFilterMap.count(filterName) == 0) {
        return FILTER_UNKNOWN;
    }
    return stringFilterMap.at(filterName);
}

}// graphics
}// nebula
