#include <stdio.h>
#include <string.h>
#include "feature_db.h"
#include "headers.h"
static int valid_class(const char*s){static const char*classes[]={"native","header","library","adapt","unsupported","investigate"};size_t i;for(i=0;i<sizeof(classes)/sizeof(classes[0]);i++)if(!strcmp(s,classes[i]))return 1;return 0;}
int main(void){size_t i,j;int errors=0;
 for(i=0;i<AMPOSIX_FEATURE_COUNT;i++){const struct amposix_feature*f=&amposix_features[i];if(!f->name[0]||!f->area[0]||!valid_class(f->class_name)){fprintf(stderr,"invalid feature entry %lu\n",(unsigned long)i);errors++;}for(j=i+1;j<AMPOSIX_FEATURE_COUNT;j++)if(!strcmp(f->name,amposix_features[j].name)){fprintf(stderr,"duplicate feature: %s\n",f->name);errors++;}}
 for(i=0;i<AMPOSIX_HEADER_COUNT;i++){const struct amposix_header*h=&amposix_headers[i];if(!h->name[0]||!valid_class(h->class_name)){fprintf(stderr,"invalid header entry %lu\n",(unsigned long)i);errors++;}for(j=i+1;j<AMPOSIX_HEADER_COUNT;j++)if(!strcmp(h->name,amposix_headers[j].name)){fprintf(stderr,"duplicate header: %s\n",h->name);errors++;}}
 if(errors)return 1;printf("database validation: PASS (%lu APIs, %lu headers)\n",(unsigned long)AMPOSIX_FEATURE_COUNT,(unsigned long)AMPOSIX_HEADER_COUNT);return 0;}
