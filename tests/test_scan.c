#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int has(const char*s,const char*x){return strstr(s,x)!=NULL;}
int main(void){FILE*f=popen("./build/amposix scan tests/fixtures","r");char b[32768];size_t n;if(!f)return 1;n=fread(b,1,sizeof(b)-1,f);b[n]=0;if(pclose(f))return 1;
 if(!has(b,"sample.c:1: adapt         include:unistd.h"))return 2;
 if(!has(b,"sample.c:2: adapt         include:sys/mman.h"))return 3;
 if(!has(b,"sample.c:6: native        read"))return 4;
 if(!has(b,"sample.c:9: adapt         fork"))return 5;
 if(!has(b,"nested/net.c:1: native        include:sys/socket.h"))return 6;
 if(has(b,"false_positives.c:1:")||has(b,"false_positives.c:2:")||has(b,"false_positives.c:4:"))return 7;
 puts("scanner test: PASS");return 0;}
