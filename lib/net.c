#include <amposix/net.h>
#include "net_platform.h"
int amposix_socket(int d,int t,int p){return amposix_platform_socket(d,t,p);}
int amposix_connect(int f,const void *a,size_t n){return amposix_platform_connect(f,a,n);}
int amposix_send(int f,const void *b,size_t n,int flags){return amposix_platform_send(f,b,n,flags);}
int amposix_recv(int f,void *b,size_t n,int flags){return amposix_platform_recv(f,b,n,flags);}
int amposix_close_socket(int f){return amposix_platform_close_socket(f);}
int amposix_select(int n,amposix_fd_set *r,amposix_fd_set *w,amposix_fd_set *e,amposix_timeval *t){return amposix_platform_select(n,r,w,e,t);}
int amposix_shutdown(int f,int h){return amposix_platform_shutdown(f,h);}
