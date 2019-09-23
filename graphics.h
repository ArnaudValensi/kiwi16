#ifndef GRAPHICS_H
#define GRAPHICS_H

int graphics_init();
void graphics_clean();
int graphics_update(void (*on_update)(uint32_t *));

#endif /* GRAPHICS_H */
