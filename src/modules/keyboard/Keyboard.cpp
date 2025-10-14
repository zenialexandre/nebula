#include "Keyboard.hpp"

namespace nebula {
    namespace keyboard {

static std::unordered_map<std::string, Key> stringKeyMap = {
    {"a", Key::A}, {"b", Key::B}, {"c", Key::C}, {"d", Key::D}, {"e", Key::E},
    {"f", Key::F}, {"g", Key::G}, {"h", Key::H}, {"i", Key::I}, {"j", Key::J},
    {"k", Key::K}, {"l", Key::L}, {"m", Key::M}, {"n", Key::N}, {"o", Key::O},
    {"p", Key::P}, {"q", Key::Q}, {"r", Key::R}, {"s", Key::S}, {"t", Key::T},
    {"u", Key::U}, {"v", Key::V}, {"w", Key::W}, {"x", Key::X}, {"y", Key::Y},
    {"z", Key::Z},

    {"0", Key::NUM_0}, {"1", Key::NUM_1}, {"2", Key::NUM_2}, {"3", Key::NUM_3},
    {"4", Key::NUM_4}, {"5", Key::NUM_5}, {"6", Key::NUM_6}, {"7", Key::NUM_7},
    {"8", Key::NUM_8}, {"9", Key::NUM_9},

    {"f1", Key::F1}, {"f2", Key::F2}, {"f3", Key::F3}, {"f4", Key::F4},
    {"f5", Key::F5}, {"f6", Key::F6}, {"f7", Key::F7}, {"f8", Key::F8},
    {"f9", Key::F9}, {"f10", Key::F10}, {"f11", Key::F11}, {"f12", Key::F12},

    {"escape", Key::ESCAPE}, {"enter", Key::ENTER}, {"space", Key::SPACE},
    {"backspace", Key::BACKSPACE}, {"tab", Key::TAB},

    {"lctrl", Key::LCTRL}, {"rctrl", Key::RCTRL}, {"lalt", Key::LALT},
    {"ralt", Key::RALT}, {"lshift", Key::LSHIFT}, {"rshift", Key::RSHIFT},

    {"left", Key::LEFT}, {"right", Key::RIGHT}, {"up", Key::UP}, {"down", Key::DOWN}
};

Keyboard::Keyboard()
        : Module(KEYBOARD, "keyboard") { };

bool Keyboard::isKeyPressed(const std::string &keyName) {
    if (stringKeyMap.count(keyName) == 0) {
        return false;
    }
    Key key = stringKeyMap.at(keyName);
    
    const bool *keyboardState = SDL_GetKeyboardState(NULL);
    SDL_Scancode scancode = keyToScancode(key);
    return keyboardState[scancode]; 
};

SDL_Scancode Keyboard::keyToScancode(Key key) {
    switch (key) {
        case Key::A: return SDL_SCANCODE_A;
        case Key::B: return SDL_SCANCODE_B;
        case Key::C: return SDL_SCANCODE_C;
        case Key::D: return SDL_SCANCODE_D;
        case Key::E: return SDL_SCANCODE_E;
        case Key::F: return SDL_SCANCODE_F;
        case Key::G: return SDL_SCANCODE_G;
        case Key::H: return SDL_SCANCODE_H;
        case Key::I: return SDL_SCANCODE_I;
        case Key::J: return SDL_SCANCODE_J;
        case Key::K: return SDL_SCANCODE_K;
        case Key::L: return SDL_SCANCODE_L;
        case Key::M: return SDL_SCANCODE_M;
        case Key::N: return SDL_SCANCODE_N;
        case Key::O: return SDL_SCANCODE_O;
        case Key::P: return SDL_SCANCODE_P;
        case Key::Q: return SDL_SCANCODE_Q;
        case Key::R: return SDL_SCANCODE_R;
        case Key::S: return SDL_SCANCODE_S;
        case Key::T: return SDL_SCANCODE_T;
        case Key::U: return SDL_SCANCODE_U;
        case Key::V: return SDL_SCANCODE_V;
        case Key::W: return SDL_SCANCODE_W;
        case Key::X: return SDL_SCANCODE_X;
        case Key::Y: return SDL_SCANCODE_Y;
        case Key::Z: return SDL_SCANCODE_Z;
        
        case Key::NUM_0: return SDL_SCANCODE_0;
        case Key::NUM_1: return SDL_SCANCODE_1;
        case Key::NUM_2: return SDL_SCANCODE_2;
        case Key::NUM_3: return SDL_SCANCODE_3;
        case Key::NUM_4: return SDL_SCANCODE_4;
        case Key::NUM_5: return SDL_SCANCODE_5;
        case Key::NUM_6: return SDL_SCANCODE_6;
        case Key::NUM_7: return SDL_SCANCODE_7;
        case Key::NUM_8: return SDL_SCANCODE_8;
        case Key::NUM_9: return SDL_SCANCODE_9;
        
        case Key::F1: return SDL_SCANCODE_F1;
        case Key::F2: return SDL_SCANCODE_F2;
        case Key::F3: return SDL_SCANCODE_F3;
        case Key::F4: return SDL_SCANCODE_F4;
        case Key::F5: return SDL_SCANCODE_F5;
        case Key::F6: return SDL_SCANCODE_F6;
        case Key::F7: return SDL_SCANCODE_F7;
        case Key::F8: return SDL_SCANCODE_F8;
        case Key::F9: return SDL_SCANCODE_F9;
        case Key::F10: return SDL_SCANCODE_F10;
        case Key::F11: return SDL_SCANCODE_F11;
        case Key::F12: return SDL_SCANCODE_F12;
        
        case Key::ESCAPE: return SDL_SCANCODE_ESCAPE;
        case Key::ENTER: return SDL_SCANCODE_RETURN;
        case Key::SPACE: return SDL_SCANCODE_SPACE;
        case Key::BACKSPACE: return SDL_SCANCODE_BACKSPACE;
        case Key::TAB: return SDL_SCANCODE_TAB;
        
        case Key::LCTRL: return SDL_SCANCODE_LCTRL;
        case Key::RCTRL: return SDL_SCANCODE_RCTRL;
        case Key::LALT: return SDL_SCANCODE_LALT;
        case Key::RALT: return SDL_SCANCODE_RALT;
        case Key::LSHIFT: return SDL_SCANCODE_LSHIFT;
        case Key::RSHIFT: return SDL_SCANCODE_RSHIFT;
        
        case Key::LEFT: return SDL_SCANCODE_LEFT;
        case Key::RIGHT: return SDL_SCANCODE_RIGHT;
        case Key::UP: return SDL_SCANCODE_UP;
        case Key::DOWN: return SDL_SCANCODE_DOWN;
        
        default: return SDL_SCANCODE_UNKNOWN;
    }
};

} // keyboard
} // nebula 
