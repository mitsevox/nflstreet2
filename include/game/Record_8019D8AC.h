#ifndef GAME_RECORD_8019D8AC_H
#define GAME_RECORD_8019D8AC_H
#include "game/fn_8019D800.h"
struct Record_8019D8AC {
    int mUnknown0;
    Pair_8019D800 mUnknown4;
    Pair_8019D800 mUnknownC;
    unsigned char *mpUnknown14;
};
extern "C" {
void fn_8019D83C(short *pOut, short *pIn, unsigned int count);
void fn_8019D8AC(int *pOut, short *pIn, int index, Record_8019D8AC *pContext);
}
#endif
