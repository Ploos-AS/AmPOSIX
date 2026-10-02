#ifndef AMPOSIX_NET_H
#define AMPOSIX_NET_H
#include <stddef.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#define AMPOSIX_INVALID_SOCKET (-1)
#define AMPOSIX_SHUT_RD 0
#define AMPOSIX_SHUT_WR 1
#define AMPOSIX_SHUT_RDWR 2
typedef fd_set amposix_fd_set;
typedef struct timeval amposix_timeval;
int amposix_socket(int domain,int type,int protocol);
int amposix_connect(int fd,const void *address,size_t address_len);
int amposix_send(int fd,const void *buffer,size_t length,int flags);
int amposix_recv(int fd,void *buffer,size_t length,int flags);
int amposix_close_socket(int fd);
int amposix_select(int nfds,amposix_fd_set *readfds,amposix_fd_set *writefds,amposix_fd_set *exceptfds,amposix_timeval *timeout);
int amposix_shutdown(int fd,int how);
#endif
