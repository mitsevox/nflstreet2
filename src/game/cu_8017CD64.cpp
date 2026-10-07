#include <string.h>
#include "game/fn_80238174.h"

/* One of the six 0x90-byte entries of Set_8017CDD4. */
struct Entry_8017CDD4 {
    unsigned char mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mText[2][64];
};

/* Allocated through fn_80238174 under the id 'bnnr' (fn_8017CDD4). */
struct Set_8017CDD4 {
    Entry_8017CDD4 mEntries[6];
};

extern "C" {
void *fn_8023816C(void *pHandle);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static Set_8017CDD4 *lbl_803ECB38;
static unsigned int lbl_803EB460 = 1;

extern "C" {

void fn_8017CFB4(int index);

int fn_8017CD64(void *p, void *q)
{
    Set_8017CDD4 *pA = (Set_8017CDD4 *)p;
    Set_8017CDD4 *pB = (Set_8017CDD4 *)q;
    int result = 0;
    unsigned int i;

    if (pB != 0) {
        /* Only the fields before the text are compared. */
        for (i = 0; i <= 5; i++) {
            result |= fn_80238258(&pA->mEntries[i], &pB->mEntries[i], 16);
        }
    } else {
        return 0;
    }
    return result;
}

void fn_8017CDD4(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803ECB38, sizeof(Set_8017CDD4), 0, 0x626E6E72);
    Set_8017CDD4 *pSet;
    unsigned int i;
    unsigned int j;

    fn_80238234(pHandle, 0, 0, 0, fn_8017CD64);
    pSet = (Set_8017CDD4 *)fn_8023816C(pHandle);
    for (i = 0; i <= 5; i++) {
        pSet->mEntries[i].mUnknown0 = 0;
        pSet->mEntries[i].mUnknown2 = 0;
        pSet->mEntries[i].mUnknown4 = 0;
        pSet->mEntries[i].mUnknown8 = 0.0f;
        pSet->mEntries[i].mUnknownC = 0.0f;
        for (j = 0; j <= 1; j++) {
            strcpy(pSet->mEntries[i].mText[j], "");
        }
    }
    fn_802381E0(pHandle);
}

void fn_8017CEB0(void)
{
    fn_8017CFB4(7);
}

void fn_8017CED4(unsigned int value)
{
    lbl_803EB460 = value;
}

int fn_8017CEDC(float step)
{
    int i;

    for (i = 0; i <= 5; i++) {
        if (lbl_803ECB38->mEntries[i].mUnknown0 && lbl_803ECB38->mEntries[i].mUnknown8 != 0.0f) {
            lbl_803ECB38->mEntries[i].mUnknownC += step;
            if (lbl_803ECB38->mEntries[i].mUnknownC > lbl_803ECB38->mEntries[i].mUnknown8) {
                fn_8017CFB4(i);
                if (i == 3 && lbl_803ECB38->mEntries[5].mUnknown8 != 0.0f) {
                    fn_8017CFB4(5);
                    lbl_803ECB38->mEntries[5].mUnknown0 = 1;
                }
            }
        }
    }
    return 0;
}

void fn_8017CFAC(void)
{
}

void fn_8017CFB0(unsigned short, unsigned short, int, int)
{
}

void fn_8017CFB4(int index)
{
    int i;
    int j;

    if (index == 7) {
        for (i = 0; i <= 5; i++) {
            fn_8017CFB4(i);
        }
    } else if (lbl_803ECB38->mEntries[index].mUnknown0) {
        for (j = 0; j < 2; j++) {
            strcpy(lbl_803ECB38->mEntries[index].mText[j], "");
        }
        lbl_803ECB38->mEntries[index].mUnknown0 = 0;
        lbl_803ECB38->mEntries[index].mUnknown8 = 0.0f;
    }
}

int fn_8017D064(int index)
{
    int result = 0;
    int i;

    if (index == 7) {
        for (i = 0; i < 6; i++) {
            result |= lbl_803ECB38->mEntries[i].mUnknown0;
        }
    } else {
        result = lbl_803ECB38->mEntries[index].mUnknown0;
    }
    return result;
}

void fn_8017D0A4(int index, int line, const char *pText)
{
    strcpy(lbl_803ECB38->mEntries[index].mText[line], pText);
}

}
