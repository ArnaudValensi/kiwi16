#include "lua.h"
#include "api.h"
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
#include <stdbool.h>

static lua_State *L;
static bool isInit = false;

static int LuaSetPixel(lua_State *L) {
    int x = lua_tointeger(L, 1);
    int y = (int)lua_tointeger(L, 2);
    int color = (int)lua_tointeger(L, 3);

    ApiSetPixel(x, y, color);

    return 0;
}

void LuaInit() {
    L = luaL_newstate();

    // Opens the standard libraries.
    luaL_openlibs(L);

    lua_register(L, "setpixel", LuaSetPixel);

    if (luaL_dofile(L, "start.lua")) {
        // Display the error on top of the stack.
        fprintf(stderr, "[C - Lua loader] %s\n", lua_tostring(L, -1));

        // Pop error message from the stack.
        lua_pop(L, 1);
    }

    isInit = true;
}

void LuaCallScriptUpdate() {
    if (!isInit) {
        LuaInit();
    }

    lua_getglobal(L, "update");

    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 0, 0)) {
            fprintf(stderr, "[C - call 'update()'] %s\n", lua_tostring(L, -1));

            // Pop error message from the stack.
            lua_pop(L, 1);
        }
    } else {
        fprintf(stderr, "[C] 'update()' does not exist\n");
    }
}

void LuaClean() {
    if (!isInit) {
        return;
    }

    lua_close(L);
    L = NULL;
    isInit = false;
}
