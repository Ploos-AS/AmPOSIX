#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/env.h>
int main(void){const char*k="AMPOSIX_TEST_ENV";
 if(amposix_unsetenv(k))return 1;
 if(amposix_setenv(k,"one",1))return 2;if(!getenv(k)||strcmp(getenv(k),"one"))return 3;
 if(amposix_setenv(k,"two",0))return 4;if(strcmp(getenv(k),"one"))return 5;
 if(amposix_setenv(k,"two",1))return 6;if(strcmp(getenv(k),"two"))return 7;
 errno=0;if(amposix_setenv("BAD=NAME","x",1)!=-1||errno!=EINVAL)return 8;
 errno=0;if(amposix_unsetenv("")!=-1||errno!=EINVAL)return 9;
 if(amposix_unsetenv(k))return 10;if(getenv(k)!=NULL)return 11;
 puts("libamposix environment compatibility: PASS");return 0;}
