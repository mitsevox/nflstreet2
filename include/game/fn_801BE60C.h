#ifndef GAME_FN_801BE60C_H
#define GAME_FN_801BE60C_H

struct Block_801BE60C;

/* Calls on the collection of four 100-byte records whose halfword +4 is the
   key (fn_801BE60C compares it with lhz 4 and returns the record + 16 or
   null; fn_801BE648 returns the halfword +4 of the record whose halfword +6
   is 3, or 0xFFFF). */
extern "C" {
int fn_801BE068(void *pA, void *pB, void *pC, unsigned short key, void *p, float value);
Block_801BE60C *fn_801BE60C(void *p, unsigned short key);
unsigned short fn_801BE648(void *p);
void fn_801BE760(void *p, unsigned short key, int a);
}

#endif
