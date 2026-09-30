#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void)
{
 struct addrinfo hints;
 struct addrinfo *result=0;
 int rc;
 hints.ai_flags=0;
 hints.ai_family=AF_UNSPEC;
 hints.ai_socktype=SOCK_STREAM;
 hints.ai_protocol=0;
 hints.ai_addrlen=0;
 hints.ai_addr=0;
 hints.ai_canonname=0;
 hints.ai_next=0;
 rc=getaddrinfo("localhost","80",&hints,&result);
 if(rc==0&&result)freeaddrinfo(result);
 return 0;
}
