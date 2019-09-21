#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("My application",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640, 480,
      0);

  if(!window) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  if(!renderer) {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Texture *texture = SDL_CreateTexture(
      renderer, 
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC,
      640, 
      480);

  if(!texture) {
    fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    return 1;
  }

  uint32_t *pixels = (uint32_t *)malloc(640 * 480 * sizeof(uint32_t));

  memset(pixels, 255, 640 * 480 * sizeof(uint32_t));

  SDL_Event e;
  bool quit = false;
  while (!quit){
    SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(uint32_t));

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

    if (SDL_RenderClear(renderer) != 0) {
      fprintf(stderr, "SDL_RenderClear failed: %s\n", SDL_GetError());
      return 1;
    }

    if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) {
      fprintf(stderr, "SDL_RenderCopy failed: %s\n", SDL_GetError());
      return 1;
    }

    SDL_RenderPresent(renderer);
  }

  free(pixels);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

