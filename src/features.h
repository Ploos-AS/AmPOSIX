/* M1 feature database. Keep this deliberately simple and C89-friendly. */
#ifndef AMPOSIX_FEATURES_H
#define AMPOSIX_FEATURES_H
struct amposix_feature { const char *name; const char *class_name; const char *area; const char *note; };
static const struct amposix_feature amposix_features[] = {
 {"open","native","files","Prefer libc/AmigaDOS-backed implementation."},
 {"close","native","files",""}, {"read","native","files",""}, {"write","native","files",""},
 {"stat","native","files",""}, {"opendir","native","directories",""}, {"readdir","native","directories",""},
 {"getenv","native","environment",""}, {"socket","native","network","Map through the native Amiga networking interface."},
 {"connect","native","network",""}, {"select","native","network",""}, {"getaddrinfo","library","network",""},
 {"getline","library","libc",""}, {"getopt_long","library","libc",""}, {"clock_gettime","library","time",""},
 {"pthread_create","investigate","threads","Requires an explicit, documented Amiga execution-model mapping."},
 {"fork","adapt","process","Prefer spawn-style adaptation; do not fake Unix fork semantics."},
 {"execvp","adapt","process",""}, {"mmap","adapt","memory",""},
 {"epoll_create","unsupported","events",""}, {"epoll_wait","unsupported","events",""},
 {"inotify_init","unsupported","filesystem-events",""}
};
#define AMPOSIX_FEATURE_COUNT (sizeof(amposix_features)/sizeof(amposix_features[0]))
#endif
