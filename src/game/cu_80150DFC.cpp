#include "game/Class_80297AB8.h"
#include "game/Object_80039F5C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[17];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

class Class_802A1D20 : public Class_80297AB8 {
public:
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

extern "C" {
Table_8015005C *fn_801530FC(void);
Object_80039F5C *fn_8003AC84(int id);
char *fn_801C2EF0(char *pDest, const char *pSource, unsigned int count);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
void fn_8017E17C(int slot, const char *pText0, const char *pText1, const char *pText2, int key);
extern const char lbl_802A0DDC[];
extern const char lbl_802A05C8[];

void fn_80150DFC(Class_802A1D20 *p)
{
    p->Class_80297AB8::vfn_05();
}

// Clear eliminated players' rows; show each remaining player's current round total.
void RefreshFourPlayerScoreRows(Class_802A1D20 *p)
{
    for (unsigned char i = 0; i <= 3; i++) {
        if (fn_801530FC()->mEntries[i].mUnknown13 == 0) {
            char score[16];
            char name[20];
            fn_801C2EF0(name, fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0)->mUnknown2927 + 21, sizeof(name));
            Entry_8015005C *pEntries = fn_801530FC()->mEntries;
            fn_801C2D88(score, sizeof(score), lbl_802A0DDC,
                        pEntries[i].mUnknown10 + pEntries[i].mUnknown8 * 2);
            fn_8017E17C(i + 1, name, score, lbl_802A05C8, fn_801530FC()->mEntries[i].mUnknown12);
        } else {
            fn_8017E17C(i + 1, lbl_802A05C8, lbl_802A05C8, lbl_802A05C8, 255);
        }
    }
}
}
