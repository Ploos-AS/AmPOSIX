#ifndef AMPOSIX_NET_PLATFORM_H
#define AMPOSIX_NET_PLATFORM_H
#include <stddef.h>
int amposix_platform_socket(int domain,int type,int protocol);
int amposix_platform_connect(int fd,const void *address,size_t address_len);
int amposix_platform_close_socket(int fd);
int amposix_platform_select(int nfds,void *readfds,void *writefds,void *exceptfds,void *timeout);
int amposix_platform_shutdown(int fd,int how);
#endif
