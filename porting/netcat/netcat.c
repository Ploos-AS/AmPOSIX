#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <amposix/net.h>
#include <amposix/netdb.h>

static unsigned short parse_port(const char *s)
{
    unsigned long n = 0;
    while (*s >= '0' && *s <= '9') {
        n = n * 10UL + (unsigned long)(*s - '0');
        if (n > 65535UL) return 0;
        s++;
    }
    return *s ? 0 : (unsigned short)n;
}

int main(int argc, char **argv)
{
    struct amposix_addrinfo_hints hints;
    struct amposix_addrinfo *ai = 0;
    struct sockaddr_in sa;
    int fd;
    char buffer[256];
    size_t i;
    int n;

    if (argc != 3 || !parse_port(argv[2])) return 2;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AMPOSIX_AF_INET;
    hints.ai_socktype = AMPOSIX_SOCK_STREAM;
    if (amposix_getaddrinfo(argv[1], argv[2], &hints, &ai) != 0) return 1;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    memcpy(&sa.sin_addr, ai->ai_addr, 4);
    sa.sin_port = htons(ai->ai_port);
    amposix_freeaddrinfo(ai);

    fd = amposix_socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return 1;
    if (amposix_connect(fd, &sa, sizeof(sa)) != 0) {
        amposix_close_socket(fd);
        return 1;
    }
    i = 0;
    while (i < sizeof(buffer) - 1) {
        int ch = getchar();
        if (ch == EOF) break;
        buffer[i++] = (char)ch;
    }
    if (i && amposix_send(fd, buffer, i, 0) < 0) {
        amposix_close_socket(fd);
        return 1;
    }
    n = amposix_recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        amposix_close_socket(fd);
        return 1;
    }
    buffer[n] = 0;
    fputs(buffer, stdout);
    amposix_close_socket(fd);
    return 0;
}
