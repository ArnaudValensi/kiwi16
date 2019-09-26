#ifndef KW_RENDERER_H
#define KW_RENDERER_H

int RendererInit();
void RendererClean();
int RendererDraw();
void RendererSetPixel(int x, int y, int color);
void RendererSetPixelRect(int x, int y, int width, int height, int color);
void RendererDrawText(char *text, int x, int y, int color);
void *RendererLoadSprite(char *spritePath);
void RendererDrawSprite(void *sprite, int x, int y);

#endif /* KW_RENDERER_H */
