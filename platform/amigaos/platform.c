/* AmigaOS platform backend.
 * Keep mappings conservative: only expose semantics we have cross-compiled
 * and can qualify on the target runtime.
 */
#include <errno.h>
#include <devices/timer.h>
#include <proto/timer.h>
#include "platform.h"

int amposix_platform_setenv(const char*name,const char*value,int overwrite)
{(void)name;(void)value;(void)overwrite;errno=ENOSYS;return -1;}

int amposix_platform_unsetenv(const char*name)
{(void)name;errno=ENOSYS;return -1;}

const char *amposix_platform_name(void){return "amigaos";}

static int monotonic_eclock(struct amposix_timespec *ts)
{
 struct EClockVal v;
 ULONG hz=ReadEClock(&v);
 unsigned long long ticks;
 unsigned long long rem;
 if(hz==0){errno=EIO;return -1;}
 ticks=((unsigned long long)v.ev_hi<<32)|(unsigned long long)v.ev_lo;
 ts->tv_sec=(long)(ticks/(unsigned long long)hz);
 rem=ticks%(unsigned long long)hz;
 ts->tv_nsec=(long)((rem*1000000000ULL)/(unsigned long long)hz);
 return 0;
}

int amposix_platform_clock_gettime(int id,struct amposix_timespec*ts)
{
 if(id==AMPOSIX_CLOCK_MONOTONIC)return monotonic_eclock(ts);
 (void)ts;
 errno=ENOSYS;
 return -1;
}

int amposix_platform_nanosleep(const struct amposix_timespec*r,struct amposix_timespec*o)
{(void)r;(void)o;errno=ENOSYS;return -1;}
