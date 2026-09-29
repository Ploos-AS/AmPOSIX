#ifndef AMPOSIX_STDIO_H
#define AMPOSIX_STDIO_H
#include <stddef.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef long amposix_ssize_t;
amposix_ssize_t amposix_getdelim(char **lineptr,size_t *n,int delimiter,FILE *stream);
amposix_ssize_t amposix_getline(char **lineptr,size_t *n,FILE *stream);
#ifdef AMPOSIX_ENABLE_POSIX_NAMES
#define getdelim amposix_getdelim
#define getline amposix_getline
#endif
#ifdef __cplusplus
}
#endif
#endif
