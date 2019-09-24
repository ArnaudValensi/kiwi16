#ifndef KW_CONFIG_H
#define KW_CONFIG_H

#include <stdint.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 144
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_SCALE 5
#define TICK_INTERVAL_IN_MS 16 // ~60 FPS (1000/60)

extern const uint32_t COLORS[];

#endif /* KW_CONFIG_H */
