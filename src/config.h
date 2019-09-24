#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_SCALE 4
#define TICK_INTERVAL_IN_MS 16 // ~60 FPS (1000/60)

extern const uint32_t COLORS[];

#endif /* CONFIG_H */
