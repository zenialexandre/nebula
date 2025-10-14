#include "Mouse.hpp"

namespace nebula {
    namespace mouse {

static std::unordered_map<std::string, int> stringSDLButtonMap = {
    {"left", SDL_BUTTON_LEFT}, {"middle", SDL_BUTTON_MIDDLE}, {"right", SDL_BUTTON_RIGHT}, {"x1", SDL_BUTTON_X1}, {"x2", SDL_BUTTON_X1},
    {"lmb", SDL_BUTTON_LEFT},  {"mmb", SDL_BUTTON_MIDDLE},    {"rmb", SDL_BUTTON_RIGHT}
};

Mouse::Mouse()
        : Module(MOUSE, "mouse") { };

void Mouse::getPosition(float &x, float &y) const {
    SDL_GetMouseState(&x, &y);
}

void Mouse::setPosition(float x, float y) {
    window::Window *windowInstance = ModuleRegistry::getInstance<window::Window>(WINDOW);

    if (windowInstance) {
        SDL_WarpMouseInWindow(windowInstance->getSDLWindow(), x, y);

        SDL_PumpEvents();
    }
}

bool Mouse::isPressed(const std::string &button) const {
    if (stringSDLButtonMap.count(button) == 0) {
        return false;
    }

    auto mouseState = SDL_GetMouseState(nullptr, nullptr);

    return mouseState && SDL_BUTTON_MASK(stringSDLButtonMap.at(button));
}

bool Mouse::isGrabbed() const {
    window::Window *windowInstance = ModuleRegistry::getInstance<window::Window>(WINDOW);
    if (!windowInstance) {
        return false;
    }
    return SDL_GetMouseFocus() && SDL_GetWindowMouseGrab(windowInstance->getSDLWindow());
}

void Mouse::setGrabbed(const bool grabbed) {
    window::Window *windowInstance = ModuleRegistry::getInstance<window::Window>(WINDOW);
    if (windowInstance) {
        SDL_SetWindowMouseGrab(windowInstance->getSDLWindow(), grabbed);
    }
}

} // mouse
} // nebula
