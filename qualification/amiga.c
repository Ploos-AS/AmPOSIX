#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/features.h>
#include <amposix/string.h>
#include <amposix/stdio.h>
#include <amposix/env.h>
#include <amposix/time.h>
#include <amposix/net.h>
#include <sys/socket.h>
static int pass=0,fail=0,skip=0;
static void result(const char*n,int ok){printf("%s %s\n",ok?"PASS":"FAIL",n);if(ok)pass++;else fail++;}
static void skipped(const char*n,const char*why){printf("SKIP %s: %s\n",n,why);skip++;}
static void qualify_network_lifecycle(void)
{
 int fd;
 amposix_fd_set rfds;
 amposix_timeval tv;
 fd=amposix_socket(AF_INET,SOCK_STREAM,0);
 if(fd<0){if(errno==ENOSYS||errno==ENODEV)skipped("socket","platform backend unqualified");else result("socket",0);return;}
 result("socket",1);
 FD_ZERO(&rfds); FD_SET(fd,&rfds); tv.tv_sec=0; tv.tv_usec=0;
 errno=0;
 if(amposix_select(fd+1,&rfds,0,0,&tv)>=0)result("select",1);
 else if(errno==ENOSYS)skipped("select","platform backend unqualified");else result("select",0);
 result("socket-close",amposix_close_socket(fd)==0);
}

int main(void){char *p=0;size_t cap=0;FILE*f;struct amposix_timespec ts,before,after,delay={0,20000000L};
 printf("AmPOSIX qualification %s\n",amposix_version_string());
 p=amposix_strdup("amiga");result("strdup",p&&strcmp(p,"amiga")==0);free(p);p=0;
 {char b[5];size_t n=amposix_strlcpy(b,"abcdef",sizeof(b));result("strlcpy",n==6&&strcmp(b,"abcd")==0);}
 f=tmpfile();if(f){fputs("line\n",f);rewind(f);result("getline",amposix_getline(&p,&cap,f)==5&&strcmp(p,"line\n")==0);free(p);p=0;fclose(f);}else skipped("getline","tmpfile unavailable");
 errno=0;if(amposix_setenv("AMPOSIX_QUALIFY","1",1)==0){result("environment",getenv("AMPOSIX_QUALIFY")!=0);amposix_unsetenv("AMPOSIX_QUALIFY");}else if(errno==ENOSYS)skipped("environment","platform backend unqualified");else result("environment",0);
 errno=0;if(amposix_clock_gettime(AMPOSIX_CLOCK_REALTIME,&ts)==0)result("realtime",ts.tv_sec>=252460800L&&ts.tv_nsec>=0&&ts.tv_nsec<1000000000L);else if(errno==ENOSYS)skipped("realtime","platform backend unqualified");else result("realtime",0);
 errno=0;if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&ts)==0)result("monotonic",ts.tv_nsec>=0&&ts.tv_nsec<1000000000L);else if(errno==ENOSYS)skipped("monotonic","platform backend unqualified");else result("monotonic",0);
 errno=0;if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&before)==0&&amposix_nanosleep(&delay,0)==0&&amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&after)==0){long sec=after.tv_sec-before.tv_sec;long nsec=after.tv_nsec-before.tv_nsec;unsigned long long elapsed;if(nsec<0){sec--;nsec+=1000000000L;}elapsed=sec<0?0ULL:(unsigned long long)sec*1000000000ULL+(unsigned long long)nsec;result("nanosleep",elapsed>=20000000ULL);}else if(errno==ENOSYS)skipped("nanosleep","platform backend unqualified");else result("nanosleep",0);
 qualify_network_lifecycle();
 printf("SUMMARY pass=%d fail=%d skip=%d\n",pass,fail,skip);return fail?20:0;}
