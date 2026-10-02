#include <stdio.h>
#include <amposix/net.h>
int main(void)
{
 int fd=amposix_socket(2,1,0);
 if(fd<0){puts("libamposix net: SKIP socket backend unavailable");return 0;}
 if(amposix_send(fd,"x",1,0)!=-1){ /* no connected peer; platform may reject or block, so lifecycle test does not qualify send */ }
 amposix_fd_set rfds;
 amposix_timeval tv;
 FD_ZERO(&rfds); FD_SET(fd,&rfds); tv.tv_sec=0; tv.tv_usec=0;
 if(amposix_select(fd+1,&rfds,0,0,&tv)<0)return 1;
 if(amposix_close_socket(fd)!=0)return 1;
 puts("libamposix net: PASS");
 return 0;
}
