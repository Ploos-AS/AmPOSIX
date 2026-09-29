#ifndef AMPOSIX_ENV_H
#define AMPOSIX_ENV_H
#ifdef __cplusplus
extern "C" {
#endif
int amposix_setenv(const char *name,const char *value,int overwrite);
int amposix_unsetenv(const char *name);
#ifdef AMPOSIX_ENABLE_POSIX_NAMES
#define setenv amposix_setenv
#define unsetenv amposix_unsetenv
#endif
#ifdef __cplusplus
}
#endif
#endif
