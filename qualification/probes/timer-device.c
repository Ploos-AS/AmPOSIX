#include <string.h>
#include <exec/types.h>
#include <exec/io.h>
#include <devices/timer.h>
#include <proto/exec.h>

int main(void)
{
    struct timerequest tr;
    memset(&tr, 0, sizeof(tr));
    if (OpenDevice(TIMERNAME, UNIT_ECLOCK, (struct IORequest *)&tr, 0) == 0)
        CloseDevice((struct IORequest *)&tr);
    return 0;
}
