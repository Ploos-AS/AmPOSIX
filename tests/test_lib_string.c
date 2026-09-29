#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/string.h>
int main(void){char*p;char b[8];size_t n;
 p=amposix_strdup("hello");if(!p||strcmp(p,"hello"))return 1;free(p);
 p=amposix_strndup("abcdef",3);if(!p||strcmp(p,"abc"))return 2;free(p);
 memset(b,'X',sizeof(b));n=amposix_strlcpy(b,"abcdefghi",sizeof(b));if(n!=9||strcmp(b,"abcdefg"))return 3;
 strcpy(b,"ab");n=amposix_strlcat(b,"cdefghijk",sizeof(b));if(n!=11||strcmp(b,"abcdefg"))return 4;
 b[0]=0;n=amposix_strlcpy(b,"x",0);if(n!=1)return 5;
 puts("libamposix string compatibility: PASS");return 0;}
