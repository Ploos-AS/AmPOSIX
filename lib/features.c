#include <stddef.h>
#include <string.h>

#include <amposix/features.h>
#include "feature_db.h"

const char *amposix_version_string(void)
{
    return "0.1.0";
}

const char *amposix_support_name(enum amposix_support support)
{
    switch (support) {
    case AMPOSIX_SUPPORT_NATIVE: return "native";
    case AMPOSIX_SUPPORT_HEADER: return "header";
    case AMPOSIX_SUPPORT_LIBRARY: return "library";
    case AMPOSIX_SUPPORT_ADAPT: return "adapt";
    case AMPOSIX_SUPPORT_UNSUPPORTED: return "unsupported";
    case AMPOSIX_SUPPORT_INVESTIGATE: return "investigate";
    default: return "unknown";
    }
}

const struct amposix_capability *amposix_capability_find(const char *name)
{
    size_t i;

    if (!name)
        return NULL;

    for (i = 0; i < AMPOSIX_FEATURE_COUNT; ++i) {
        if (strcmp(name, amposix_features[i].name) == 0)
            return (const struct amposix_capability *)&amposix_features[i];
    }

    return NULL;
}
