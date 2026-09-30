#ifndef AMPOSIX_NETDB_H
#define AMPOSIX_NETDB_H
#ifdef __cplusplus
extern "C" {
#endif
#define AMPOSIX_AF_UNSPEC 0
#define AMPOSIX_AF_INET 2
#define AMPOSIX_SOCK_STREAM 1
#define AMPOSIX_SOCK_DGRAM 2
#define AMPOSIX_EAI_NONAME -2
#define AMPOSIX_EAI_FAIL -4
#define AMPOSIX_EAI_FAMILY -6
#define AMPOSIX_EAI_MEMORY -10
#define AMPOSIX_EAI_SERVICE -8
struct amposix_addrinfo {
 int ai_family;
 int ai_socktype;
 int ai_protocol;
 unsigned short ai_port;
 unsigned char ai_addr[4];
 char *ai_canonname;
 struct amposix_addrinfo *ai_next;
};
struct amposix_addrinfo_hints {
 int ai_family;
 int ai_socktype;
 int ai_protocol;
};
int amposix_getaddrinfo(const char *node,const char *service,
 const struct amposix_addrinfo_hints *hints,struct amposix_addrinfo **result);
void amposix_freeaddrinfo(struct amposix_addrinfo *result);
const char *amposix_gai_strerror(int error);
#ifdef __cplusplus
}
#endif
#endif
