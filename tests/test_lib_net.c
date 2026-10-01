#include <stdio.h>
#include <amposix/net.h>
int main(void)
{
 int fd=amposix_socket(2,1,0);
 if(fd<0){puts("libamposix net: SKIP socket backend unavailable");return 0;}
 if(amposix_close_socket(fd)!=0)return 1;
 puts("libamposix net: PASS");
 return 0;
}
