#include "kiwios.h"
#include "api.h"
#include "config.h"
#include <stdio.h>

static void *spriteButtonNew;

int KiwiOsInit() {
    spriteButtonNew = ApiLoadSprite("./asset/button-new.png");

    if (spriteButtonNew == NULL) {
        fprintf(stderr, "ApiLoadSprite(\"./asset/button-new.png\") error\n");
        return 1;
    }

    return 0;
}

void KiwiOsUpdate() {
    // Draw top bar background.
    ApiSetPixelRect(0, 0, SCREEN_WIDTH, 9, 0);

    // Kiwi text 'K' background.
    ApiSetPixelRect(8, 1, 5, 7, 4);

    // Draw background.
    // TODO: Use clear color.
    ApiSetPixelRect(0, 9, SCREEN_WIDTH, SCREEN_HEIGHT - 9, 15);

    // Top left KIWI.
    ApiDrawText("K", 9, 2, 0);
    ApiDrawText("IWI", 14, 2, 4);

    // Date.
    ApiDrawText("TUE 11:33PM 1985", 185, 2, 4);

    // Title
    ApiDrawText("Home", 120, 2, 1);

    ApiDrawSprite(spriteButtonNew, 18, 24);
}

void KiwiOsClean() {
}
