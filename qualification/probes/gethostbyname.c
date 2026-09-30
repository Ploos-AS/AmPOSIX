#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void)
{
 struct hostent *h=gethostbyname("localhost");
 return h?0:0;
}
