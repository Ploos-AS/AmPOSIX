#ifndef AMPOSIX_NET_H
#define AMPOSIX_NET_H
#include <stddef.h>
#define AMPOSIX_INVALID_SOCKET (-1)
#define AMPOSIX_SHUT_RD 0
#define AMPOSIX_SHUT_WR 1
#define AMPOSIX_SHUT_RDWR 2
int amposix_socket(int domain,int type,int protocol);
int amposix_connect(int fd,const void *address,size_t address_len);
int amposix_close_socket(int fd);
int amposix_select(int nfds,void *readfds,void *writefds,void *exceptfds,void *timeout);
int amposix_shutdown(int fd,int how);
#endif
