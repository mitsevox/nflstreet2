/* SN runtime malloc stub (sn_malloc.c): the C library's own allocation entry, kept only to stop the game
   with a library-error panic that names the calling address when anything calls malloc directly. */

#include <dolphin/os.h>
#include <stddef.h>

void *malloc(size_t size)
{
    char *caller;

    asm volatile("mflr %0" : "=r"(caller));
    OSPanic(0, 0,
            "\n*** Library error ***\nAn external call has been made to 'malloc'\nCalling function address: 0x%X\n"
            "Please See the ProDG manual\n",
            caller - 4);
}
