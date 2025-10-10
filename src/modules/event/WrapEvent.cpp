#include "WrapEvent.hpp"

namespace nebula {

#define event() (ModuleRegistry::getInstance<event::Event>(EVENT))

    namespace event {

int w_poll(lua_State *L) {
    NebulaEvent *eventPointer = event()->poll();

    if (eventPointer != nullptr) {
        lua_pushstring(L, eventPointer->name.c_str());
        return 1;
    }

    return 0;
}

static const luaL_Reg functions[] = {
    {"poll", w_poll},
    {0, 0}
};

extern "C" int nlua_event(lua_State *L) {
    Event *event = event();

    WrapModule wModule;
    wModule.module = event;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // event
} // nebula
