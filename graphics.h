#ifndef GRAPHICS_H
#define GRAPHICS_H

int graphics_init();
void graphics_clean();
int graphics_draw();
void graphics_set_pixel(int x, int y, int color);

#endif /* GRAPHICS_H */
