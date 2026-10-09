#ifndef GAME_CU_8003AEA8_H
#define GAME_CU_8003AEA8_H

/* src/game/cu_8003AEA8.cpp; fn_8003B6BC is declared in game/fn_8003B6BC.h. */

/* Passed by pointer; only the words at +4 and +8 are read. */
struct Pair_8003AEA8 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
void fn_8003B3F8(int group, int *list, int value);
void fn_8003B6F0(int reset);
void fn_8003B8BC(void);
void fn_8003AEF4(int a, int kind, int index, int d, Pair_8003AEA8 *p0, Pair_8003AEA8 *p1, Pair_8003AEA8 *p2);
void fn_8003AF8C(int a, int kind, int index, int key, int e, Pair_8003AEA8 *pPair, int *pValues, int *pResult);
}

#endif
