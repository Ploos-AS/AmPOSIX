#include <stdlib.h>
#include <string.h>
#include <amposix/string.h>
char *amposix_strdup(const char*s){size_t n;char*p;if(!s)return NULL;n=strlen(s)+1;p=(char*)malloc(n);if(p)memcpy(p,s,n);return p;}
char *amposix_strndup(const char*s,size_t maxlen){size_t n=0;char*p;if(!s)return NULL;while(n<maxlen&&s[n])n++;p=(char*)malloc(n+1);if(!p)return NULL;if(n)memcpy(p,s,n);p[n]=0;return p;}
size_t amposix_strlcpy(char*dst,const char*src,size_t size){size_t n=strlen(src);if(size){size_t c=n>=size?size-1:n;if(c)memcpy(dst,src,c);dst[c]=0;}return n;}
size_t amposix_strlcat(char*dst,const char*src,size_t size){size_t d=0,s=strlen(src),c;while(d<size&&dst[d])d++;if(d==size)return size+s;c=size-d-1;if(c){if(s<c)c=s;memcpy(dst+d,src,c);dst[d+c]=0;}return d+s;}
