#ifndef AMPOSIX_FEATURES_PUBLIC_H
#define AMPOSIX_FEATURES_PUBLIC_H
#ifdef __cplusplus
extern "C" {
#endif
#define AMPOSIX_VERSION_MAJOR 0
#define AMPOSIX_VERSION_MINOR 1
#define AMPOSIX_VERSION_PATCH 0
enum amposix_support {
 AMPOSIX_SUPPORT_UNKNOWN=0,
 AMPOSIX_SUPPORT_NATIVE,
 AMPOSIX_SUPPORT_HEADER,
 AMPOSIX_SUPPORT_LIBRARY,
 AMPOSIX_SUPPORT_ADAPT,
 AMPOSIX_SUPPORT_UNSUPPORTED,
 AMPOSIX_SUPPORT_INVESTIGATE
};
struct amposix_capability {
 const char *name;
 enum amposix_support support;
 const char *area;
 const char *note;
};
const char *amposix_version_string(void);
const struct amposix_capability *amposix_capability_find(const char *name);
const char *amposix_support_name(enum amposix_support support);
#ifdef __cplusplus
}
#endif
#endif
