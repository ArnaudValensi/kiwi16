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
