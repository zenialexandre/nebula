#include "Event.hpp"

namespace nebula {
    namespace event {

NebulaEvent::NebulaEvent(std::string name) : name(name) { }

Event::Event() : Module(EVENT, "event") { }

NebulaEvent *Event::poll() {
    SDL_Event sdlEvent{0};
    while(SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            // handle other events here
            case SDL_EVENT_KEY_UP: {
                keyboard::Keyboard *keyboard = ModuleRegistry::getInstance<keyboard::Keyboard>(KEYBOARD);
                keyboard->pushKeyReleased(sdlEvent.key.scancode);
                return new NebulaEvent("keyReleased");
            }
            case SDL_EVENT_QUIT: {
                return new NebulaEvent("quit");
            }
        }
    }
    return nullptr;
}

} // event
} // nebula
