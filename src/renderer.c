#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

typedef struct state_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *fontAtlas;
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

    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
        fprintf(stderr, "Warning: Cannot use nearest pixel sampling for texture scaling.\n");
    }

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    state.texture = SDL_CreateTexture(state.renderer,
                                      SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      SCREEN_WIDTH,
                                      SCREEN_HEIGHT);

    if (!state.texture) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        return 1;
    }

    memset(state.pixels, 255, SCREEN_SIZE * sizeof(uint32_t));

    // Load the font spritesheet.
    SDL_Surface *fontSurface = IMG_Load("./asset/font.png");

    if (!fontSurface) {
        fprintf(stderr, "IMG_Load failed: %s\n", IMG_GetError());
        return 1;
    }

    state.fontAtlas = SDL_ConvertSurfaceFormat(fontSurface, SDL_PIXELFORMAT_RGBA8888, 0);

    if (!state.fontAtlas) {
        fprintf(stderr, "SDL_ConvertSurfaceFormat failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_FreeSurface(fontSurface);

    return 0;
}

int RendererDraw() {
    SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * sizeof(uint32_t));

    if (SDL_RenderCopy(state.renderer, state.texture, NULL, NULL) != 0) {
        fprintf(stderr, "SDL_RenderCopy failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_RenderPresent(state.renderer);

    if (SDL_RenderClear(state.renderer) != 0) {
        fprintf(stderr, "SDL_RenderClear failed: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void RendererClean() {
    SDL_DestroyTexture(state.texture);
    SDL_FreeSurface(state.fontAtlas);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void RendererSetPixel(int x, int y, int color) {
    state.pixels[y * SCREEN_WIDTH + x] = COLORS[color];
}

void RendererSetPixelRect(int x, int y, int width, int height, int color) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            state.pixels[j * SCREEN_WIDTH + i] = COLORS[color];
        }
    }
}

static inline int GetSurfacePixelColor(int x, int y, SDL_Surface *surface) {
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;

    return *(Uint32 *)p;
}

static void CopyFromSurfaceToPixelBuffer(
    SDL_Surface *surface, SDL_Rect *source, int destStartX, int destStartY, int color) {
    int sourceStartX = source->x;
    int sourceStartY = source->y;
    int sourceEndX = source->x + source->w;
    int sourceEndY = source->y + source->h;
    int sourceWidth = surface->w;
    int sourceHeight = surface->h;

    int j = 0;
    int sourceY = sourceStartY;
    while (sourceY < sourceEndY && sourceY < sourceHeight) {

        int i = 0;
        int sourceX = sourceStartX;
        while (sourceX < sourceEndX && sourceX < sourceWidth) {
            uint32_t pixelColor = GetSurfacePixelColor(sourceX, sourceY, surface);

            int alpha = pixelColor & 0xff;

            if (alpha == 0xff) {
                int destX = destStartX + i;
                int destY = destStartY + j;

                if (destX < SCREEN_WIDTH && destY < SCREEN_HEIGHT) {
                    state.pixels[destY * SCREEN_WIDTH + destX] = COLORS[color];
                }
            }

            i++;
            sourceX = sourceStartX + i;
        }

        j++;
        sourceY = sourceStartY + j;
    }
}

void RendererDrawText(char *text, int x, int y, int color) {
    for (size_t i = 0; text[i] != '\0'; i++) {
        int c = (int)text[i];

        // Bounds of the printable ascii characters.
        if (c >= 0x20 && c <= 0x7e) {
            SDL_Rect sourceRect;
            int charIndexInAtlas = c - 0x20;
            int charColumn = charIndexInAtlas % 10;
            int charRow = charIndexInAtlas / 10;
            int destX = x + i * 4;

            sourceRect.x = charColumn * 4;
            sourceRect.y = charRow * 6;
            sourceRect.w = 3;
            sourceRect.h = 5;

            CopyFromSurfaceToPixelBuffer(state.fontAtlas, &sourceRect, destX, y, color);
        }
    }
}
