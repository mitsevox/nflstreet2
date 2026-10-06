#ifndef GAME_CU_800314E0_H
#define GAME_CU_800314E0_H

/* 168-byte entry allocated through fn_801D2B7C and kept in lbl_80306620. */
struct Entry_80306620 {
    char mName[132];
    char mText[32];
    int mUnknown164;
};

extern "C" {
void fn_80031C28(void);
void fn_80031DC8(void);
void fn_80031EFC(void);
unsigned int fn_8003203C(void);
void fn_80032044(int index, Entry_80306620 *pEntry);
void fn_800320B0(void);
int fn_80032110(Entry_80306620 *pEntry);
}

#endif
