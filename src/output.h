#ifndef AMPOSIX_OUTPUT_H
#define AMPOSIX_OUTPUT_H
struct amposix_finding {
 const char *file; unsigned long line; const char *kind; const char *name;
 const char *class_name; const char *area; const char *note;
};
enum amposix_output_format { AMPOSIX_OUTPUT_TEXT, AMPOSIX_OUTPUT_JSON };
void amposix_output_begin(enum amposix_output_format format);
void amposix_output_finding(enum amposix_output_format format,const struct amposix_finding *f);
void amposix_output_end(enum amposix_output_format format,int files,int findings);
#endif
