#ifndef AMPOSIX_NET_PLATFORM_H
#define AMPOSIX_NET_PLATFORM_H
#include <stddef.h>
#include <sys/select.h>
#include <sys/time.h>
int amposix_platform_socket(int domain,int type,int protocol);
int amposix_platform_connect(int fd,const void *address,size_t address_len);
int amposix_platform_send(int fd,const void *buffer,size_t length,int flags);
int amposix_platform_recv(int fd,void *buffer,size_t length,int flags);
int amposix_platform_close_socket(int fd);
int amposix_platform_select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,struct timeval *timeout);
int amposix_platform_shutdown(int fd,int how);
#endif
