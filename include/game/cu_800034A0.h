#ifndef GAME_CU_800034A0_H
#define GAME_CU_800034A0_H

struct CardStreamTarget {
    unsigned int mChecksum;
    unsigned int mSize;
    unsigned int mPosition;
    unsigned char mFillToEnd;
};

extern "C" {
extern CardStreamTarget lbl_80367580;
extern void *lbl_803ECCA4;
extern int lbl_803EB8C8;
extern unsigned char lbl_803EB8D4;

void fn_800034A0(void);
void fn_800034D0(void);
void fn_800034FC(void);
void fn_80003620(void);
void fn_800037C0(int a, int *b);
int fn_800039E4(int a, int *b);
}

#endif
