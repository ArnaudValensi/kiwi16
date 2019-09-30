#include <stdio.h>
#include <sys/stat.h>

const char startFileTempate[] = "function update()\n\nend";

int fileExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

int CommandInit() {
    printf("CommandInit\n");

    const char *startFile = "./start.lua";
    FILE *fp;

    if (fileExists(startFile)) {
        printf("The file 'start.lua' already exists, keeping it.\n");
        return 0;
    }

    fp = fopen(startFile, "w");
    fprintf(fp, "%s\n", startFileTempate);
    fclose(fp);

    printf("Created new game project\n");

    return 0;
}
