#include "kiwios.h"
#include "api.h"
#include "config.h"

void KiwiOsInit() {
}

void KiwiOsUpdate() {
    // Draw top bar background.
    ApiSetPixelRect(0, 0, SCREEN_WIDTH, 9, 0);

    // Kiwi text 'K' background.
    ApiSetPixelRect(8, 1, 5, 7, 4);

    // Draw background.
    ApiSetPixelRect(0, 9, SCREEN_WIDTH, SCREEN_HEIGHT - 9, 15);
}

void KiwiOsClean() {
}
