#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/features.h>
#include <amposix/string.h>
#include <amposix/stdio.h>
#include <amposix/env.h>
#include <amposix/time.h>
static int pass=0,fail=0,skip=0;
static void result(const char*n,int ok){printf("%s %s\n",ok?"PASS":"FAIL",n);if(ok)pass++;else fail++;}
static void skipped(const char*n,const char*why){printf("SKIP %s: %s\n",n,why);skip++;}
int main(void){char *p=0;size_t cap=0;FILE*f;struct amposix_timespec ts,before,after,delay={0,1000000L};
 printf("AmPOSIX qualification %s\n",amposix_version_string());
 p=amposix_strdup("amiga");result("strdup",p&&strcmp(p,"amiga")==0);free(p);p=0;
 {char b[5];size_t n=amposix_strlcpy(b,"abcdef",sizeof(b));result("strlcpy",n==6&&strcmp(b,"abcd")==0);}
 f=tmpfile();if(f){fputs("line\n",f);rewind(f);result("getline",amposix_getline(&p,&cap,f)==5&&strcmp(p,"line\n")==0);free(p);p=0;fclose(f);}else skipped("getline","tmpfile unavailable");
 errno=0;if(amposix_setenv("AMPOSIX_QUALIFY","1",1)==0){result("environment",getenv("AMPOSIX_QUALIFY")!=0);amposix_unsetenv("AMPOSIX_QUALIFY");}else if(errno==ENOSYS)skipped("environment","platform backend unqualified");else result("environment",0);
 errno=0;if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&ts)==0)result("monotonic",ts.tv_nsec>=0&&ts.tv_nsec<1000000000L);else if(errno==ENOSYS)skipped("monotonic","platform backend unqualified");else result("monotonic",0);
 errno=0;if(amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&before)==0&&amposix_nanosleep(&delay,0)==0&&amposix_clock_gettime(AMPOSIX_CLOCK_MONOTONIC,&after)==0)result("nanosleep",(after.tv_sec>before.tv_sec)||(after.tv_sec==before.tv_sec&&after.tv_nsec>=before.tv_nsec));else if(errno==ENOSYS)skipped("nanosleep","platform backend unqualified");else result("nanosleep",0);
 printf("SUMMARY pass=%d fail=%d skip=%d\n",pass,fail,skip);return fail?20:0;}
