#include <unistd.h>
#include <sys/mman.h>

int main(void) {
    char buf[8];
    read(0, buf, sizeof buf);
    write(1, buf, sizeof buf);
    /* Deliberately difficult POSIX semantics for scanner coverage. */
    if (fork() == 0) return 0;
    mmap(0, 4096, 0, 0, -1, 0);
    return 0;
}
