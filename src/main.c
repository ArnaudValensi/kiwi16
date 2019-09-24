#include "config.h"
#include "lua.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

float t = 0;
void Draw() {
    t += 0.02;

    for (int i = 0; i < 1000; i++) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int c = (int)(x / 16.0 + y / 32.0 + t) % 6 + 11;

        RendererSetPixel(x, y, c);
    }
}

void WaitForNextTick() {
    static uint32_t nextTickTime = TICK_INTERVAL_IN_MS;

    uint32_t now = SDL_GetTicks();
    if (nextTickTime > now) {
        SDL_Delay(nextTickTime - now);
    }

    nextTickTime += TICK_INTERVAL_IN_MS;
}

int main() {
    SDL_Event event;
    bool quit = false;

    LuaRun();

    if (RendererInit()) {
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
        }

        Draw();

        if (RendererDraw()) {
            return 1;
        }

        WaitForNextTick();
    }

    RendererClean();

    return 0;
}
