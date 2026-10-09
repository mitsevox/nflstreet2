#include <string.h>
#include "game/fn_80191804.h"

extern "C" {

void fn_8017F49C(int value, char *pOut, int size);

void fn_80191804(int a, int b, float c)
{
}

void fn_80191808(void)
{
}

void fn_8019180C(void)
{
}

int fn_80191810(int value)
{
    switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        return 1;
    case 7:
        return 3;
    case 8:
        return 2;
    case 0:
        return 0;
    }
    return 0;
}

/* Writes a byte count as a number of 8 KB blocks, rounded up, followed by
   " block" or " blocks" and pText when one is given; a negative count
   writes a blank. */
void fn_80191868(int value, char *pOut, int size, int unused, const char *pText)
{
    int blocks;

    if (value < 0) {
        strcpy(pOut, " ");
        return;
    }
    blocks = (value & 0x1FFF) ? 1 : 0;
    blocks += value >> 13;
    if (pText) {
        fn_8017F49C(blocks, pOut, size);
        if (blocks == 1) {
            strcat(pOut, " block ");
        } else {
            strcat(pOut, " blocks ");
        }
        strcat(pOut, pText);
    } else {
        fn_8017F49C(blocks, pOut, size);
        if (blocks == 1) {
            strcat(pOut, " block");
        } else {
            strcat(pOut, " blocks");
        }
    }
}
}
