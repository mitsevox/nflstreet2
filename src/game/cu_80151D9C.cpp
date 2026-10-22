#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"
#include "game/Object_80039F5C.h"
#include "game/fn_8009D990.h"

class Class_802A1DC8 : public Class_80297BF8 {
public:
    virtual void vfn_07();
    unsigned char mUnknown4;
};

class Class_802A1D58 : public Class_80297CE8 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A1D20 : public Class_80297AB8 {
public:
    virtual void vfn_03();
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

class Class_802A1C98 : public Class_80297C60 {
public:
    virtual void vfn_05();
};

class Class_802A1C30 : public Class_80297B90 {
public:
    virtual void vfn_06();
};

class Class_802A1E38 : public Class_802A56E8 {
public:
    virtual int vfn_01();
};

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[16];
    unsigned char mUnknown116;
    unsigned char mUnknown117;
    unsigned char mCount;
    unsigned char mUnknown119;
    int mUnknown120;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
};

struct Object_8015005C {
    Class_802A1DC8 mUnknown0;
    Class_802A1D58 mUnknown8;
    Class_802A1D20 mUnknown12;
    Class_802A1C98 mUnknown24;
    Class_802A1C30 mUnknown28;
    Class_802A1E38 mUnknown32;
    Table_8015005C *mpUnknown36;
};

class Class_802A2918 : public Class_80148A58 {
public:
    Object_8015005C *mpUnknown1C;
    unsigned int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
int fn_80151B20(Class_802A2918 *p);
void fn_8017D844(const char *pText);
char *fn_801C2EF0(char *pDest, const char *pSource, unsigned int count);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C3180(const char *pString);
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
Object_80039F5C *fn_8003AC84(int id);
void fn_80151CCC(Class_802A2918 *p, unsigned int index, unsigned char value);
void fn_801502B4(void *p);
void fn_801735D8(unsigned int mask);
void fn_8009D8CC(int index);
int fn_8009D9A8(int index);
void fn_8009D964(int index, int value);

void fn_80151D9C(Class_802A2918 *p)
{
    char text[83];
    char line[83];
    int over = 0;
    unsigned char sudden = 0;
    Table_8015005C *pTable;
    Object_80039F5C *pPlayer;
    unsigned int i;
    bool last;
    Class_802A1D20 *pState;
    Entry_8015005C *pEntries;
    Entry_8015005C *pRows;

    if ((p->mUnknown36 != 0 && fn_8009D990(1) == 0) ||
        (p->mUnknown32 != 0 &&
         p->mpUnknown1C->mpUnknown36->mEntries[0].mUnknown10 +
                 p->mpUnknown1C->mpUnknown36->mEntries[0].mUnknown8 * 2 >= p->mUnknown32)) {
        if (fn_80151B20(p)) {
            pTable = p->mpUnknown1C->mpUnknown36;
            if (pTable->mUnknown124 == 0) {
                pTable->mUnknown124 = 1;
                fn_8017D844("Sudden Death!");
            }
        } else {
            over = 1;
            pTable = p->mpUnknown1C->mpUnknown36;
            if (pTable->mUnknown124 != 0) {
                sudden = 1;
            }
            pTable->mUnknown124 = 0;
        }
    }
    if (!over) {
        return;
    }
    if (p->mUnknown40 == 0) {
        p->mpUnknown1C->mpUnknown36->mUnknown126 = sudden;
        fn_801502B4(&p->mpUnknown1C->mUnknown32);
        return;
    }
    fn_801C2EF0(text, "Starting next round.\n", sizeof(text));
    for (i = 3; i != 0; i--) {
        if (p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12[1] == 0) {
            pPlayer = fn_8003AC84(p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown0);
            fn_801C2D88(line, sizeof(line), "Eliminated %s %s.\n", pPlayer->mUnknown2927,
                        pPlayer->mUnknown2927 + 21);
            fn_801C2F88(text, line, sizeof(text) - fn_801C3180(text));
            pEntries = p->mpUnknown1C->mpUnknown36->mEntries;
            if (pEntries[i].mUnknown10 + pEntries[i].mUnknown8 * 2 !=
                pEntries[i - 1].mUnknown10 + pEntries[i - 1].mUnknown8 * 2) {
                break;
            }
        }
    }
    last = i == 1;
    for (; i <= 3; i++) {
        if (p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12[1] == 0) {
            fn_80151CCC(p, i, !last);
        }
    }
    if (last) {
        p->mpUnknown1C->mpUnknown36->mUnknown126 = sudden;
        fn_801502B4(&p->mpUnknown1C->mUnknown32);
        return;
    }
    fn_8017D844(text);
    for (i = 0; i < 4; i++) {
        pRows = p->mpUnknown1C->mpUnknown36->mEntries;
        if (pRows[i].mUnknown10 + pRows[i].mUnknown8 * 2 > pRows[i].mUnknown4) {
            pRows[i].mUnknown4 = pRows[i].mUnknown10 + pRows[i].mUnknown8 * 2;
        }
        pRows[i].mUnknown14 += pRows[i].mUnknown8;
        pRows[i].mUnknown16 += pRows[i].mUnknown10;
        pRows[i].mUnknown8 = 0;
        pRows[i].mUnknown10 = 0;
    }
    fn_801735D8(0x800);
    fn_8009D8CC(1);
    fn_8009D964(1, fn_8009D9A8(1));
    pState = &p->mpUnknown1C->mUnknown12;
    pState->mUnknown9 = 1;
    pState->mUnknown8 = 0;
}
}

extern "C" Table_8015005C *fn_801530FC(void);

extern "C" void fn_801502B4(void *p)
{
    for (unsigned int i = 0; i <= 3; i++) {
        Entry_8015005C *pEntry = &fn_801530FC()->mEntries[i];
        unsigned int score = pEntry->mUnknown10 + pEntry->mUnknown8 * 2;
        if (score > pEntry->mUnknown4) {
            pEntry->mUnknown4 = score;
        }
        pEntry->mUnknown14 += pEntry->mUnknown8;
        pEntry->mUnknown16 += pEntry->mUnknown10;
        pEntry->mUnknown10 = 0;
        pEntry->mUnknown8 = 0;
    }
    fn_801530FC()->mUnknown125 = 1;
}
