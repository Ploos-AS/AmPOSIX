#include <stdio.h>

int main(void)
{
    unsigned long lines = 0;
    unsigned long words = 0;
    unsigned long bytes = 0;
    int ch;
    int in_word = 0;

    while ((ch = getchar()) != EOF) {
        bytes++;
        if (ch == '\n')
            lines++;
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ||
            ch == '\f' || ch == '\v') {
            in_word = 0;
        } else if (!in_word) {
            words++;
            in_word = 1;
        }
    }

    if (ferror(stdin))
        return 1;

    printf("%lu %lu %lu\n", lines, words, bytes);
    return 0;
}
