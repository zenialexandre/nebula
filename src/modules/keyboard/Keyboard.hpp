#pragma once

#include "../common/Module.hpp"

#include <SDL3/SDL.h>

#include <unordered_map>
#include <string>

namespace nebula {
    namespace keyboard {

enum class Key {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    ESCAPE, ENTER, SPACE, BACKSPACE, TAB,
    LCTRL, RCTRL, LALT, RALT, LSHIFT, RSHIFT,
    LEFT, RIGHT, UP, DOWN,
    UNKNOWN
};

class Keyboard : public Module {
public:
    Keyboard();

    bool isKeyPressed(const std::string &keyName);
    bool isKeyReleased(const std::string &keyName);

    void resetKeysReleased();
    void pushKeyReleased(SDL_Scancode key);
private:
    bool keysReleased[SDL_SCANCODE_COUNT];
    SDL_Scancode keyToScancode(Key key);
};

} // keyboard
} // nebula
