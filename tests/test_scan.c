#include <stdio.h>
#include <stdlib.h>
int main(void){
 FILE *f=popen("./build/amposix scan tests/fixtures/sample.c","r"); char b[4096]; size_t n;
 if(!f) return 1; n=fread(b,1,sizeof(b)-1,f); b[n]='\0';
 if(pclose(f)!=0) return 1;
 if(!strstr(b,"native        read") || !strstr(b,"adapt         fork") || !strstr(b,"adapt         mmap")) return 1;
 puts("scanner test: PASS"); return 0;
}
