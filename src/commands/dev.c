#include "../config.h"
#include "../kiwios.h"
#include "../lua.h"
#include "../renderer.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

void WaitForNextTick() {
    static uint32_t nextTickTime = TICK_INTERVAL_IN_MS;

    uint32_t now = SDL_GetTicks();
    if (nextTickTime > now) {
        SDL_Delay(nextTickTime - now);
    }

    nextTickTime += TICK_INTERVAL_IN_MS;
}

int CommandDev() {
    SDL_Event event;
    bool quit = false;
    bool displayDevTools = false;
    bool wasDisplayingDevToolsLastFrame = false;

    if (RendererInit()) {
        return 1;
    }

    if (KiwiOsInit()) {
        return 1;
    }

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
                displayDevTools = !displayDevTools;
            }
        }

        if (displayDevTools) {
            if (!wasDisplayingDevToolsLastFrame) {
                LuaClean();
            }
            KiwiOsUpdate();
            wasDisplayingDevToolsLastFrame = true;
        } else {
            LuaCallScriptUpdate();
            wasDisplayingDevToolsLastFrame = false;
        }

        if (RendererDraw()) {
            return 1;
        }

        WaitForNextTick();
    }

    KiwiOsClean();
    LuaClean();
    RendererClean();

    return 0;
}
