#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int contains(const char *s,const char *x){return strstr(s,x)!=NULL;}
int main(void){
 FILE *f=popen("./build/amposix scan tests/fixtures","r"); char b[16384]; size_t n;
 if(!f) return 1; n=fread(b,1,sizeof(b)-1,f); b[n]='\0';
 if(pclose(f)!=0) return 1;
 if(!contains(b,"sample.c:6: native        read")) return 2;
 if(!contains(b,"sample.c:9: adapt         fork")) return 3;
 if(!contains(b,"sample.c:10: adapt         mmap")) return 4;
 if(!contains(b,"nested/net.c:4: native        socket")) return 5;
 if(!contains(b,"Files scanned: 2")) return 6;
 puts("scanner test: PASS"); return 0;
}
