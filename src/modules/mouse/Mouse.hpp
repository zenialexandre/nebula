#pragma once

#include "../common/Module.hpp"
#include "../window/Window.h"

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>

namespace nebula {
    namespace mouse {

class Mouse : public Module {
public:
    Mouse();

    void getPosition(float &x, float &y) const;

    void setPosition(float x, float y);

    bool isPressed(const std::string &button) const;

    bool isReleased(const std::string &button) const;

    bool isGrabbed() const;

    void setGrabbed(const bool grabbed);
};

} // mouse
} // nebula
