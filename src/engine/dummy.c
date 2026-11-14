/* SN Systems runtime console output (the SN runtime library's dummy.c): writes to the
   standard output and error descriptors go to the development kit's serial port. */

#include <dolphin/exi.h>
#include "engine/dummy.h"

extern int fn_801AC9C8(int fd, void *buf, int len);

int __sn_serialp(void *buf, int len)
{
    static int first = 1;

    if (first) {
        first = 0;
        InitializeUART(0);
    }
    WriteUARTN(buf, len);
    return len;
}

int _write(int fd, void *buf, int len)
{
    if (fd == 1 || fd == 2)
        return __sn_serialp(buf, len);
    if (fd == 0)
        return -1;
    return fn_801AC9C8(fd, buf, len);
}

int write(int fd, void *buf, int len)
{
    return _write(fd, buf, len);
}
