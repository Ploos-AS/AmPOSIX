/* Capability probe: native getaddrinfo must not be assumed on classic AmigaOS.
 * This file is intentionally informational and is not a required build target.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void)
{
    struct addrinfo hints;
    struct addrinfo *result = 0;
    (void)hints;
    (void)result;
    return 0;
}
