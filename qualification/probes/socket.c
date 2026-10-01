#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <amposix/net.h>

static int check_socket(void)
{
 int fd=amposix_socket(AF_INET,SOCK_STREAM,0);
 if(fd<0)return 0;
 if(amposix_close_socket(fd)!=0)return 0;
 return 1;
}

int main(void)
{
 if(check_socket()){puts("PASS socket");return 0;}
 if(errno==ENOSYS||errno==ENODEV){puts("SKIP socket backend unavailable");return 0;}
 puts("FAIL socket");return 1;
}
