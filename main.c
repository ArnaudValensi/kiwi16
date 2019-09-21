#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SIZE SCREEN_WIDTH * SCREEN_HEIGHT

typedef struct _Core {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t pixels[SCREEN_SIZE];
} Core;

int main()
{
  Core core;

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  core.window = SDL_CreateWindow("My application",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640, 480,
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
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC,
      640, 
      480);

  if(!core.texture) {
    fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    return 1;
  }

  memset(core.pixels, 255, SCREEN_SIZE * sizeof(uint32_t));

  SDL_Event e;
  bool quit = false;
  while (!quit){
    SDL_UpdateTexture(core.texture, NULL, core.pixels, 640 * sizeof(uint32_t));

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

