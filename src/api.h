#ifndef KW_API_H
#define KW_API_H

void ApiSetPixel(int x, int y, int color);
void ApiSetPixelRect(int x, int y, int width, int height, int color);
void ApiDrawText(char *text, int x, int y, int color);
void *ApiLoadSprite(char *spritePath);
void ApiDrawSprite(void *sprite, int x, int y);

#endif /* KW_API_H */
