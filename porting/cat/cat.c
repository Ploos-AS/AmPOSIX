#include <stdio.h>

int main(void)
{
    int ch;
    while ((ch = getchar()) != EOF)
        if (putchar(ch) == EOF)
            return 1;
    return ferror(stdin) ? 1 : 0;
}
