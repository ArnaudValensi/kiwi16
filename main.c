#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "graphics.h"
#include "config.h"

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

// #define TICK_INTERVAL 33

// static Uint32 next_time;

// uint32_t time_left()
// {
//   uint32_t now;

//   now = SDL_GetTicks();
//   if (next_time <= now)
//     return 0;
//   else
//     return next_time - now;
// }

void set_pixel(uint32_t *pixels, int x, int y, int color)
{
  pixels[y * SCREEN_WIDTH + x] = COLORS[color];
}

float t = 0;
void update(uint32_t *pixels)
{
  t += 0.02;

  for (int i = 0; i < 1000; i++)
  {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;
    int c = (int)(x / 16.0 + y / 32.0 + t) % 6 + 11;

    set_pixel(pixels, x, y, c);
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

    if (graphics_update(update))
    {
      return 1;
    }
  }

  graphics_clean();

  return 0;
}
