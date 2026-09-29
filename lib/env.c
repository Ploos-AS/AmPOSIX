#include <errno.h>
#include <string.h>
#include <amposix/env.h>
#include "platform.h"
static int valid_name(const char*n){return n&&*n&&!strchr(n,'=');}
int amposix_setenv(const char*name,const char*value,int overwrite){if(!valid_name(name)||!value){errno=EINVAL;return -1;}return amposix_platform_setenv(name,value,overwrite);}
int amposix_unsetenv(const char*name){if(!valid_name(name)){errno=EINVAL;return -1;}return amposix_platform_unsetenv(name);}
