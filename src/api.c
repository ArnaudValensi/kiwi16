#include "api.h"
#include "renderer.h"

void ApiSetPixel(int x, int y, int color) {
    RendererSetPixel(x, y, color);
}
