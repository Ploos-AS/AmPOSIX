#include <stdio.h>
#include <string.h>

#include "feature_db.h"
#include "headers.h"

static int valid_support(enum amposix_support support)
{
    return support >= AMPOSIX_SUPPORT_NATIVE &&
           support <= AMPOSIX_SUPPORT_INVESTIGATE;
}

static int valid_class(const char *name)
{
    static const char *classes[] = {
        "native", "header", "library", "adapt", "unsupported", "investigate"
    };
    size_t i;

    for (i = 0; i < sizeof(classes) / sizeof(classes[0]); ++i)
        if (strcmp(name, classes[i]) == 0)
            return 1;
    return 0;
}

int main(void)
{
    size_t i, j;
    int errors = 0;

    for (i = 0; i < AMPOSIX_FEATURE_COUNT; ++i) {
        const struct amposix_feature *feature = &amposix_features[i];

        if (!feature->name[0] || !feature->area[0] ||
            !valid_support(feature->support)) {
            fprintf(stderr, "invalid feature entry %lu\n", (unsigned long)i);
            ++errors;
        }

        for (j = i + 1; j < AMPOSIX_FEATURE_COUNT; ++j) {
            if (strcmp(feature->name, amposix_features[j].name) == 0) {
                fprintf(stderr, "duplicate feature: %s\n", feature->name);
                ++errors;
            }
        }
    }

    for (i = 0; i < AMPOSIX_HEADER_COUNT; ++i) {
        const struct amposix_header *header = &amposix_headers[i];

        if (!header->name[0] || !valid_class(header->class_name)) {
            fprintf(stderr, "invalid header entry %lu\n", (unsigned long)i);
            ++errors;
        }

        for (j = i + 1; j < AMPOSIX_HEADER_COUNT; ++j) {
            if (strcmp(header->name, amposix_headers[j].name) == 0) {
                fprintf(stderr, "duplicate header: %s\n", header->name);
                ++errors;
            }
        }
    }

    if (errors)
        return 1;

    printf("database validation: PASS (%lu APIs, %lu headers)\n",
           (unsigned long)AMPOSIX_FEATURE_COUNT,
           (unsigned long)AMPOSIX_HEADER_COUNT);
    return 0;
}
