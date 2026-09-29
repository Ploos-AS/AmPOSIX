/* AmPOSIX portability scanner -- C-first, with host traversal isolated here. */
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "features.h"

static int total_findings;
static int total_files;

static int ident(int c){ return isalnum((unsigned char)c) || c=='_'; }
static int source_name(const char *p){
 const char *d=strrchr(p,'.');
 return d && (!strcmp(d,".c")||!strcmp(d,".h")||!strcmp(d,".cc")||!strcmp(d,".cpp")||!strcmp(d,".cxx")||!strcmp(d,".hpp"));
}
static int call_at(const char *line,const char *name){
 size_t n=strlen(name); const char *p=line;
 while((p=strstr(p,name))!=NULL){
  const char *q=p+n;
  if((p==line || !ident((unsigned char)p[-1])) && !ident((unsigned char)*q)){
   while(*q && isspace((unsigned char)*q)) q++;
   if(*q=='(') return 1;
  }
  p+=n;
 }
 return 0;
}
static int scan_file(const char *path){
 FILE *f=fopen(path,"r"); char line[8192]; unsigned long lineno=0; size_t i;
 if(!f){fprintf(stderr,"amposix: cannot read %s\n",path);return 1;}
 total_files++;
 while(fgets(line,sizeof(line),f)){
  lineno++;
  for(i=0;i<AMPOSIX_FEATURE_COUNT;i++) if(call_at(line,amposix_features[i].name)){
   const struct amposix_feature *x=&amposix_features[i];
   printf("%s:%lu: %-13s %-18s [%s]",path,lineno,x->class_name,x->name,x->area);
   if(x->note[0]) printf(" - %s",x->note);
   putchar('\n'); total_findings++;
  }
 }
 fclose(f); return 0;
}
static int join_path(char *out,size_t cap,const char *a,const char *b){
 int n=snprintf(out,cap,"%s/%s",a,b); return n<0 || (size_t)n>=cap;
}
static int scan_path(const char *path){
 struct stat st;
 if(stat(path,&st)!=0){fprintf(stderr,"amposix: cannot stat %s\n",path);return 1;}
 if(S_ISREG(st.st_mode)) return source_name(path)?scan_file(path):0;
 if(S_ISDIR(st.st_mode)){
  DIR *d=opendir(path); struct dirent *e; int rc=0;
  if(!d){fprintf(stderr,"amposix: cannot open directory %s\n",path);return 1;}
  while((e=readdir(d))!=NULL){
   char child[4096];
   if(!strcmp(e->d_name,".")||!strcmp(e->d_name,"..")||!strcmp(e->d_name,".git")||!strcmp(e->d_name,"build")) continue;
   if(join_path(child,sizeof(child),path,e->d_name)){fprintf(stderr,"amposix: path too long under %s\n",path);rc=1;continue;}
   if(scan_path(child)!=0) rc=1;
  }
  closedir(d); return rc;
 }
 return 0;
}
static void usage(void){fprintf(stderr,"usage: amposix scan <source-file-or-directory>\n");}
int main(int argc,char **argv){
 int rc;
 if(argc!=3 || strcmp(argv[1],"scan")!=0){usage();return 2;}
 puts("AmPOSIX portability report\n==========================");
 rc=scan_path(argv[2]);
 printf("\nFiles scanned: %d\nFindings: %d\n",total_files,total_findings);
 return rc;
}
