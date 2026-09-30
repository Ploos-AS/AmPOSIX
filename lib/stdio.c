#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <amposix/stdio.h>

#define AMPOSIX_INITIAL_LINE 128U

static int grow(char **lineptr, size_t *capacity, size_t need)
{
    size_t next;
    char *resized;

    if (*capacity >= need)
        return 0;

    next = *capacity ? *capacity : AMPOSIX_INITIAL_LINE;
    while (next < need) {
        if (next > ((size_t)-1) / 2) {
            errno = ENOMEM;
            return -1;
        }
        next *= 2;
    }

    resized = (char *)realloc(*lineptr, next);
    if (!resized) {
        errno = ENOMEM;
        return -1;
    }

    *lineptr = resized;
    *capacity = next;
    return 0;
}

amposix_ssize_t amposix_getdelim(char **lineptr, size_t *n, int delimiter,
                                 FILE *stream)
{
    size_t used = 0;
    int ch;

    if (!lineptr || !n || !stream) {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL)
        *n = 0;

    for (;;) {
        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream))
                return -1;
            if (used == 0)
                return -1;
            break;
        }

        if (grow(lineptr, n, used + 2) != 0)
            return -1;

        (*lineptr)[used++] = (char)ch;
        if (ch == (unsigned char)delimiter)
            break;
    }

    if (grow(lineptr, n, used + 1) != 0)
        return -1;

    (*lineptr)[used] = '\0';
    if (used > (size_t)LONG_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    return (amposix_ssize_t)used;
}

amposix_ssize_t amposix_getline(char **lineptr, size_t *n, FILE *stream)
{
    return amposix_getdelim(lineptr, n, '\n', stream);
}
