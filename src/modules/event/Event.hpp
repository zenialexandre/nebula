#pragma once

#include <SDL3/SDL.h>

#include "../common/Module.hpp"
#include "../keyboard/Keyboard.hpp"

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
};

} // event
} // nebula
