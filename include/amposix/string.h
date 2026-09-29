#ifndef AMPOSIX_STRING_H
#define AMPOSIX_STRING_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
char *amposix_strdup(const char *s);
char *amposix_strndup(const char *s,size_t maxlen);
size_t amposix_strlcpy(char *dst,const char *src,size_t size);
size_t amposix_strlcat(char *dst,const char *src,size_t size);
#ifdef AMPOSIX_ENABLE_POSIX_NAMES
#define strdup amposix_strdup
#define strndup amposix_strndup
#endif
#ifdef AMPOSIX_ENABLE_BSD_NAMES
#define strlcpy amposix_strlcpy
#define strlcat amposix_strlcat
#endif
#ifdef __cplusplus
}
#endif
#endif
