#include <stdio.h>
#include <amposix/time.h>

int main(void)
{
    struct amposix_timespec req;
    req.tv_sec = 0;
    req.tv_nsec = 20000000L;
    if (amposix_nanosleep(&req, 0) != 0)
        return 1;
    puts("slept");
    return 0;
}
