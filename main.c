#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *screen = SDL_CreateWindow("My application",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640, 480,
      0);

  if(!screen) {
    fprintf(stderr, "Could not create window\n");
    return 1;
  }

  SDL_Event e;
  bool quit = false;
  while (!quit){
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
  }

  SDL_DestroyWindow(screen);
  SDL_Quit();
  return 0;
}

