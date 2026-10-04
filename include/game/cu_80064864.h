#ifndef GAME_CU_80064864_H
#define GAME_CU_80064864_H

typedef int (*Callback_803EA638)(unsigned short *pA, unsigned short *pB, int *pC);

extern "C" {
void fn_80064864(void);
void fn_800648C4(void);
void fn_80064908(void);
int fn_80064970(void);
void fn_8006498C(void);
void fn_800649AC(void);
int fn_80064B94(void);
int fn_80064BF8(void);
void fn_80064CCC(void);
void fn_80064CD0(void);
void fn_80064CD4(void);
void fn_80064DC0(int index, Callback_803EA638 pCallback);
void fn_80064DD0(int index);
void fn_80064E18(void);
void fn_80064EA4(void);
void fn_80064EFC(unsigned short a, unsigned short b, int c);
void fn_80064F58(unsigned short a, unsigned short b, int c, unsigned int count, int *pArgs, int keep);
void fn_80065194(void);
void fn_800652A8(void);
void fn_800652DC(void);
void fn_800655B8(void);
void fn_800655D0(void);
void fn_800655E8(void);
int fn_800655F8(void);
int fn_8006560C(void);
int fn_8006562C(void);
void fn_80065638(void);
void fn_8006563C(void);
int fn_80065650(void);
unsigned char fn_8006565C(void);
void fn_80065664(unsigned char value);
unsigned char fn_8006569C(void);
void fn_800656A4(unsigned char value);
void fn_800656AC(unsigned char value);
void fn_800656E4(int value);
}

#endif
