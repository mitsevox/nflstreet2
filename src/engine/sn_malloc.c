/* SN runtime allocation stubs (sn_malloc.c): the C library's own malloc, free, realloc and calloc
   entries, kept only to stop the game with a library-error panic that names the calling address when
   anything calls them directly. Only malloc is called; the linker discards the other three. */

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

void free(void *ptr)
{
    char *caller;

    asm volatile("mflr %0" : "=r"(caller));
    OSPanic(0, 0,
            "\n*** Library error ***\nAn external call has been made to 'free'\nCalling function address: 0x%X\n"
            "Please See the ProDG manual\n",
            caller - 4);
}

void *realloc(void *ptr, size_t size)
{
    char *caller;

    asm volatile("mflr %0" : "=r"(caller));
    OSPanic(0, 0,
            "\n*** Library error ***\nAn external call has been made to 'realloc'\nCalling function address: 0x%X\n"
            "Please See the ProDG manual\n",
            caller - 4);
}

void *calloc(size_t count, size_t size)
{
    char *caller;

    asm volatile("mflr %0" : "=r"(caller));
    OSPanic(0, 0,
            "\n*** Library error ***\nAn external call has been made to 'calloc'\nCalling function address: 0x%X\n"
            "Please See the ProDG manual\n",
            caller - 4);
}
