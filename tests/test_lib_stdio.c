#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amposix/stdio.h>
int main(void){FILE*f;char *p=NULL;size_t n=0;amposix_ssize_t r;
 f=tmpfile();if(!f)return 1;fputs("alpha\nbeta",f);rewind(f);
 r=amposix_getline(&p,&n,f);if(r!=6||strcmp(p,"alpha\n"))return 2;
 r=amposix_getline(&p,&n,f);if(r!=4||strcmp(p,"beta"))return 3;
 if(amposix_getline(&p,&n,f)!=-1)return 4;free(p);fclose(f);
 f=tmpfile();if(!f)return 5;fputs("a:b",f);rewind(f);p=NULL;n=0;
 r=amposix_getdelim(&p,&n,':',f);if(r!=2||strcmp(p,"a:"))return 6;
 free(p);fclose(f);puts("libamposix stdio compatibility: PASS");return 0;}
