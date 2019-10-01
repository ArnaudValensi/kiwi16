#include "commands/dev.h"
#include "commands/init.h"
#include "generated_usage.h"
#include <stdio.h>
#include <string.h>

int HandleArgs(int argc, char **argv) {
    (void)argv;
    if (argc == 1) {
        printf(USAGE);
        return 1;
    }

    if (strcmp("init", argv[1]) == 0) {
        return CommandInit();
    } else if (strcmp("dev", argv[1]) == 0) {
        return CommandDev();
    }

    printf(USAGE);
    return 1;
}

int main(int argc, char **argv) {
    return HandleArgs(argc, argv);
}
