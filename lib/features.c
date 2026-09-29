#include <stddef.h>
#include <string.h>
#include <amposix/features.h>
#include "feature_db.h"
static enum amposix_support support_from_name(const char*s){
 if(!strcmp(s,"native"))return AMPOSIX_SUPPORT_NATIVE;if(!strcmp(s,"header"))return AMPOSIX_SUPPORT_HEADER;
 if(!strcmp(s,"library"))return AMPOSIX_SUPPORT_LIBRARY;if(!strcmp(s,"adapt"))return AMPOSIX_SUPPORT_ADAPT;
 if(!strcmp(s,"unsupported"))return AMPOSIX_SUPPORT_UNSUPPORTED;if(!strcmp(s,"investigate"))return AMPOSIX_SUPPORT_INVESTIGATE;
 return AMPOSIX_SUPPORT_UNKNOWN;
}
const char *amposix_version_string(void){return "0.1.0";}
const char *amposix_support_name(enum amposix_support s){
 switch(s){case AMPOSIX_SUPPORT_NATIVE:return "native";case AMPOSIX_SUPPORT_HEADER:return "header";case AMPOSIX_SUPPORT_LIBRARY:return "library";case AMPOSIX_SUPPORT_ADAPT:return "adapt";case AMPOSIX_SUPPORT_UNSUPPORTED:return "unsupported";case AMPOSIX_SUPPORT_INVESTIGATE:return "investigate";default:return "unknown";}
}
const struct amposix_capability *amposix_capability_find(const char *name){
 static struct amposix_capability out;size_t i;if(!name)return NULL;
 for(i=0;i<AMPOSIX_FEATURE_COUNT;i++)if(!strcmp(name,amposix_features[i].name)){out.name=amposix_features[i].name;out.support=support_from_name(amposix_features[i].class_name);out.area=amposix_features[i].area;out.note=amposix_features[i].note;return &out;}return NULL;
}
