/* M1 feature database. Keep this deliberately simple and C89-friendly. */
#ifndef AMPOSIX_FEATURE_DB_H
#define AMPOSIX_FEATURE_DB_H
#include <amposix/features.h>
struct amposix_feature { const char *name; enum amposix_support support; const char *area; const char *note; };
static const struct amposix_feature amposix_features[] = {
 {"open",AMPOSIX_SUPPORT_NATIVE,"files","Prefer libc/AmigaDOS-backed implementation."},
 {"close",AMPOSIX_SUPPORT_NATIVE,"files",""}, {"read",AMPOSIX_SUPPORT_NATIVE,"files",""}, {"write",AMPOSIX_SUPPORT_NATIVE,"files",""},
 {"stat",AMPOSIX_SUPPORT_NATIVE,"files",""}, {"opendir",AMPOSIX_SUPPORT_NATIVE,"directories",""}, {"readdir",AMPOSIX_SUPPORT_NATIVE,"directories",""},
 {"getenv",AMPOSIX_SUPPORT_NATIVE,"environment","Use the C environment where available; AmigaDOS variables are a distinct backend concern."}, {"socket",AMPOSIX_SUPPORT_NATIVE,"network","Map through the native Amiga networking interface."},
 {"connect",AMPOSIX_SUPPORT_NATIVE,"network",""}, {"select",AMPOSIX_SUPPORT_NATIVE,"network",""}, {"getaddrinfo",AMPOSIX_SUPPORT_LIBRARY,"network",""},
 {"strdup",AMPOSIX_SUPPORT_LIBRARY,"libc","Implemented by libamposix as amposix_strdup."}, {"strndup",AMPOSIX_SUPPORT_LIBRARY,"libc","Implemented by libamposix as amposix_strndup."}, {"strlcpy",AMPOSIX_SUPPORT_LIBRARY,"bsd-extension","BSD extension implemented as amposix_strlcpy."}, {"strlcat",AMPOSIX_SUPPORT_LIBRARY,"bsd-extension","BSD extension implemented as amposix_strlcat."},
 {"getline",AMPOSIX_SUPPORT_LIBRARY,"libc","Implemented by libamposix as amposix_getline."}, {"getdelim",AMPOSIX_SUPPORT_LIBRARY,"libc","Implemented by libamposix as amposix_getdelim."}, {"getopt_long",AMPOSIX_SUPPORT_LIBRARY,"libc",""}, {"clock_gettime",AMPOSIX_SUPPORT_LIBRARY,"time","Host realtime and monotonic backends implemented; AmigaOS backend unqualified."},
 {"pthread_create",AMPOSIX_SUPPORT_INVESTIGATE,"threads","Requires an explicit, documented Amiga execution-model mapping."},
 {"fork",AMPOSIX_SUPPORT_ADAPT,"process","Prefer spawn-style adaptation; do not fake Unix fork semantics."},
 {"execvp",AMPOSIX_SUPPORT_ADAPT,"process",""}, {"mmap",AMPOSIX_SUPPORT_ADAPT,"memory",""},
 {"epoll_create",AMPOSIX_SUPPORT_UNSUPPORTED,"events",""}, {"epoll_wait",AMPOSIX_SUPPORT_UNSUPPORTED,"events",""},
 {"inotify_init",AMPOSIX_SUPPORT_UNSUPPORTED,"filesystem-events",""},
 {"lstat",AMPOSIX_SUPPORT_INVESTIGATE,"files","Verify libc behaviour and symlink semantics."},
 {"fstat",AMPOSIX_SUPPORT_INVESTIGATE,"files","Verify descriptor semantics."},
 {"access",AMPOSIX_SUPPORT_INVESTIGATE,"files","Permission semantics differ across platforms."},
 {"fcntl",AMPOSIX_SUPPORT_INVESTIGATE,"files","Command coverage must be mapped individually."},
 {"pipe",AMPOSIX_SUPPORT_INVESTIGATE,"ipc","Requires Amiga execution and stream semantics review."},
 {"dup",AMPOSIX_SUPPORT_INVESTIGATE,"files","Descriptor behaviour requires qualification."},
 {"dup2",AMPOSIX_SUPPORT_INVESTIGATE,"files","Descriptor behaviour requires qualification."},
 {"poll",AMPOSIX_SUPPORT_INVESTIGATE,"events","Determine native or compatibility implementation."},
 {"nanosleep",AMPOSIX_SUPPORT_LIBRARY,"time","Host backend implemented; AmigaOS timing semantics require qualification."},
 {"usleep",AMPOSIX_SUPPORT_INVESTIGATE,"time","Timing resolution requires qualification."},
 {"setenv",AMPOSIX_SUPPORT_LIBRARY,"environment","Host backend implemented; AmigaDOS backend still requires qualification."},
 {"unsetenv",AMPOSIX_SUPPORT_LIBRARY,"environment","Host backend implemented; AmigaDOS backend still requires qualification."},
 {"realpath",AMPOSIX_SUPPORT_INVESTIGATE,"paths","Amiga path semantics require explicit mapping."},
 {"symlink",AMPOSIX_SUPPORT_INVESTIGATE,"files","Filesystem support and semantics vary."},
 {"readlink",AMPOSIX_SUPPORT_INVESTIGATE,"files","Filesystem support and semantics vary."},
 {"kill",AMPOSIX_SUPPORT_ADAPT,"process","Unix signal/process semantics require source adaptation."},
 {"waitpid",AMPOSIX_SUPPORT_ADAPT,"process","Unix child-process semantics require source adaptation."},
 {"sigaction",AMPOSIX_SUPPORT_ADAPT,"signals","Unix signal semantics do not map directly to AmigaOS."},
 {"sigprocmask",AMPOSIX_SUPPORT_ADAPT,"signals","Unix signal-mask semantics do not map directly to AmigaOS."}
};
static const char *amposix_feature_support_name(enum amposix_support support)
{
 switch(support){
 case AMPOSIX_SUPPORT_NATIVE:return "native";
 case AMPOSIX_SUPPORT_HEADER:return "header";
 case AMPOSIX_SUPPORT_LIBRARY:return "library";
 case AMPOSIX_SUPPORT_ADAPT:return "adapt";
 case AMPOSIX_SUPPORT_UNSUPPORTED:return "unsupported";
 case AMPOSIX_SUPPORT_INVESTIGATE:return "investigate";
 default:return "unknown";
 }
}
#define AMPOSIX_FEATURE_COUNT (sizeof(amposix_features)/sizeof(amposix_features[0]))
#endif
