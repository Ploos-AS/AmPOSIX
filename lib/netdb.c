#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <amposix/netdb.h>
#include "platform.h"

static int parse_service(const char *s,unsigned short *port)
{
 unsigned long n=0;
 const unsigned char *p=(const unsigned char *)s;
 if(!s||!*s){*port=0;return 0;}
 while(*p){if(*p<'0'||*p>'9')return AMPOSIX_EAI_SERVICE;n=n*10UL+(unsigned long)(*p-'0');if(n>65535UL)return AMPOSIX_EAI_SERVICE;p++;}
 *port=(unsigned short)n;return 0;
}
int amposix_getaddrinfo(const char *node,const char *service,
 const struct amposix_addrinfo_hints *hints,struct amposix_addrinfo **result)
{
 struct amposix_addrinfo *ai; unsigned short port; int rc;
 if(!result)return AMPOSIX_EAI_FAIL; *result=0;
 if(!node||!*node)return AMPOSIX_EAI_NONAME;
 if(hints&&hints->ai_family!=AMPOSIX_AF_UNSPEC&&hints->ai_family!=AMPOSIX_AF_INET)return AMPOSIX_EAI_FAMILY;
 rc=parse_service(service,&port);if(rc)return rc;
 ai=(struct amposix_addrinfo *)calloc(1,sizeof(*ai));if(!ai)return AMPOSIX_EAI_MEMORY;
 ai->ai_family=AMPOSIX_AF_INET;ai->ai_socktype=hints?hints->ai_socktype:0;ai->ai_protocol=hints?hints->ai_protocol:0;ai->ai_port=port;
 rc=amposix_platform_resolve_ipv4(node,ai->ai_addr);
 if(rc!=0){free(ai);return rc;}
 *result=ai;return 0;
}
void amposix_freeaddrinfo(struct amposix_addrinfo *ai)
{while(ai){struct amposix_addrinfo *next=ai->ai_next;free(ai->ai_canonname);free(ai);ai=next;}}
const char *amposix_gai_strerror(int e)
{
 switch(e){case 0:return "success";case AMPOSIX_EAI_NONAME:return "name or service not known";case AMPOSIX_EAI_FAIL:return "resolver failure";case AMPOSIX_EAI_FAMILY:return "address family not supported";case AMPOSIX_EAI_MEMORY:return "memory allocation failure";case AMPOSIX_EAI_SERVICE:return "service not supported";default:return "resolver error";}
}
