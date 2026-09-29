#include <stdio.h>
#include <string.h>
#include "output.h"
static int first_json=1;
static void json_string(const char*s){unsigned char c;putchar('"');while((c=(unsigned char)*s++)!=0){if(c=='"'||c=='\\'){putchar('\\');putchar(c);}else if(c=='\n')fputs("\\n",stdout);else if(c=='\r')fputs("\\r",stdout);else if(c=='\t')fputs("\\t",stdout);else if(c<32)printf("\\u%04x",(unsigned)c);else putchar(c);}putchar('"');}
void amposix_output_begin(enum amposix_output_format format){first_json=1;if(format==AMPOSIX_OUTPUT_JSON)fputs("{\n  \"schema\": 1,\n  \"findings\": [\n",stdout);else puts("AmPOSIX portability report\n==========================");}
void amposix_output_finding(enum amposix_output_format format,const struct amposix_finding*f){
 if(format==AMPOSIX_OUTPUT_JSON){if(!first_json)fputs(",\n",stdout);first_json=0;fputs("    {\"file\":",stdout);json_string(f->file);printf(",\"line\":%lu,\"kind\":",f->line);json_string(f->kind);fputs(",\"name\":",stdout);json_string(f->name);fputs(",\"class\":",stdout);json_string(f->class_name);fputs(",\"area\":",stdout);json_string(f->area);fputs(",\"note\":",stdout);json_string(f->note);putchar('}');}
 else {printf("%s:%lu: %-13s ",f->file,f->line,f->class_name);if(!strcmp(f->kind,"include"))printf("include:%-10s",f->name);else printf("%-18s",f->name);printf(" [%s]",f->area);if(f->note[0])printf(" - %s",f->note);putchar('\n');}
}
void amposix_output_end(enum amposix_output_format format,int files,int findings){if(format==AMPOSIX_OUTPUT_JSON)printf("\n  ],\n  \"files_scanned\": %d,\n  \"finding_count\": %d\n}\n",files,findings);else printf("\nFiles scanned: %d\nFindings: %d\n",files,findings);}
