#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>

int LuaSetPixel(lua_State *L) {
    int x = lua_tointeger(L, 1);
    int y = (int)lua_tointeger(L, 2);
    int color = (int)lua_tointeger(L, 3);

    printf("[C] LuaSetPixel, x: %d, y: %d, color: %d\n", x, y, color);
    return 0;
}

void LuaRun() {
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();

    // Opens the standard libraries.
    luaL_openlibs(L);

    lua_register(L, "setpixel", LuaSetPixel);

    if (luaL_dofile(L, "main.lua")) {
        fprintf(stderr, "[Lua loader] %s\n", lua_tostring(L, -1));

        // Pop error message from the stack.
        lua_pop(L, 1);
    }

    lua_close(L);
}
