#ifndef RENDERER_H
#define RENDERER_H

int RendererInit();
void RendererClean();
int RendererDraw();
void RendererSetPixel(int x, int y, int color);

#endif /* RENDERER_H */
