#include <errno.h>
#include <stdio.h>
#include <amposix/time.h>
int main(void){struct amposix_timespec a,b,r={0,1000000L};
 if(amposix_clock_gettime(AMPOSIX_CLOCK_REALTIME,&a))return 1;
 if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&a))return 2;
 if(amposix_nanosleep(&r,0))return 3;
 if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&b))return 4;
 if(b.tv_sec<a.tv_sec||(b.tv_sec==a.tv_sec&&b.tv_nsec<a.tv_nsec))return 5;
 errno=0;r.tv_nsec=1000000000L;if(amposix_nanosleep(&r,0)!=-1||errno!=EINVAL)return 6;
 errno=0;if(amposix_clock_gettime(99,&a)!=-1||errno!=EINVAL)return 7;
 puts("libamposix time compatibility: PASS");return 0;}
