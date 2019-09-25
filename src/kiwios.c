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
    // TODO: Use clear color.
    ApiSetPixelRect(0, 9, SCREEN_WIDTH, SCREEN_HEIGHT - 9, 15);

    ApiDrawText("K", 9, 2, 0);
    ApiDrawText("IWI", 14, 2, 4);
}

void KiwiOsClean() {
}
