#include "WrapTexture.hpp"

namespace nebula {
    namespace graphics {

    extern "C" int nlua_graphics_texture(lua_State *L) {
        WrapType wrapTexture;
        wrapTexture.name = "Texture";
        wrapTexture.funcs = nullptr;
        wrapTexture.fields = nullptr;

        return registerType(L, wrapTexture);
    }
} // graphics
} // nebula
