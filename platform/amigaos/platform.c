/* AmigaOS platform backend. */
#include <errno.h>
#include <string.h>
#include <exec/io.h>
#include <devices/timer.h>
#include <proto/exec.h>
#include <proto/timer.h>
#include "platform.h"

struct Device *TimerBase;

int amposix_platform_setenv(const char*n,const char*v,int o){(void)n;(void)v;(void)o;errno=ENOSYS;return -1;}
int amposix_platform_unsetenv(const char*n){(void)n;errno=ENOSYS;return -1;}
const char *amposix_platform_name(void){return "amigaos";}

static int monotonic_eclock(struct amposix_timespec *ts)
{
 struct timerequest tr;
 struct EClockVal v;
 ULONG hz;
 unsigned long long ticks,rem;
 memset(&tr,0,sizeof(tr));
 if(OpenDevice(TIMERNAME,UNIT_ECLOCK,(struct IORequest *)&tr,0)!=0){errno=EIO;return -1;}
 TimerBase=tr.tr_node.io_Device;
 hz=ReadEClock(&v);
 CloseDevice((struct IORequest *)&tr);
 TimerBase=0;
 if(hz==0){errno=EIO;return -1;}
 ticks=((unsigned long long)v.ev_hi<<32)|(unsigned long long)v.ev_lo;
 ts->tv_sec=(long)(ticks/(unsigned long long)hz);
 rem=ticks%(unsigned long long)hz;
 ts->tv_nsec=(long)((rem*1000000000ULL)/(unsigned long long)hz);
 return 0;
}

static int realtime_system_clock(struct amposix_timespec *ts)
{
 struct timerequest tr;
 unsigned long long seconds;
 memset(&tr,0,sizeof(tr));
 if(OpenDevice(TIMERNAME,UNIT_MICROHZ,(struct IORequest *)&tr,0)!=0){
  errno=EIO;
  return -1;
 }
 tr.tr_node.io_Command=TR_GETSYSTIME;
 DoIO((struct IORequest *)&tr);
 seconds=(unsigned long long)tr.tr_time.tv_secs+252460800ULL;
 ts->tv_sec=(long)seconds;
 ts->tv_nsec=(long)tr.tr_time.tv_micro*1000L;
 CloseDevice((struct IORequest *)&tr);
 return 0;
}

int amposix_platform_clock_gettime(int id,struct amposix_timespec*ts)
{
 if(id==AMPOSIX_CLOCK_REALTIME)return realtime_system_clock(ts);
 if(id==AMPOSIX_CLOCK_MONOTONIC)return monotonic_eclock(ts);
 errno=EINVAL;return -1;
}
int amposix_platform_nanosleep(const struct amposix_timespec *request,
                              struct amposix_timespec *remaining)
{
 struct timerequest tr;
 unsigned long seconds;
 unsigned long micros;

 seconds=(unsigned long)request->tv_sec;
 micros=((unsigned long)request->tv_nsec+999UL)/1000UL;
 if(micros>=1000000UL){seconds++;micros-=1000000UL;}

 memset(&tr,0,sizeof(tr));
 if(OpenDevice(TIMERNAME,UNIT_MICROHZ,(struct IORequest *)&tr,0)!=0){
  errno=EIO;
  return -1;
 }

 tr.tr_node.io_Command=TR_ADDREQUEST;
 tr.tr_time.tv_secs=seconds;
 tr.tr_time.tv_micro=micros;
 DoIO((struct IORequest *)&tr);
 CloseDevice((struct IORequest *)&tr);

 if(remaining){
  remaining->tv_sec=0;
  remaining->tv_nsec=0;
 }
 return 0;
}
