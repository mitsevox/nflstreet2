/* Runtime support for variable argument lists: va_arg in <stdarg.h> calls __va_arg to fetch the
   address of the next argument of a given kind (word, double word, float, or vector) from the
   registers saved at entry or from the stack. Part of the C runtime linked into the game; no code
   in this build calls it. */
#include <stdarg.h>

void *__va_arg(va_list list, unsigned char type)
{
    char *addr;
    char *reg = &list->gpr;
    int g_reg = list->gpr;
    int maxsize = 8;
    int size = 4;
    int increment = 1;
    int even = 0;
    int fpr_offset = 0;
    int regsize = 4;

    if (type == 4) {
        addr = (char *)(((unsigned long)list->input_arg_area + 15) & ~15);
        list->input_arg_area = addr + 16;
        return addr;
    }
    if (type == 3) {
        reg = &list->fpr;
        g_reg = list->fpr;
        size = 8;
        fpr_offset = 32;
        regsize = 8;
    }
    if (type == 2) {
        size = 8;
        maxsize--;
        if (g_reg & 1)
            even = 1;
        increment = 2;
    }
    if (g_reg < maxsize) {
        g_reg += even;
        addr = list->reg_save_area + fpr_offset + g_reg * regsize;
        *reg = g_reg + increment;
    } else {
        *reg = 8;
        addr = list->input_arg_area;
        addr = (char *)(((unsigned long)addr + (size - 1)) & ~(size - 1));
        list->input_arg_area = addr + size;
    }
    if (type == 0)
        addr = *(char **)addr;
    return addr;
}
