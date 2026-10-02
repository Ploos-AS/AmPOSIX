#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include "net_platform.h"
int amposix_platform_socket(int d,int t,int p){return socket(d,t,p);}
int amposix_platform_connect(int f,const void *a,size_t n){return connect(f,(const struct sockaddr *)a,(socklen_t)n);}
int amposix_platform_close_socket(int f){return close(f);}
int amposix_platform_select(int n,void *r,void *w,void *e,void *t){return select(n,(fd_set *)r,(fd_set *)w,(fd_set *)e,(struct timeval *)t);}
int amposix_platform_shutdown(int f,int h){return shutdown(f,h);}

#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "net_platform.h"
int amposix_platform_send(int f,const void *b,size_t n,int flags){return (int)send(f,b,n,flags);}
int amposix_platform_recv(int f,void *b,size_t n,int flags){return (int)recv(f,b,n,flags);}
