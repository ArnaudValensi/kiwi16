#include "commands/commands.h"
#include "config.h"
#include "kiwios.h"
#include "lua.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const char kiwiUsageString[] = "Kiwi fantasy console\n"
                               "\n"
                               "USAGE:\n"
                               "    kiwi [OPTIONS] [SUBCOMMAND]\n"
                               "\n"
                               "OPTIONS:\n"
                               "    -V, --version           Print version info and exit\n"
                               "    -h, --help              Prints help information\n"
                               "\n"
                               "Kiwi commands are:\n"
                               "    init        Create a new kiwi game in an existing directory\n";

int HandleArgs(int argc, char **argv) {
    (void)argv;
    if (argc == 1) {
        printf(kiwiUsageString);
        return 1;
    }

    if (strcmp("init", argv[1]) == 0) {
        CommandInit();
        return 0;
    }

    printf(kiwiUsageString);
    return 1;
}

void WaitForNextTick() {
    static uint32_t nextTickTime = TICK_INTERVAL_IN_MS;

    uint32_t now = SDL_GetTicks();
    if (nextTickTime > now) {
        SDL_Delay(nextTickTime - now);
    }

    nextTickTime += TICK_INTERVAL_IN_MS;
}

int main(int argc, char **argv) {
    return HandleArgs(argc, argv);

    // SDL_Event event;
    // bool quit = false;

    // if (RendererInit()) {
    //     return 1;
    // }

    // LuaInit();

    // if (KiwiOsInit()) {
    //     return 1;
    // }

    // while (!quit) {
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             quit = true;
    //         }

    //         if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
    //             quit = true;
    //         }
    //     }

    //     // LuaCallScriptUpdate();
    //     KiwiOsUpdate();

    //     if (RendererDraw()) {
    //         return 1;
    //     }

    //     WaitForNextTick();
    // }

    // KiwiOsClean();
    // LuaClean();
    // RendererClean();

    return 0;
}
