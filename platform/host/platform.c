#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdlib.h>
#include <time.h>

#include "platform.h"

#if !defined(_WIN32)
extern int setenv(const char *, const char *, int);
extern int unsetenv(const char *);
#endif

int amposix_platform_setenv(const char *name, const char *value, int overwrite)
{
#if defined(_WIN32)
    (void)name;
    (void)value;
    (void)overwrite;
    errno = ENOSYS;
    return -1;
#else
    return setenv(name, value, overwrite);
#endif
}

int amposix_platform_unsetenv(const char *name)
{
#if defined(_WIN32)
    (void)name;
    errno = ENOSYS;
    return -1;
#else
    return unsetenv(name);
#endif
}

const char *amposix_platform_name(void)
{
    return "host";
}

int amposix_platform_clock_gettime(int id, struct amposix_timespec *out)
{
    struct timespec ts;
    clockid_t clock_id =
        id == AMPOSIX_CLOCK_MONOTONIC ? CLOCK_MONOTONIC : CLOCK_REALTIME;

    if (clock_gettime(clock_id, &ts) != 0)
        return -1;

    out->tv_sec = (long)ts.tv_sec;
    out->tv_nsec = ts.tv_nsec;
    return 0;
}

int amposix_platform_nanosleep(const struct amposix_timespec *request,
                               struct amposix_timespec *remaining)
{
    struct timespec req;
    struct timespec rem;
    struct timespec *remp = remaining ? &rem : 0;
    int rc;

    req.tv_sec = (time_t)request->tv_sec;
    req.tv_nsec = request->tv_nsec;
    rc = nanosleep(&req, remp);

    if (remaining && rc != 0 && errno == EINTR) {
        remaining->tv_sec = (long)rem.tv_sec;
        remaining->tv_nsec = rem.tv_nsec;
    }

    return rc;
}
