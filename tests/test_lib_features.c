#include <stdio.h>
#include <string.h>
#include <amposix/features.h>
int main(void){const struct amposix_capability*f;
 if(strcmp(amposix_version_string(),"0.1.0"))return 1;
 f=amposix_capability_find("read");if(!f||f->support!=AMPOSIX_SUPPORT_NATIVE)return 2;
 f=amposix_capability_find("fork");if(!f||f->support!=AMPOSIX_SUPPORT_ADAPT)return 3;
 f=amposix_capability_find("epoll_wait");if(!f||f->support!=AMPOSIX_SUPPORT_UNSUPPORTED)return 4;
 if(amposix_capability_find("not_a_real_api")!=0)return 5;
 if(strcmp(amposix_support_name(AMPOSIX_SUPPORT_INVESTIGATE),"investigate"))return 6;
 puts("libamposix feature API: PASS");return 0;}
