#ifndef AMPOSIX_TIME_H
#define AMPOSIX_TIME_H
#ifdef __cplusplus
extern "C" {
#endif
#define AMPOSIX_CLOCK_REALTIME 0
#define AMPOSIX_CLOCK_MONOTONIC 1
struct amposix_timespec { long tv_sec; long tv_nsec; };
int amposix_clock_gettime(int clock_id,struct amposix_timespec *ts);
int amposix_nanosleep(const struct amposix_timespec *request,struct amposix_timespec *remaining);
#ifdef __cplusplus
}
#endif
#endif
