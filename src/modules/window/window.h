#pragma once

#include "../Common/Module.hpp"

#include "data/ImageFile.h"

#include <string>
#include <SDL3/SDL.h>

namespace nebula {

namespace window {

struct WindowSettings {
    std::string title   = "nebula";
    std::string icon    = "";
    bool fullscreen     = false;
    bool resizable      = false;
    bool borderless     = false;
    bool centered       = true;
    int vsync           = 1;
    int x               = 0;
    int y               = 0;
    //int display         = 0;
    int fpsCap          = 0;
};

class Window : public Module {
public:
    Window();
    ~Window();

    bool createWindow(int width = 800, int height = 600);
    void setWindow(int width = 800, int height = 600, WindowSettings *ws = nullptr);

    void close();

    void setTitle(std::string &title);
    bool setIcon(std::string &iconPath);
    void setFullscreen(const bool fullscreen, const bool desktopMode = false);
    void setSize(int width, int height);

    int getWidth();
    int getHeight();

    void swapBuffers();

    SDL_Window *getSDLWindow() const;

private:
    void setGLContextAttributes();
    void setGLBufferAttributes();

    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_DisplayMode originalDisplayMode;

    int width = 800;
    int height = 600;
    std::string title;
};

}
}