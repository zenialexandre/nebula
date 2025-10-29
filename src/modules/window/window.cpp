#include "Window.h"

namespace nebula {
    namespace window {

Window::Window()
        : Module(WINDOW, "window")
        , title("nebula")
        , window(nullptr)
        , glContext(nullptr) {
    
    if(!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
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
}

void Window::close() {
    SDL_Log("%s", "CLOSE::WINDOW");
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_FlushEvents(SDL_EVENT_WINDOW_FIRST, SDL_EVENT_WINDOW_LAST);
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
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
    centerScreen();
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

void Window::setFullscreen(const bool fullscreen, const bool desktopMode) {
    if (fullscreen) {
        if (desktopMode) {
            SDL_SetWindowFullscreenMode(this->window, nullptr);
        } else {
            SDL_DisplayID displayId = SDL_GetDisplayForWindow(this->window);
            SDL_DisplayMode displayMode {};

            SDL_DisplayMode currDisplayMode = *SDL_GetCurrentDisplayMode(displayId);
            this->originalDisplayMode = &currDisplayMode;
            
            if(SDL_GetClosestFullscreenDisplayMode(displayId, width, height, 0.0f, false, &displayMode)) {
                SDL_SetWindowFullscreenMode(this->window, &displayMode);
            }
        }
    } else {
        if (!desktopMode) {
            SDL_SetWindowFullscreenMode(this->window, this->originalDisplayMode);
        }
    }
    if (SDL_SetWindowFullscreen(this->window, fullscreen)) {
        SDL_GL_MakeCurrent(this->window, this->glContext);
    }
}

void Window::setSize(int width, int height) {
    SDL_SetWindowSize(this->window, width, height);
    centerScreen();
}

void Window::setResizable(const bool resizable) {
    SDL_SetWindowResizable(this->window, resizable);
}

void Window::setBorderless(const bool borderless) {
    SDL_SetWindowBordered(this->window, !borderless);
}

// SDL Documentation:
// 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync.
void Window::setVsync(int vsync) {
    SDL_GL_SetSwapInterval(vsync);
}

void Window::onSizeChange() {
    SDL_GetWindowSize(this->window, &this->width, &this->height);
}

void Window::centerScreen() {
    SDL_DisplayID displayId = SDL_GetDisplayForWindow(this->window);
    auto center = SDL_WINDOWPOS_CENTERED_DISPLAY(displayId);
    SDL_SetWindowPosition(window, center, center);
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