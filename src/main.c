#include "commands/dev.h"
#include "commands/init.h"
#include <stdio.h>
#include <string.h>

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
        return CommandInit();
    } else if (strcmp("dev", argv[1]) == 0) {
        return CommandDev();
    }

    printf(kiwiUsageString);
    return 1;
}

int main(int argc, char **argv) {
    return HandleArgs(argc, argv);
}
