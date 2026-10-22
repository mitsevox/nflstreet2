#ifndef GAME_RECORD_8019D8AC_H
#define GAME_RECORD_8019D8AC_H
#include "game/fn_8019D800.h"
typedef struct Record_8019D8AC {
    int mUnknown0;
    struct Pair_8019D800 mUnknown4;
    struct Pair_8019D800 mUnknownC;
    unsigned char *mpUnknown14;
} Record_8019D8AC;
#ifdef __cplusplus
extern "C" {
#endif
void fn_8019D83C(short *pOut, short *pIn, unsigned int count);
void fn_8019D8AC(int *pOut, short *pIn, int index, Record_8019D8AC *pContext);
#ifdef __cplusplus
}
#endif
#endif
