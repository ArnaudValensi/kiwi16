#include "config.h"
#include <SDL2/SDL.h>

typedef struct state_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint32_t pixels[SCREEN_SIZE];
} state_t;

static state_t state;

int RendererInit() {
    uint32_t next_time;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    state.window = SDL_CreateWindow("My application",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH * SCREEN_SCALE,
                                    SCREEN_HEIGHT * SCREEN_SCALE,
                                    SDL_WINDOW_OPENGL);

    if (!state.window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    if (!state.renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return 1;
    }

    state.texture = SDL_CreateTexture(state.renderer,
                                      SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_STATIC,
                                      SCREEN_WIDTH,
                                      SCREEN_HEIGHT);

    if (!state.texture) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        return 1;
    }

    memset(state.pixels, 255, SCREEN_SIZE * sizeof(uint32_t));

    return 0;
}

int RendererDraw() {
    SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * sizeof(uint32_t));

    if (SDL_RenderClear(state.renderer) != 0) {
        fprintf(stderr, "SDL_RenderClear failed: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_RenderCopy(state.renderer, state.texture, NULL, NULL) != 0) {
        fprintf(stderr, "SDL_RenderCopy failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_RenderPresent(state.renderer);

    return 0;
}

void RendererClean() {
    SDL_DestroyTexture(state.texture);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void RendererSetPixel(int x, int y, int color) {
    state.pixels[y * SCREEN_WIDTH + x] = COLORS[color];
}
