#include <errno.h>
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <time.h>
#include "platform.h"
#if !defined(_WIN32)
extern int setenv(const char *,const char *,int);
extern int unsetenv(const char *);
#endif
int amposix_platform_setenv(const char*name,const char*value,int overwrite){
#if defined(_WIN32)
 (void)name;(void)value;(void)overwrite;errno=ENOSYS;return -1;
#else
 return setenv(name,value,overwrite);
#endif
}
int amposix_platform_unsetenv(const char*name){
#if defined(_WIN32)
 (void)name;errno=ENOSYS;return -1;
#else
 return unsetenv(name);
#endif
}
const char *amposix_platform_name(void){return "host";}

int amposix_platform_clock_gettime(int id,struct amposix_timespec*o){struct timespec t;clockid_t c=id==AMPOSIX_CLOCK_MONOTONIC?CLOCK_MONOTONIC:CLOCK_REALTIME;if(clock_gettime(c,&t))return -1;o->tv_sec=(long)t.tv_sec;o->tv_nsec=t.tv_nsec;return 0;}
int amposix_platform_nanosleep(const struct amposix_timespec*r,struct amposix_timespec*o){struct timespec a,b,*bp=o?&b:0;int rc;a.tv_sec=(time_t)r->tv_sec;a.tv_nsec=r->tv_nsec;rc=nanosleep(&a,bp);if(o&&rc){o->tv_sec=(long)b.tv_sec;o->tv_nsec=b.tv_nsec;}return rc;}
