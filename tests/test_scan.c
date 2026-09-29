#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int has(const char*s,const char*x){return strstr(s,x)!=NULL;}
static int run(const char*cmd,char*b,size_t cap){FILE*f=popen(cmd,"r");size_t n;if(!f)return 1;n=fread(b,1,cap-1,f);b[n]=0;return pclose(f)!=0;}
int main(void){char b[65536];
 if(run("./build/amposix scan tests/fixtures",b,sizeof(b)))return 1;
 if(!has(b,"sample.c:1: adapt         include:unistd.h"))return 2;
 if(!has(b,"sample.c:6: native        read"))return 3;
 if(has(b,"false_positives.c:1:")||has(b,"false_positives.c:2:"))return 4;
 if(run("./build/amposix scan --format=json tests/fixtures",b,sizeof(b)))return 5;
 if(!has(b,"\"schema\": 1"))return 6;
 if(!has(b,"\"kind\":\"call\""))return 7;
 if(!has(b,"\"name\":\"fork\""))return 8;
 if(!has(b,"\"class\":\"adapt\""))return 9;
 if(!has(b,"\"kind\":\"include\""))return 10;
 if(!has(b,"\"files_scanned\": 3"))return 11;
 puts("scanner test: PASS");return 0;}
