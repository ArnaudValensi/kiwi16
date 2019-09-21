#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH 249
#define SCREEN_HEIGHT 136
#define SCREEN_SIZE SCREEN_WIDTH * SCREEN_HEIGHT

uint32_t COLORS[] = {
  0x1a1c2cff,
  0x5d275dff,
  0xb13e53ff,
  0xef7d57ff,
  0xffcd75ff,
  0xa7f070ff,
  0x38b764ff,
  0x257179ff,
  0x29366fff,
  0x3b5dc9ff,
  0x41a6f6ff,
  0x73eff7ff,
  0xf4f4f4ff,
  0x94b0c2ff,
  0x566c86ff,
  0x333c57ff,
};

typedef struct _Core {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t pixels[SCREEN_SIZE];
} Core;

int core_run(void (*on_update)(uint32_t *)) {
  Core core;

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  core.window = SDL_CreateWindow("My application",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      0);

  if(!core.window) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return 1;
  }

  core.renderer = SDL_CreateRenderer(core.window, -1, 0);

  if(!core.renderer) {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    return 1;
  }

  core.texture = SDL_CreateTexture(
      core.renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STATIC,
      SCREEN_WIDTH, 
      SCREEN_HEIGHT);

  if(!core.texture) {
    fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    return 1;
  }

  memset(core.pixels, 255, SCREEN_SIZE * sizeof(uint32_t));

  SDL_Event e;
  bool quit = false;
  while (!quit){
    on_update(core.pixels);

    SDL_UpdateTexture(core.texture, NULL, core.pixels, SCREEN_WIDTH * sizeof(uint32_t));

    while (SDL_PollEvent(&e)){
      if (e.type == SDL_QUIT){
        quit = true;
      }
      if (e.type == SDL_KEYDOWN){
        quit = true;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN){
        quit = true;
      }
    }

    if (SDL_RenderClear(core.renderer) != 0) {
      fprintf(stderr, "SDL_RenderClear failed: %s\n", SDL_GetError());
      return 1;
    }

    if (SDL_RenderCopy(core.renderer, core.texture, NULL, NULL) != 0) {
      fprintf(stderr, "SDL_RenderCopy failed: %s\n", SDL_GetError());
      return 1;
    }

    SDL_RenderPresent(core.renderer);
  }

  SDL_DestroyTexture(core.texture);
  SDL_DestroyRenderer(core.renderer);
  SDL_DestroyWindow(core.window);
  SDL_Quit();

  return 0;
}

void set_pixel(uint32_t *pixels, int x, int y, int color) {
  pixels[y * SCREEN_WIDTH + x] = COLORS[color];
}

void update(uint32_t *pixels) {
  set_pixel(pixels, 10, 20, 1);
}

int main()
{
  return core_run(update);
}

