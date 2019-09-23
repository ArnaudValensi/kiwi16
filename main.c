#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
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

#define TICK_INTERVAL 33

static Uint32 next_time;

uint32_t time_left()
{
  uint32_t now;

  now = SDL_GetTicks();
  if(next_time <= now)
    return 0;
  else
    return next_time - now;
}

typedef struct _Core {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t pixels[SCREEN_SIZE];
} Core;

int core_run(void (*on_update)(uint32_t *)) {
  Core core;
  uint32_t next_time;

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  core.window = SDL_CreateWindow("My application",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL);

  if(!core.window) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return 1;
  }

  core.renderer = SDL_CreateRenderer(core.window, -1, SDL_RENDERER_ACCELERATED);

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

  next_time = SDL_GetTicks() + TICK_INTERVAL;

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

    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
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

float t = 0;
void update(uint32_t *pixels) {
  t += 0.02;

  for (int i = 0; i < 1000; i++) {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;
    int c = (int)(x / 16.0 + y / 32.0 + t) % 6 + 11;

    set_pixel(pixels, x, y, c);
  }
}

int main()
{
  return core_run(update);
}
