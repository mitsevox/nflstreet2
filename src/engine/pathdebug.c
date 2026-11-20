/* PATH debug output (pathdebug.c): the music library's printf, whose output is compiled out of this
   release, so it returns without printing. */

#include "engine/pathlib.h"

extern "C" void PATHI_printf(const char *format, ...)
{
    // FAKEMATCH: unused string local; emits the unreferenced "%s  %s" that starts the target .rodata
    const char *header = "%s  %s";
}
