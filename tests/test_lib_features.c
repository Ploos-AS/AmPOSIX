#include <stdio.h>
#include <string.h>

#include <amposix/features.h>

int main(void)
{
    const struct amposix_capability *read_cap;
    const struct amposix_capability *fork_cap;

    if (strcmp(amposix_version_string(), "0.1.0") != 0)
        return 1;

    read_cap = amposix_capability_find("read");
    if (!read_cap || read_cap->support != AMPOSIX_SUPPORT_NATIVE)
        return 2;

    fork_cap = amposix_capability_find("fork");
    if (!fork_cap || fork_cap->support != AMPOSIX_SUPPORT_ADAPT)
        return 3;

    /*
     * A second lookup must not overwrite the first result.  This guards
     * against implementations that return one shared mutable scratch object.
     */
    if (strcmp(read_cap->name, "read") != 0 ||
        read_cap->support != AMPOSIX_SUPPORT_NATIVE)
        return 4;
    if (strcmp(fork_cap->name, "fork") != 0 ||
        fork_cap->support != AMPOSIX_SUPPORT_ADAPT)
        return 5;
    if (read_cap == fork_cap)
        return 6;

    if (!amposix_capability_find("epoll_wait") ||
        amposix_capability_find("epoll_wait")->support !=
            AMPOSIX_SUPPORT_UNSUPPORTED)
        return 7;

    if (amposix_capability_find("not_a_real_api") != NULL)
        return 8;
    if (amposix_capability_find(NULL) != NULL)
        return 9;

    if (strcmp(amposix_support_name(AMPOSIX_SUPPORT_INVESTIGATE),
               "investigate") != 0)
        return 10;

    puts("libamposix feature API: PASS");
    return 0;
}
