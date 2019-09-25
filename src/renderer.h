#ifndef KW_RENDERER_H
#define KW_RENDERER_H

int RendererInit();
void RendererClean();
int RendererDraw();
void RendererSetPixel(int x, int y, int color);
void RendererSetPixelRect(int x, int y, int width, int height, int color);

#endif /* KW_RENDERER_H */
