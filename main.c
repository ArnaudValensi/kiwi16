#include "config.h"
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

int main() {
    SDL_Event e;
    bool quit = false;

    if (RendererInit()) {
        return 1;
    }

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        Draw();

        if (RendererDraw()) {
            return 1;
        }
    }

    RendererClean();

    return 0;
}
