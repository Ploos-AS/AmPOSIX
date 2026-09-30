#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

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

int amposix_platform_resolve_ipv4(const char *node, unsigned char address[4])
{
    struct addrinfo hints;
    struct addrinfo *result = 0;
    struct addrinfo *it;
    int rc;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    rc = getaddrinfo(node, 0, &hints, &result);
    if (rc != 0)
        return AMPOSIX_EAI_NONAME;

    for (it = result; it; it = it->ai_next) {
        if (it->ai_family == AF_INET && it->ai_addr) {
            const struct sockaddr_in *sin = (const struct sockaddr_in *)it->ai_addr;
            const unsigned char *p = (const unsigned char *)&sin->sin_addr;
            address[0] = p[0]; address[1] = p[1];
            address[2] = p[2]; address[3] = p[3];
            freeaddrinfo(result);
            return 0;
        }
    }
    freeaddrinfo(result);
    return AMPOSIX_EAI_NONAME;
}
