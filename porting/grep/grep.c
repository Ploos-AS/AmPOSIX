#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char line[4096];
    if (argc != 2)
        return 2;
    while (fgets(line, sizeof(line), stdin)) {
        if (strstr(line, argv[1]) != NULL)
            fputs(line, stdout);
    }
    return ferror(stdin) ? 1 : 0;
}
