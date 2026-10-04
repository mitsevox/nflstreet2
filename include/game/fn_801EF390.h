#ifndef GAME_FN_801EF390_H
#define GAME_FN_801EF390_H

/* Calls taking a data block pointer and an index below the halfword at
   pData +0x14; each returns an int. */
extern "C" {
int fn_801EF390(void *pData, int index, int a);
int fn_801F010C(void *pData, int index);
int fn_801F0DB8(void *pData, int index);
}

#endif
