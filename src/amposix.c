/* AmPOSIX portability scanner -- dependency-free C implementation. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "features.h"

static int ident(int c){ return isalnum((unsigned char)c) || c=='_'; }
static int call_seen(const char *s,const char *name){
 size_t n=strlen(name); const char *p=s;
 while((p=strstr(p,name))!=NULL){
  const char *q=p+n;
  if((p==s || !ident((unsigned char)p[-1])) && !ident((unsigned char)*q)){
   while(*q && isspace((unsigned char)*q)) q++;
   if(*q=='(') return 1;
  }
  p+=n;
 }
 return 0;
}
static char *read_all(const char *path){
 FILE *f=fopen(path,"rb"); long n; char *b;
 if(!f) return NULL; if(fseek(f,0,SEEK_END)!=0){fclose(f);return NULL;}
 n=ftell(f); if(n<0){fclose(f);return NULL;} rewind(f);
 b=(char*)malloc((size_t)n+1); if(!b){fclose(f);return NULL;}
 if(fread(b,1,(size_t)n,f)!=(size_t)n){free(b);fclose(f);return NULL;}
 b[n]='\0'; fclose(f); return b;
}
static int scan_file(const char *path){
 char *s=read_all(path); size_t i; int count=0;
 if(!s){fprintf(stderr,"amposix: cannot read %s\n",path);return 2;}
 printf("AmPOSIX portability report\n==========================\nSource: %s\n",path);
 for(i=0;i<AMPOSIX_FEATURE_COUNT;i++) if(call_seen(s,amposix_features[i].name)){
  const struct amposix_feature *f=&amposix_features[i]; count++;
  printf("%-13s %-18s [%s]",f->class_name,f->name,f->area);
  if(f->note[0]) printf(" - %s",f->note); putchar('\n');
 }
 printf("Known interfaces detected: %d\n",count); free(s); return 0;
}
static void usage(void){fprintf(stderr,"usage: amposix scan <source-file>\n");}
int main(int argc,char **argv){
 if(argc!=3 || strcmp(argv[1],"scan")!=0){usage();return 2;}
 return scan_file(argv[2]);
}
