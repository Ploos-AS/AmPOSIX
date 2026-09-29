#include <errno.h>
#include <amposix/time.h>
#include "platform.h"
static int valid_ts(const struct amposix_timespec*t){return t&&t->tv_sec>=0&&t->tv_nsec>=0&&t->tv_nsec<1000000000L;}
int amposix_clock_gettime(int id,struct amposix_timespec*ts){if(!ts||(id!=AMPOSIX_CLOCK_REALTIME&&id!=AMPOSIX_CLOCK_MONOTONIC)){errno=EINVAL;return -1;}return amposix_platform_clock_gettime(id,ts);}
int amposix_nanosleep(const struct amposix_timespec*req,struct amposix_timespec*rem){if(!valid_ts(req)){errno=EINVAL;return -1;}return amposix_platform_nanosleep(req,rem);}
