#ifndef AMPOSIX_PLATFORM_H
#define AMPOSIX_PLATFORM_H
int amposix_platform_setenv(const char *name,const char *value,int overwrite);
int amposix_platform_unsetenv(const char *name);
const char *amposix_platform_name(void);
#endif
