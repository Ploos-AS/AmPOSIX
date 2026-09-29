/* POSIX-ish headers relevant to porting analysis. */
#ifndef AMPOSIX_HEADERS_H
#define AMPOSIX_HEADERS_H
struct amposix_header { const char *name; const char *class_name; const char *note; };
static const struct amposix_header amposix_headers[] = {
 {"unistd.h","adapt","Broad POSIX interface; inspect APIs actually used."},
 {"sys/mman.h","adapt","Memory mapping semantics require review."},
 {"sys/epoll.h","unsupported","Linux-specific event API."},
 {"sys/inotify.h","unsupported","Linux-specific filesystem notification API."},
 {"pthread.h","investigate","Thread semantics require explicit Amiga mapping."},
 {"dirent.h","native","Directory operations can map to AmigaDOS/libc."},
 {"sys/socket.h","native","Networking maps through the Amiga socket interface."},
 {"netdb.h","library","Resolver compatibility may require AmPOSIX."},
 {"arpa/inet.h","native","Networking compatibility header."}
};
#define AMPOSIX_HEADER_COUNT (sizeof(amposix_headers)/sizeof(amposix_headers[0]))
#endif
