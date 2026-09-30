#include <stdio.h>
#include <string.h>
#include <amposix/netdb.h>
static int fails;
static void check(int ok,const char *name){if(!ok){fprintf(stderr,"FAIL %s\n",name);fails++;}}
int main(void)
{
 struct amposix_addrinfo *ai=0;
 struct amposix_addrinfo_hints hints;
 int rc;
 memset(&hints,0,sizeof(hints));hints.ai_family=AMPOSIX_AF_INET;hints.ai_socktype=AMPOSIX_SOCK_STREAM;
 rc=amposix_getaddrinfo("127.0.0.1","80",&hints,&ai);
 check(rc==0&&ai!=0,"numeric ipv4");
 if(ai){check(ai->ai_port==80,"port");check(ai->ai_addr[0]==127&&ai->ai_addr[3]==1,"address");amposix_freeaddrinfo(ai);}
 ai=0;rc=amposix_getaddrinfo("localhost","443",&hints,&ai);check(rc==0&&ai!=0,"localhost");amposix_freeaddrinfo(ai);
 rc=amposix_getaddrinfo("localhost","http",&hints,&ai);check(rc==AMPOSIX_EAI_SERVICE,"named service rejected");
 hints.ai_family=99;rc=amposix_getaddrinfo("localhost","80",&hints,&ai);check(rc==AMPOSIX_EAI_FAMILY,"family rejected");
 check(strcmp(amposix_gai_strerror(AMPOSIX_EAI_SERVICE),"service not supported")==0,"gai strerror");
 if (fails == 0) puts("libamposix netdb: PASS");
 return fails?1:0;
}
