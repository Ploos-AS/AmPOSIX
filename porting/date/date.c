#include <stdio.h>
#include <amposix/time.h>

int main(void)
{
    struct amposix_timespec ts;
    if (amposix_clock_gettime(AMPOSIX_CLOCK_REALTIME, &ts) != 0)
        return 1;
    printf("%ld\n", ts.tv_sec);
    return 0;
}
