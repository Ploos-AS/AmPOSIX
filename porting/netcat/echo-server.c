#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int s, c, port;
    struct sockaddr_in sa;
    char buf[256];
    int n;

    if (argc != 2) return 2;
    port = atoi(argv[1]);
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) return 1;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sa.sin_port = htons((unsigned short)port);
    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) return 1;
    if (listen(s, 1) < 0) return 1;
    fprintf(stderr, "READY\\n");
    fflush(stderr);
    c = accept(s, 0, 0);
    if (c < 0) return 1;
    n = recv(c, buf, sizeof(buf) - 1, 0);
    if (n < 0) return 1;
    if (send(c, buf, n, 0) != n) return 1;
    close(c);
    close(s);
    return 0;
}
