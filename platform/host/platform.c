#include <errno.h>
#include <stdlib.h>
#include "platform.h"
#if !defined(_WIN32)
extern int setenv(const char *,const char *,int);
extern int unsetenv(const char *);
#endif
int amposix_platform_setenv(const char*name,const char*value,int overwrite){
#if defined(_WIN32)
 (void)name;(void)value;(void)overwrite;errno=ENOSYS;return -1;
#else
 return setenv(name,value,overwrite);
#endif
}
int amposix_platform_unsetenv(const char*name){
#if defined(_WIN32)
 (void)name;errno=ENOSYS;return -1;
#else
 return unsetenv(name);
#endif
}
const char *amposix_platform_name(void){return "host";}
