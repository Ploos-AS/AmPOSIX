/* AmPOSIX portability scanner -- C-first, conservative lexical analysis. */
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "feature_db.h"
#include "headers.h"
#include "output.h"

static enum amposix_output_format output_format=AMPOSIX_OUTPUT_TEXT;

static int total_findings, total_files;
static int ident(int c){return isalnum((unsigned char)c)||c=='_';}
static int source_name(const char *p){const char *d=strrchr(p,'.');return d&&(!strcmp(d,".c")||!strcmp(d,".h")||!strcmp(d,".cc")||!strcmp(d,".cpp")||!strcmp(d,".cxx")||!strcmp(d,".hpp"));}

/* Strip comments and quoted literals while preserving character positions/newlines. */
static void sanitize(char *s){
 int block=0,line=0,str=0,chr=0,esc=0; size_t i;
 for(i=0;s[i];i++){
  char c=s[i],n=s[i+1];
  if(line){if(c=='\n') line=0; else s[i]=' '; continue;}
  if(block){if(c=='*'&&n=='/'){s[i]=s[i+1]=' ';i++;block=0;}else if(c!='\n')s[i]=' ';continue;}
  if(str||chr){
   if(c=='\n'){str=chr=esc=0;continue;}
   if(esc){s[i]=' ';esc=0;continue;}
   if(c=='\\'){s[i]=' ';esc=1;continue;}
   if((str&&c=='"')||(chr&&c=='\'')){s[i]=' ';str=chr=0;}else s[i]=' ';
   continue;
  }
  if(c=='/'&&n=='/'){s[i]=s[i+1]=' ';i++;line=1;continue;}
  if(c=='/'&&n=='*'){s[i]=s[i+1]=' ';i++;block=1;continue;}
  if(c=='"'){s[i]=' ';str=1;continue;} if(c=='\''){s[i]=' ';chr=1;continue;}
 }
}
static unsigned long line_of(const char *base,const char *p){unsigned long n=1;while(base<p){if(*base++=='\n')n++;}return n;}
static int call_at(const char *base,const char *name,const char **hit){
 size_t n=strlen(name);const char *p=base;
 while((p=strstr(p,name))!=NULL){const char *q=p+n;if((p==base||!ident((unsigned char)p[-1]))&&!ident((unsigned char)*q)){while(*q&&isspace((unsigned char)*q))q++;if(*q=='('){*hit=p;return 1;}}p+=n;}return 0;
}
static char *read_all(const char *path){FILE *f=fopen(path,"rb");long n;char *b;if(!f)return NULL;if(fseek(f,0,SEEK_END)){fclose(f);return NULL;}n=ftell(f);if(n<0){fclose(f);return NULL;}rewind(f);b=(char*)malloc((size_t)n+1);if(!b){fclose(f);return NULL;}if(fread(b,1,(size_t)n,f)!=(size_t)n){free(b);fclose(f);return NULL;}b[n]=0;fclose(f);return b;}
static void scan_includes(const char *path,const char *original){
 const char *p=original; unsigned long ln=1;
 while(*p){const char *e=strchr(p,'\n');size_t len=e?(size_t)(e-p):strlen(p);const char *q=p;size_t i;
  while(q<p+len&&isspace((unsigned char)*q))q++;
  if(q<p+len&&*q=='#'){q++;while(q<p+len&&isspace((unsigned char)*q))q++;if((size_t)(p+len-q)>=7&&!strncmp(q,"include",7)){q+=7;while(q<p+len&&isspace((unsigned char)*q))q++;if(q<p+len&&(*q=='<'||*q=='"')){char end=*q=='<'?'>':'"';char name[256];size_t k=0;q++;while(q<p+len&&*q!=end&&k+1<sizeof(name))name[k++]=*q++;name[k]=0;for(i=0;i<AMPOSIX_HEADER_COUNT;i++)if(!strcmp(name,amposix_headers[i].name)){{struct amposix_finding f={path,ln,"include",name,amposix_headers[i].class_name,"header",amposix_headers[i].note};amposix_output_finding(output_format,&f);total_findings++;}}}}}
  if(!e)break;p=e+1;ln++;
 }
}
static int scan_file(const char *path){
 char *orig=read_all(path),*clean;size_t i;if(!orig){fprintf(stderr,"amposix: cannot read %s\n",path);return 1;}total_files++;scan_includes(path,orig);
 clean=(char*)malloc(strlen(orig)+1);if(!clean){free(orig);return 1;}strcpy(clean,orig);sanitize(clean);
 for(i=0;i<AMPOSIX_FEATURE_COUNT;i++){const char *p=clean,*hit;while(call_at(p,amposix_features[i].name,&hit)){const struct amposix_feature*x=&amposix_features[i];{struct amposix_finding f={path,line_of(clean,hit),"call",x->name,x->class_name,x->area,x->note};amposix_output_finding(output_format,&f);total_findings++;}p=hit+strlen(x->name);}}
 free(clean);free(orig);return 0;
}
static int join_path(char*out,size_t cap,const char*a,const char*b){int n=snprintf(out,cap,"%s/%s",a,b);return n<0||(size_t)n>=cap;}
static int scan_path(const char*path){struct stat st;if(stat(path,&st)!=0){fprintf(stderr,"amposix: cannot stat %s\n",path);return 1;}if(S_ISREG(st.st_mode))return source_name(path)?scan_file(path):0;if(S_ISDIR(st.st_mode)){DIR*d=opendir(path);struct dirent*e;int rc=0;if(!d)return 1;while((e=readdir(d))!=NULL){char child[4096];if(!strcmp(e->d_name,".")||!strcmp(e->d_name,"..")||!strcmp(e->d_name,".git")||!strcmp(e->d_name,"build"))continue;if(join_path(child,sizeof(child),path,e->d_name)){rc=1;continue;}if(scan_path(child))rc=1;}closedir(d);return rc;}return 0;}
int main(int argc,char**argv){
 int rc;const char *path;
 if(argc==3&&!strcmp(argv[1],"scan"))path=argv[2];
 else if(argc==4&&!strcmp(argv[1],"scan")&&!strcmp(argv[2],"--format=json")){output_format=AMPOSIX_OUTPUT_JSON;path=argv[3];}
 else {fprintf(stderr,"usage: amposix scan [--format=json] <source-file-or-directory>\n");return 2;}
 amposix_output_begin(output_format);rc=scan_path(path);amposix_output_end(output_format,total_files,total_findings);return rc;
}
