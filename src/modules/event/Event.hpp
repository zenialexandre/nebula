#pragma once

#include <SDL3/SDL.h>

#include "../common/Module.hpp"
#include "../keyboard/Keyboard.hpp"
#include "../graphics/Graphics.h"
#include "../window/Window.h"

#include <string>

namespace nebula {
    namespace event {
        
struct NebulaEvent {
    std::string name;

    NebulaEvent(std::string name);
};

class Event: public Module {
public:
    Event();
    NebulaEvent *poll();
    void quit();
};

} // event
} // nebula
