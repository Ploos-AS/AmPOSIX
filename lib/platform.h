#ifndef AMPOSIX_PLATFORM_H
#define AMPOSIX_PLATFORM_H
#include <amposix/time.h>
#include <amposix/netdb.h>
int amposix_platform_setenv(const char *name,const char *value,int overwrite);
int amposix_platform_unsetenv(const char *name);
const char *amposix_platform_name(void);
int amposix_platform_clock_gettime(int clock_id,struct amposix_timespec *ts);
int amposix_platform_nanosleep(const struct amposix_timespec *request,struct amposix_timespec *remaining);
int amposix_platform_resolve_ipv4(const char *node,unsigned char address[4]);
#endif
