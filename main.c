#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "graphics.h"
#include "config.h"

float t = 0;
void draw()
{
  t += 0.02;

  for (int i = 0; i < 1000; i++)
  {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;
    int c = (int)(x / 16.0 + y / 32.0 + t) % 6 + 11;

    graphics_set_pixel(x, y, c);
  }
}

int main()
{
  SDL_Event e;
  bool quit = false;

  if (graphics_init())
  {
    return 1;
  }

  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    draw();

    if (graphics_draw())
    {
      return 1;
    }
  }

  graphics_clean();

  return 0;
}
