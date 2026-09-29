/* AmigaOS platform backend contract.
 * This file is intentionally not part of the host build yet.
 * Implement only after the exact libc/AmigaDOS variable semantics are
 * qualified with the m68k toolchain and emulator runtime.
 */
#include <errno.h>
#include "../platform.h"
int amposix_platform_setenv(const char*name,const char*value,int overwrite){(void)name;(void)value;(void)overwrite;errno=ENOSYS;return -1;}
int amposix_platform_unsetenv(const char*name){(void)name;errno=ENOSYS;return -1;}
const char *amposix_platform_name(void){return "amigaos-unqualified";}

int amposix_platform_clock_gettime(int id,struct amposix_timespec*ts){(void)id;(void)ts;errno=ENOSYS;return -1;}
int amposix_platform_nanosleep(const struct amposix_timespec*r,struct amposix_timespec*o){(void)r;(void)o;errno=ENOSYS;return -1;}
