/* M1 feature database. Keep this deliberately simple and C89-friendly. */
#ifndef AMPOSIX_FEATURE_DB_H
#define AMPOSIX_FEATURE_DB_H
struct amposix_feature { const char *name; const char *class_name; const char *area; const char *note; };
static const struct amposix_feature amposix_features[] = {
 {"open","native","files","Prefer libc/AmigaDOS-backed implementation."},
 {"close","native","files",""}, {"read","native","files",""}, {"write","native","files",""},
 {"stat","native","files",""}, {"opendir","native","directories",""}, {"readdir","native","directories",""},
 {"getenv","native","environment","Use the C environment where available; AmigaDOS variables are a distinct backend concern."}, {"socket","native","network","Map through the native Amiga networking interface."},
 {"connect","native","network",""}, {"select","native","network",""}, {"getaddrinfo","library","network",""},
 {"strdup","library","libc","Implemented by libamposix as amposix_strdup."}, {"strndup","library","libc","Implemented by libamposix as amposix_strndup."}, {"strlcpy","library","bsd-extension","BSD extension implemented as amposix_strlcpy."}, {"strlcat","library","bsd-extension","BSD extension implemented as amposix_strlcat."},
 {"getline","library","libc","Implemented by libamposix as amposix_getline."}, {"getdelim","library","libc","Implemented by libamposix as amposix_getdelim."}, {"getopt_long","library","libc",""}, {"clock_gettime","library","time","Host realtime and monotonic backends implemented; AmigaOS backend unqualified."},
 {"pthread_create","investigate","threads","Requires an explicit, documented Amiga execution-model mapping."},
 {"fork","adapt","process","Prefer spawn-style adaptation; do not fake Unix fork semantics."},
 {"execvp","adapt","process",""}, {"mmap","adapt","memory",""},
 {"epoll_create","unsupported","events",""}, {"epoll_wait","unsupported","events",""},
 {"inotify_init","unsupported","filesystem-events",""},
 {"lstat","investigate","files","Verify libc behaviour and symlink semantics."},
 {"fstat","investigate","files","Verify descriptor semantics."},
 {"access","investigate","files","Permission semantics differ across platforms."},
 {"fcntl","investigate","files","Command coverage must be mapped individually."},
 {"pipe","investigate","ipc","Requires Amiga execution and stream semantics review."},
 {"dup","investigate","files","Descriptor behaviour requires qualification."},
 {"dup2","investigate","files","Descriptor behaviour requires qualification."},
 {"poll","investigate","events","Determine native or compatibility implementation."},
 {"nanosleep","library","time","Host backend implemented; AmigaOS timing semantics require qualification."},
 {"usleep","investigate","time","Timing resolution requires qualification."},
 {"setenv","library","environment","Host backend implemented; AmigaDOS backend still requires qualification."},
 {"unsetenv","library","environment","Host backend implemented; AmigaDOS backend still requires qualification."},
 {"realpath","investigate","paths","Amiga path semantics require explicit mapping."},
 {"symlink","investigate","files","Filesystem support and semantics vary."},
 {"readlink","investigate","files","Filesystem support and semantics vary."},
 {"kill","adapt","process","Unix signal/process semantics require source adaptation."},
 {"waitpid","adapt","process","Unix child-process semantics require source adaptation."},
 {"sigaction","adapt","signals","Unix signal semantics do not map directly to AmigaOS."},
 {"sigprocmask","adapt","signals","Unix signal-mask semantics do not map directly to AmigaOS."}
};
#define AMPOSIX_FEATURE_COUNT (sizeof(amposix_features)/sizeof(amposix_features[0]))
#endif
