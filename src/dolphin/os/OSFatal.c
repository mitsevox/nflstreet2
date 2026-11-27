/* OSFatal.c, the os library's fatal-error screen. None of its functions is in this
   executable (OSFatal and its helpers were not linked); its two statics remain in .bss. */

#include <dolphin/os.h>

typedef struct OSFatalParam {
    GXColor fg;
    GXColor bg;
    const char* msg;
} OSFatalParam;

static OSFatalParam FatalParam;
static OSContext FatalContext;
