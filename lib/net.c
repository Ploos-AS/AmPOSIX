#include <amposix/net.h>
#include <errno.h>
#include <stddef.h>
#include "net_platform.h"
int amposix_socket(int d,int t,int p){return amposix_platform_socket(d,t,p);}
int amposix_connect(int fd,const void *a,size_t n){return amposix_platform_connect(fd,a,n);}
int amposix_close_socket(int fd){return amposix_platform_close_socket(fd);}
int amposix_select(int n,void *r,void *w,void *e,void *t){return amposix_platform_select(n,r,w,e,t);}
int amposix_shutdown(int fd,int h){return amposix_platform_shutdown(fd,h);}
