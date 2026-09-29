#include <sys/socket.h>
int probe_network(void)
{
    return socket(0, 0, 0);
}
