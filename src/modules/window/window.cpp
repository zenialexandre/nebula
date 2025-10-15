#include "Window.h"

namespace nebula {
    namespace window {

Window::Window()
        : Module(WINDOW, "window")
        , title("nebula")
        , window(nullptr)
        , glContext(nullptr) {
    
    if(!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        //TODO: throw Exception
        SDL_Log("%s", "ERROR::SDL::INITIALIZE::VIDEO");
    }
}
Window::~Window() {
    close();
}

void Window::setWindow(int width, int height, WindowSettings *ws) {
    if (!ws) {
        return;
    }

    int num_displays = 0;
    SDL_DisplayID *display_ids = SDL_GetDisplays(&num_displays);
}

void Window::close() {
    SDL_Log("%s", "CLOSE::WINDOW");
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_FlushEvents(SDL_EVENT_WINDOW_FIRST, SDL_EVENT_WINDOW_LAST);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool Window::createWindow(int width, int height) {
    setGLContextAttributes();
    setGLBufferAttributes();
    window = SDL_CreateWindow(title.c_str(), 
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    if(!window) {
        //TODO: throw Exception
        SDL_Log("%s", "ERROR::SDL::WINDOW::CREATE");
        return false;
    }
    glContext = SDL_GL_CreateContext(window);
    if(!glContext) {
        //TODO: throw Exception
        SDL_Log("%s", "ERROR::SDL::WINDOW::CREATE_CONTEXT");
        return false;
    }
    this->width = width;
    this->height = height;
    return true;
}

void Window::setTitle(std::string &title) {
    SDL_SetWindowTitle(this->window, title.c_str());
}

bool Window::setIcon(std::string &iconPath) {
    int width {}, height {}, nrChannels {};
    unsigned char* data {};

    data::ImageFile* iconFile = new data::ImageFile(iconPath.c_str());
    iconFile->read(data, width, height, nrChannels, 4);

    SDL_Surface *surface = SDL_CreateSurfaceFrom(
        width,
        height,
        SDL_PIXELFORMAT_RGBA32,
        data,
        width * 4
    );

    if (!surface) {
        return false;
    }

    SDL_SetWindowIcon(this->window, surface);

    SDL_DestroySurface(surface);
    delete iconFile;
    return true;
}

void Window::setFullscreen(const bool fullscreen) {

}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

void Window::setGLContextAttributes() {
    // OpenGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // OpenGL Core Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void Window::setGLBufferAttributes() {
    // 8 bits to each channel RGBA8888
    // meaning 256 values for each channel (0 to 255)
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    // double buffer (back and front)
    // switch with SDL_GL_SwapWindow
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // if the framebuffer content is preserved when minimizing window
    SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 0);

    // z-buffer size (usually 24 bits)
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // stencil buffer size (8 bits)
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

SDL_Window *Window::getSDLWindow() const {
    return this->window;
}

} // window
} // nebula