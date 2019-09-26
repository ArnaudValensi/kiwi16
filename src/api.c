#include "api.h"
#include "renderer.h"

void ApiSetPixel(int x, int y, int color) {
    RendererSetPixel(x, y, color);
}

void ApiSetPixelRect(int x, int y, int width, int height, int color) {
    RendererSetPixelRect(x, y, width, height, color);
}

void ApiDrawText(char *text, int x, int y, int color) {
    RendererDrawText(text, x, y, color);
}

void *ApiLoadSprite(char *spritePath) {
    return RendererLoadSprite(spritePath);
}

void ApiDrawSprite(void *sprite, int x, int y) {
    RendererDrawSprite(sprite, x, y);
}
