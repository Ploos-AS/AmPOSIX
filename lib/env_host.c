#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/env.h>
#if !defined(_WIN32)
extern int setenv(const char *,const char *,int);
extern int unsetenv(const char *);
#endif
static int valid_name(const char*n){return n&&*n&&!strchr(n,'=');}
int amposix_setenv(const char*name,const char*value,int overwrite){
 if(!valid_name(name)||!value){errno=EINVAL;return -1;}
#if defined(_WIN32)
 (void)overwrite; errno=ENOSYS; return -1;
#else
 return setenv(name,value,overwrite);
#endif
}
int amposix_unsetenv(const char*name){
 if(!valid_name(name)){errno=EINVAL;return -1;}
#if defined(_WIN32)
 errno=ENOSYS; return -1;
#else
 return unsetenv(name);
#endif
}
