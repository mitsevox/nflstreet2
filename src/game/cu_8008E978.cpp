#include <string.h>

#include "engine/vptmanager.h"
#include "game/Class_80148A58.h"
#include "game/Entry_80219044.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Object_80039F5C.h"
#include "game/RecordList_8002E7C0.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/fn_8007F828.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_80238174.h"
#include "game/fn_802372EC.h"

/* Data whose word +4 fn_80094374 returns and whose words from +8
   fn_80093BAC indexes; the bound of that array is not established. */
struct Table_80093BAC {
    unsigned char mUnknown0[4];
    int mUnknown4;
    Actor_801C009C *mpUnknown8[1];
};

/* One of the six 20-byte entries at +4 of Block_800925F0. */
struct Entry_80094238 {
    Table_80093BAC *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
};

/* The 3664 bytes at +128 of Block_800925F0 that fn_800920EC copies and
   fn_80092168 compares. */
struct Block_800920EC {
    Character_80093BCC mCharacters[4];
    short mUnknownE40[7];
    unsigned char mUnknownE4E;
    unsigned char mUnknownE4F[1];
};

/* Allocated through fn_80238174 under the id 'anms' (fn_800925F0). */
struct Block_800925F0 {
    unsigned char mUnknown0[4];
    Entry_80094238 mEntries[6];
    void *mpUnknown7C;
    Block_800920EC mUnknown80;
};

/* 16-byte records of the .data tables used by fn_80093E38, fn_80093E4C,
   fn_80093EC0 and fn_800940D8. */
struct Record_80093E4C {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8[4];
    unsigned char mUnknownC;
    unsigned char mUnknownD[3];
};

/* 16-byte records of the two-entry table cleared by fn_8009418C. */
struct Slot_8009418C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
};

/* 12-byte records of the .data table searched by fn_80093FD4. */
struct Record_80093FD4 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

/* 12-byte records returned by fn_80094490. */
struct Record_80094490 {
    unsigned char mUnknown0[12];
};

/* 14-byte block cleared by fn_80094B78. */
struct Header_80094B78 {
    unsigned char mUnknown0[2];
    short mUnknown2;
    unsigned char mUnknown4[10];
};

/* One of the ten 40-byte entries of the block fn_80094E80 allocates under
   the id 'anmm'. */
struct Entry_80094BC4 {
    void *mpUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    float mUnknown14;
    float mUnknown18;
    float mUnknown1C;
    void (*mpCallback20)(void *p);
    int mUnknown24;
};

/* Block allocated by fn_80096954 with fn_801D2B7C (112 bytes). */
struct Block_80096954 {
    Table_80093BAC *mpUnknown0[2];
    void *mpUnknown8;
    unsigned char mUnknownC[4];
    Playback_80096DA8 mUnknown10[2];
};

/* Two 8-byte records whose word +4 fn_80096D14 decrements. */
struct Slot_80096D14 {
    int mUnknown0;
    int mUnknown4;
};

/* 60-byte items of the array that Record_80097518 +3048 points to. */
struct Item_8009A63C {
    unsigned char mUnknown0[60];
};

/* 8-byte entries from +12 of Record_80097518; their bound is not
   established. */
struct Pair_8009A63C {
    Item_8009A63C *mpUnknown0;
    int mUnknown4;
};

/* 3080-byte records of the .bss array at 0x8030C2B8. */
struct Record_80097518 {
    unsigned char mUnknown0[12];
    Pair_8009A63C mUnknownC[1];
    unsigned char mUnknown14[3028];
    Item_8009A63C *mpUnknownBE8;
    unsigned char mUnknownBEC[28];
};

/* 12-byte block allocated by fn_8009AB34 under the id 'ctup'. */
struct Block_8009AB34 {
    float mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

/* 16-byte callback records copied into Block_8009B5E8 by fn_8009B87C. */
struct Entry_8009B87C {
    int (*mpCallback0)(int value, int *pData);
    int (*mpCallback4)(int *pData);
    void (*mpCallback8)(int *pData);
    int mUnknownC;
};

/* The 300 bytes at +4 of Block_8009B720 that fn_8009B698 copies and
   fn_8009B5E8 checks. */
struct Block_8009B5E8 {
    int mUnknown0;
    Entry_8009B87C mEntries[2];
    unsigned int mUnknown24;
    int mUnknown28[63];
    unsigned char mUnknown124[3];
    unsigned char mUnknown127;
    int mUnknown128;
};

/* Record passed to fn_8009D338-fn_8009D3F0. Only the accessed words are
   declared; the size is unknown. */
struct Timer_8009D338 {
    unsigned char mUnknown0[4];
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned char mUnknownC[4];
    unsigned int mUnknown10;
    int mUnknown14;
};

/* 304-byte blocks allocated by fn_8009B720 under the id 'celb'. */
struct Block_8009B720 {
    void *mpUnknown0;
    Block_8009B5E8 mUnknown4;
};

extern "C" {
int fn_80238278(const void *p, int size, int seed);
void fn_8015A0D0(int value);
void fn_8015C254(int a);
int fn_80092830(int handle);
float fn_80094454(int handle);
int fn_801BC044(int index);
int fn_801BC060(int index);
int fn_80094374(int index);
Object_80039F5C *fn_8003AD2C(int id);
int fn_801485D4(void);
int fn_80178AE0(void);
int fn_80025708(void);
int fn_80177F7C(void);
void fn_80093410(int handle);
void fn_80094BC4(Entry_80094BC4 *p);
int fn_80094C4C(Entry_80094BC4 *p);
void *fn_8023816C(void *pHandle);
int fn_8009B9BC(void);
void fn_8017CFB4(int index);

extern Block_800925F0 *lbl_803EC924;
extern unsigned char lbl_803EA8BC;
extern unsigned char lbl_803EA8BD;
extern unsigned char lbl_803EA8BE;
extern unsigned char lbl_803EA8BF;
extern unsigned char lbl_803EA8C0;
extern int lbl_803EA8C4;
extern unsigned char lbl_803EA8C8;
extern int lbl_803EA8CC;
extern unsigned char lbl_803EA8D4;
extern unsigned char lbl_803EA8D5;
extern unsigned char lbl_802D72BC[];
extern Record_80093E4C lbl_802D72D8[];
extern Record_80093E4C lbl_802D73B8[];
extern Record_80093E4C lbl_802D77D8[];
extern Record_80093E4C lbl_802D7808[];
extern int lbl_802D7974[5][5];
extern Record_80094490 lbl_8030C0B4[];
extern Slot_8009418C lbl_8030C164[2];
extern Record_80093FD4 lbl_802D78D8[];
extern unsigned int lbl_802D79D8[];
extern int lbl_803EC928;
extern Entry_80094BC4 *lbl_803EA8DC;
extern int lbl_8030C270[14];
extern Block_80096954 *lbl_803EA920;
extern Slot_80096D14 lbl_8030C2A8[2];
extern Record_80097518 lbl_8030C2B8[];

int fn_801BE648(void *p);
int fn_800BA6F8(void);
void fn_8009A8F0(void);
int fn_800AE978(void);
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
int fn_8002CA74(Type_803EA368 *p, int msg, int value);
void fn_8002CF34(Type_803EA368 *p);
unsigned char fn_8002D060(Type_803EA368 *p);
void fn_8002E890(RecordList_8002E7C0 *pList);
int fn_801C6458(int a, int b);
int fn_801E15D0(int a);
int fn_801E195C(int a);
void fn_80093684(void *p);
void fn_800937CC(void);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
void fn_8009D924(int index);
void fn_8009D944(int index);
unsigned int fn_801C3180(const char *pText);
void fn_8009B87C(int index, Entry_8009B87C *pEntry);
void fn_8009B8C4(int index);
unsigned int fn_8009B910(int index);
int fn_8009B9A8(int index);

extern unsigned char lbl_803EA930;
extern Block_8009AB34 *lbl_803EA948;
extern Block_8009B720 *lbl_803EA984[2];
extern unsigned char lbl_803EA98C;
extern int lbl_803EA990;
extern char lbl_803EA994[7];
extern unsigned char lbl_803EA99B;
extern void *lbl_803EB688;
extern Entry_8009B87C lbl_802D7BF8;
extern Entry_80219044 lbl_8030E6D0;
}

extern "C" int fn_80090244(int *p)
{
    int result = 0;

    if (fn_80092830(*p) != 0) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8009036C(int *p)
{
    fn_80094454(*p);
}

extern "C" Actor_801C009C *fn_80091240(unsigned short index)
{
    Character_80093BCC *pCharacter = fn_80093BCC(index);

    return fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
}

extern "C" int fn_800920B8(void *p, void *pBuffer)
{
    memcpy(pBuffer, p, sizeof(Block_800925F0));
    return 1;
}

extern "C" int fn_800920EC(void *p, void *pBuffer)
{
    ((Block_800925F0 *)p)->mUnknown80 = ((Block_800925F0 *)pBuffer)->mUnknown80;
    return 1;
}

extern "C" int fn_80092160(void *p)
{
    return sizeof(Block_800925F0);
}

extern "C" int fn_80092168(void *p, void *q)
{
    Block_800925F0 *pBlock = (Block_800925F0 *)p;
    Block_800925F0 *pOther = (Block_800925F0 *)q;
    int result;

    if (pOther != 0) {
        result = memcmp(&pBlock->mUnknown80, &pOther->mUnknown80, sizeof(Block_800920EC));
    } else {
        result = fn_80238278(&pBlock->mUnknown80, sizeof(Block_800920EC), 0);
    }
    return result;
}

extern "C" void fn_800942F0(int index);
extern "C" void fn_8009418C(void);

extern "C" void fn_800925A4(void)
{
    fn_800942F0(0);
    fn_800942F0(1);
    fn_800942F0(2);
    fn_800942F0(3);
    fn_800942F0(4);
    fn_800942F0(5);
}

extern "C" void fn_800925F0(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EC924, sizeof(Block_800925F0), 0, 0x616E6D73);

    fn_80238234(pHandle, 0, 0, 0, fn_80092168);
    fn_80238248(pHandle, fn_800920B8, fn_80092160, fn_800920EC);
    fn_802381E0(pHandle);
    lbl_803EA8BC = 0;
    lbl_803EA8BD = 0;
    lbl_803EA8BE = 0;
    lbl_803EA8BF = 0;
    lbl_803EA8C0 = 0;
    lbl_803EA8C4 = 0;
    lbl_803EA8C8 = 0;
    lbl_803EA8D5 = 0;
    lbl_803EA8CC = 0;
    lbl_803EA8D4 = 0;
    fn_8009418C();
}

extern "C" void fn_800926A8(void)
{
    lbl_803EA8BC = 0;
    lbl_803EA8BD = 0;
    lbl_803EA8BE = 0;
    lbl_803EA8BF = 0;
    lbl_803EA8C0 = 0;
    lbl_803EA8C4 = 0;
    lbl_803EA8C8 = 0;
    lbl_803EA8D5 = 0;
    lbl_803EA8CC = 0;
    fn_8009418C();
}

extern "C" int fn_800926F4(void)
{
    int result = -1;
    unsigned short i;

    for (i = 0; i <= 3; i++) {
        if (fn_80093BCC(i) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int fn_8009274C(int index)
{
    Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];
    int result = 0;

    if (pCharacter->mUnknown0 != -1 && pCharacter->mUnknown38C != 8) {
        result = 1;
    }
    return result;
}

extern "C" int fn_80092784(unsigned char index)
{
    Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];
    int result = 0;

    if (pCharacter->mUnknown0 != -1) {
        result = pCharacter->mUnknown38C == 5;
    }
    return result;
}

extern "C" int fn_800927BC(int index)
{
    Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];
    int result = 0;

    if (pCharacter->mUnknownD8.mWord < 0) {
        result = fn_801BC060(pCharacter->mUnknownD8.mParts[1]) == 1;
    } else if (fn_801BC044(pCharacter->mUnknownD8.mParts[1]) == 1) {
        result = 1;
    }
    return result;
}

extern "C" Actor_801C009C *fn_80093BAC(int a, int b)
{
    return lbl_803EC924->mEntries[b].mpUnknown0->mpUnknown8[a];
}

extern "C" Character_80093BCC *fn_80093BCC(unsigned short index)
{
    Block_800925F0 *pBlock = lbl_803EC924;
    Character_80093BCC *pCharacter = 0;

    if (pBlock != 0 && index <= 3 && pBlock->mUnknown80.mCharacters[index].mUnknown0 != -1) {
        pCharacter = &pBlock->mUnknown80.mCharacters[index];
    }
    return pCharacter;
}

extern "C" void *fn_80093C08(unsigned int index)
{
    void *p = 0;

    if (index <= 3 && lbl_803EC924->mUnknown80.mCharacters[index].mUnknown0 != -1) {
        p = lbl_803EC924->mUnknown80.mCharacters[index].mUnknownEC;
    }
    return p;
}

extern "C" void fn_80093C3C(int index, short value, Object_80039F5C *p)
{
    short *pValues = lbl_803EC924->mUnknown80.mUnknownE40;

    pValues[index] = value;
}

extern "C" int fn_80093C50(int index)
{
    short *pValues = lbl_803EC924->mUnknown80.mUnknownE40;

    return pValues[index];
}

extern "C" int fn_80093C64(void)
{
    return lbl_803EC924->mUnknown80.mUnknownE4E;
}

extern "C" int fn_80093E38(int index)
{
    return lbl_802D73B8[index].mUnknown0;
}

extern "C" int fn_80093E4C(int kind, int index)
{
    int result = 999;

    switch (kind) {
    case 0:
    case 1:
        break;
    case 3:
        result = lbl_802D73B8[index].mUnknown4;
        break;
    case 4:
        result = lbl_802D72D8[index].mUnknown4;
        break;
    case 5:
        result = lbl_802D7808[index].mUnknown4;
        break;
    case 2:
        result = lbl_802D77D8[index].mUnknown4;
        break;
    }
    return result;
}

extern "C" int fn_80093EC0(int kind, int value)
{
    int result = 999;
    unsigned int i;

    switch (kind) {
    case 2:
        break;
    case 3:
        for (i = 0; i < fn_80094374(kind); i++) {
            if (lbl_802D73B8[i].mUnknown0 == value) {
                result = lbl_802D73B8[i].mUnknown4;
                break;
            }
        }
        break;
    case 4:
        for (i = 0; i < fn_80094374(kind); i++) {
            if (lbl_802D72D8[i].mUnknown0 == value) {
                result = lbl_802D72D8[i].mUnknown4;
                break;
            }
        }
        break;
    case 5:
        for (i = 0; i < fn_80094374(kind); i++) {
            if (lbl_802D7808[i].mUnknown0 == value) {
                result = lbl_802D7808[i].mUnknown4;
                break;
            }
        }
        break;
    }
    return result;
}

extern "C" int fn_80093FD4(int key, int *pA, int *pB)
{
    int found = 0;
    int i;

    for (i = 0; i <= 12; i++) {
        if (lbl_802D78D8[i].mUnknown0 == key) {
            found = 1;
            *pA = lbl_802D78D8[i].mUnknown4;
            *pB = lbl_802D78D8[i].mUnknown8;
            break;
        }
    }
    return found;
}

extern "C" int fn_80094048(int key, Object_80039F5C **ppA, Object_80039F5C **ppB)
{
    int a = 0x7FFF;
    int b = 0x7FFF;
    int found = fn_80093FD4(key, &a, &b);

    if (found) {
        if (a != 0x7FFF) {
            *ppA = fn_8003AD2C(a);
        } else {
            *ppA = 0;
        }
        if (b != 0x7FFF) {
            *ppB = fn_8003AD2C(b);
        } else {
            *ppB = 0;
        }
    }
    return found;
}

extern "C" void fn_800940D8(int index, unsigned char value)
{
    lbl_802D73B8[index].mUnknownC = value;
}

extern "C" void fn_8009418C(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        lbl_8030C164[i].mUnknown0 = -1;
        lbl_8030C164[i].mUnknown4 = 0;
    }
}

extern "C" void fn_800941B8(void)
{
    if (lbl_803EA8BE) {
        fn_800655D0();
        lbl_803EA8BE = 0;
    }
}

extern "C" void fn_800941EC(void)
{
    if (lbl_803EA8BF) {
        fn_8015C254(1);
        fn_8015A0D0(1);
        lbl_803EA8BF = 0;
    }
}

extern "C" int fn_8009422C(void)
{
    return lbl_802D72BC[0];
}

extern "C" void fn_800942F0(int index)
{
    void *pData = lbl_803EC924->mpUnknown7C;

    fn_801F010C(pData, lbl_803EC924->mEntries[index].mUnknown8);
    fn_801F010C(pData, lbl_803EC924->mEntries[index].mUnknownC);
    lbl_803EC924->mEntries[index].mUnknown8 = 0;
    lbl_803EC924->mEntries[index].mUnknownC = 0;
    lbl_803EC924->mEntries[index].mUnknown10 = 0;
    lbl_803EC924->mEntries[index].mpUnknown0 = 0;
    lbl_803EC924->mEntries[index].mUnknown4 = 0;
}

extern "C" int fn_80094374(int index)
{
    Table_80093BAC *pTable = lbl_803EC924->mEntries[index].mpUnknown0;
    int count = 0;

    if (pTable != 0) {
        count = pTable->mUnknown4;
    }
    return count;
}

extern "C" int fn_8009439C(int index)
{
    return lbl_803EC924->mEntries[index].mUnknown10;
}

extern "C" int fn_800943B0(int index)
{
    Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];

    return pCharacter->mUnknown38C == 7;
}

extern "C" int fn_800943D0(void)
{
    return lbl_803EA8BD;
}

extern "C" int fn_80094488(void)
{
    return lbl_803EA8C4;
}

extern "C" Record_80094490 *fn_80094490(int index)
{
    return &lbl_8030C0B4[index];
}

extern "C" int fn_800944A4(int kind)
{
    int result = 1;

    if ((fn_801485D4() != 0 && fn_80148A58()->mUnknown8[12] == 0) || fn_80178AE0() != 2 || fn_80025708() != 0) {
        result = 0;
    } else if (kind != 14) {
        if ((kind == 1 && fn_80177F7C() != 4) || lbl_802D79D8[kind] == 0) {
            result = 0;
        } else {
            result = lbl_802D79D8[kind] > fn_802372EC(0, 100) + 1;
        }
    }
    return result;
}

extern "C" int fn_80094564(unsigned int a, unsigned int b)
{
    int result = -1;

    if (a <= 4 && b <= 4) {
        result = lbl_802D7974[a][b];
    }
    return result;
}

extern "C" void fn_80094608(unsigned char value)
{
    lbl_803EA8D4 = value;
}

extern "C" void fn_80094B78(Header_80094B78 *p)
{
    fn_801C1F94(p, 0, sizeof(Header_80094B78));
    lbl_803EC928 = 0;
    p->mUnknown2 = sizeof(Header_80094B78);
}

extern "C" void fn_80094BBC(int value)
{
    lbl_803EC928 = value;
}

extern "C" void fn_80094C00(Entry_80094BC4 *p, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        fn_80094BC4(&p[i]);
    }
}

extern "C" int fn_80094D94(Entry_80094BC4 *p)
{
    return fn_80092830(p->mUnknown8);
}

extern "C" void fn_80094DB8(Entry_80094BC4 *p)
{
    fn_80093410(p->mUnknown8);
    p->mUnknown8 = -1;
}

extern "C" void fn_80094EDC(void);

extern "C" void fn_80094DF0(void)
{
    int count;

    do {
        Entry_80094BC4 *p = lbl_803EA8DC;
        int i;

        count = 0;
        for (i = 0; i < 10; i++) {
            switch (p->mUnknown24) {
            case 0:
                break;
            case 2:
                p->mUnknown24 = 3;
            case 1:
            case 3:
            case 4:
                count++;
                break;
            }
            p++;
        }
        if (count != 0) {
            fn_80094EDC();
        }
    } while (count > 0);
}

extern "C" void fn_80094E80(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EA8DC, 10 * sizeof(Entry_80094BC4), 0, 0x616E6D6D);

    fn_80094C00((Entry_80094BC4 *)fn_8023816C(pHandle), 10);
    fn_802381E0(pHandle);
    fn_800925F0();
}

extern "C" void fn_80094EDC(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        Entry_80094BC4 *p = &lbl_803EA8DC[i];

        switch (p->mUnknown24) {
        case 0:
            break;
        case 1:
            if (fn_80094C4C(p) == 1) {
                p->mUnknown24 = 2;
            } else {
                p->mUnknown24 = 4;
            }
            break;
        case 2:
            if (fn_80094D94(p) == 0) {
                p->mUnknown24 = 3;
            }
            break;
        case 3:
            fn_80094DB8(p);
            p->mUnknown24 = 4;
            break;
        case 4:
            if (p->mpCallback20 != 0) {
                if (p->mpUnknown0 != 0) {
                    p->mpCallback20(p->mpUnknown0);
                }
                if (p->mpUnknown4 != 0) {
                    p->mpCallback20(p->mpUnknown4);
                }
            }
            fn_80094BC4(p);
            p->mUnknown24 = 0;
            break;
        }
    }
}

extern "C" void fn_80094FE8(void)
{
    if (lbl_803EA8DC != 0) {
        fn_80094DF0();
        fn_800941B8();
        fn_80094C00(lbl_803EA8DC, 10);
    }
    fn_800926A8();
}

extern "C" int fn_80095028(unsigned int id)
{
    switch (id) {
    case 0x544D4B30:
    case 0x544D4B31:
    case 0x544D4B32:
    case 0x544D4B33:
    case 0x544D4B34:
    case 0x544D4B35:
    case 0x544D4B36:
    case 0x544D4B37:
    case 0x544D4B38:
    case 0x544D4B39:
    case 0x544D4F30:
    case 0x544D4F31:
    case 0x544D4F32:
    case 0x544D4F33:
    case 0x544D4F34:
    case 0x544D4F35:
    case 0x544D4F36:
    case 0x544D4F37:
    case 0x544D4F38:
    case 0x544D4F39:
        return 0;
    }
    return 1;
}

extern "C" int fn_80095FD8(Object_80039F5C *p)
{
    int result = 1;

    if (p->mIdBytes[3] == 1) {
        switch (p->mpState->mId) {
        case 10:
        case 11:
        case 12:
        case 16:
        case 17:
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" void fn_8009601C(void)
{
    fn_801C1F94(lbl_8030C270, 0, sizeof(lbl_8030C270));
}

extern "C" void fn_8009604C(int index, int value)
{
    lbl_8030C270[index] = value;
}

extern "C" int fn_80096060(int index)
{
    return lbl_8030C270[index];
}

extern "C" int fn_8009637C(unsigned short index)
{
    Character_80093BCC *pCharacter = fn_80093BCC(index);
    int result = 1;

    fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    if (pCharacter->mUnknownE0.mUnknown0 == 0 && fn_80027DF0() == 0 && fn_800AD9B4() == 4) {
        result = fn_8009B9BC() == 0;
    }
    return result;
}

extern "C" int fn_80096590(void)
{
    int result = -1;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        if (fn_80096DA8(i)->mUnknown0 == -1) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" Table_80093BAC *fn_800966F8(int index)
{
    return lbl_803EA920->mpUnknown0[index];
}

extern "C" int fn_80096794(void)
{
    return 0;
}

extern "C" void fn_80096A24(void)
{
    fn_801F010C(lbl_803EA920->mpUnknown8, 3);
    fn_801D2BD0(lbl_803EA920);
}

extern "C" void fn_80096D14(int index)
{
    Playback_80096DA8 *p = fn_80096DA8(index);

    if (p != 0) {
        if (lbl_8030C2A8[index].mUnknown4 != 0) {
            lbl_8030C2A8[index].mUnknown4--;
            fn_801C1F94(&lbl_803EA920->mUnknown10[index], 0, sizeof(Playback_80096DA8));
            lbl_803EA920->mUnknown10[index].mUnknown0 = -1;
        }
        p->mUnknown10 = 3;
        fn_8017CFB4(7);
    }
}

extern "C" Playback_80096DA8 *fn_80096DA8(unsigned int index)
{
    Playback_80096DA8 *p = 0;

    if (index <= 1) {
        p = &lbl_803EA920->mUnknown10[index];
    }
    return p;
}

extern "C" Actor_801C009C *fn_80096DCC(unsigned int a, int b)
{
    Table_80093BAC *pTable = fn_800966F8(b);
    Actor_801C009C *pActor;

    if (a < pTable->mUnknown4) {
        pActor = pTable->mpUnknown8[a];
    } else {
        pActor = 0;
    }
    return pActor;
}

extern "C" void fn_80096E1C(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        if (lbl_803EA920->mUnknown10[i].mUnknown0 != -1) {
            fn_80096D14(i);
        }
    }
}

extern "C" int fn_8009740C(int value)
{
    int result;

    if (value == 2) {
        result = 2;
    } else if (value == 1) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_80097430(int angle)
{
    return (0x1000000 - angle) & 0xFFFFFF;
}

extern "C" void fn_80097518(int index)
{
    if (lbl_8030C2B8[index].mpUnknownBE8 != 0) {
        fn_801D2BD0(lbl_8030C2B8[index].mpUnknownBE8);
        lbl_8030C2B8[index].mpUnknownBE8 = 0;
    }
}

extern "C" void fn_80097564(void)
{
    unsigned char i;

    for (i = 0; i <= 2; i++) {
        fn_80097518(i);
    }
}

extern "C" Item_8009A63C *fn_8009A63C(int ref)
{
    Item_8009A63C *p;
    int index = ref & 0x1FFFFFFF;
    unsigned int record = (unsigned int)ref >> 29 & 3;

    if (ref < 0) {
        p = &lbl_8030C2B8[record].mpUnknownBE8[index];
    } else {
        p = lbl_8030C2B8[record].mUnknownC[index].mpUnknown0;
    }
    return p;
}

extern "C" int fn_8009A68C(Object_80039F5C *p)
{
    switch (fn_801BE648(p->mpUnknown792)) {
    case 67:
    case 224:
    case 225:
    case 226:
    case 227:
        return 1;
    }
    return 0;
}

extern "C" void fn_8009A6D8(void)
{
    lbl_803EA930 = !lbl_803EA930;
}

extern "C" void fn_8009A8D4(void *p)
{
    if (p != 0) {
        ((int *)p)[2] = ((int *)p)[0] = 0x1FFFFFFF;
    }
}

extern "C" void fn_8009ABC0(void)
{
}

extern "C" void fn_8009ABC4(void)
{
    if (fn_8007F828(8) != 0 && fn_800BA6F8() == 0) {
        lbl_803EA948->mUnknown8 = 1;
    } else {
        lbl_803EA948->mUnknown8 = 0;
    }
    fn_8009A8F0();
}

extern "C" int fn_8009AD30(int a, int b)
{
    return b;
}

extern "C" void fn_8009B1B0(Block_8009B720 *p)
{
    p->mUnknown4.mUnknown127 = 0;
    p->mUnknown4.mUnknown0 = -1;
}

extern "C" int fn_8009B1C4(int value, int *pState)
{
    int result = fn_800AE978() == 0;

    if (fn_80178AE0() != 2) {
        result = 0;
    }
    if (fn_8002D060(lbl_803EA368)) {
        result = 0;
    }
    if (result) {
        fn_8002C9A8(lbl_803EA368, 3, 0);
        if (fn_8002892C() == 0) {
            fn_801E15D0(fn_801C6458(lbl_803EA990, 0));
        }
        if (fn_801E195C(fn_801C6458(lbl_803EA990, 0)) == 2) {
            fn_8002CA74(lbl_803EA368, 10, lbl_803EA990);
        }
        *pState = 0;
        result = 1;
    }
    return result;
}

extern "C" void fn_8009B3A4(int *pState)
{
    if (fn_8002D060(lbl_803EA368)) {
        fn_8002CA74(lbl_803EA368, 9, 0);
    }
}

extern "C" void fn_8009B3E0(Block_8009B720 *p)
{
    fn_8009B87C(1, &lbl_802D7BF8);
    fn_80093684(p->mpUnknown0);
}

extern "C" void fn_8009B420(Block_8009B720 *p)
{
    fn_8009B8C4(1);
    fn_800937CC();
}

extern "C" int fn_8009B448(int value, int index)
{
    int result = 0;
    int *pData = lbl_803EA984[index]->mUnknown4.mUnknown28;

    if (lbl_803EA984[index]->mUnknown4.mEntries[index].mpCallback0 != 0
        && lbl_803EA984[index]->mUnknown4.mEntries[index].mpCallback0(value, pData)) {
        lbl_803EA984[index]->mUnknown4.mUnknown0 = index;
        lbl_803EA984[index]->mUnknown4.mUnknown24 = 0;
        result = 1;
    }
    return result;
}

extern "C" int fn_8009B4C8(void)
{
    int result = 0;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        int *pData = lbl_803EA984[i]->mUnknown4.mUnknown28;

        if (fn_8009B9A8(i)) {
            int index = lbl_803EA984[i]->mUnknown4.mUnknown0;

            if (fn_8009B910(i) < 900) {
                lbl_803EA984[i]->mUnknown4.mUnknown24++;
                if (lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback4(pData)) {
                    result = 1;
                } else {
                    lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback8(pData);
                    result = 0;
                }
            } else {
                lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback8(pData);
                result = 0;
            }
            if (result == 0) {
                fn_8009B1B0(lbl_803EA984[i]);
            }
        }
    }
    if (fn_80025708() && result == 0) {
        fn_8009D944(4);
    }
    return result;
}

extern "C" int fn_8009B5E8(void *p, void *q)
{
    int result;

    if (q != 0) {
        result = fn_80238258(p, q, sizeof(Block_8009B720));
    } else {
        result = fn_80238278(&((Block_8009B720 *)p)->mUnknown4, sizeof(Block_8009B5E8), 0);
    }
    return result;
}

extern "C" int fn_8009B628(void *p, void *pBuffer)
{
    *(Block_8009B720 *)pBuffer = *(Block_8009B720 *)p;
    return 1;
}

extern "C" int fn_8009B698(void *p, void *pBuffer)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        ((Block_8009B720 *)p)->mUnknown4 = ((Block_8009B720 *)pBuffer)->mUnknown4;
    }
    return 1;
}

extern "C" int fn_8009B718(void *p)
{
    return sizeof(Block_8009B720);
}

extern "C" void fn_8009B720(void *pData)
{
    Block_8009B720 *pBlock;
    unsigned int i;

    lbl_803EA98C = 0;
    for (i = 0; i <= 1; i++) {
        void *pHandle = fn_80238174(0, (void **)&lbl_803EA984[i], sizeof(Block_8009B720), 0, 0x63656C62);

        fn_80238234(pHandle, 0, 0, 0, fn_8009B5E8);
        fn_80238248(pHandle, fn_8009B628, fn_8009B718, fn_8009B698);
        pBlock = (Block_8009B720 *)fn_8023816C(pHandle);
        pBlock->mpUnknown0 = pData;
        fn_8009B1B0(pBlock);
        fn_802381E0(pHandle);
    }
    fn_8009B3E0(pBlock);
}

extern "C" void fn_8009B7E0(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        int *pData = lbl_803EA984[i]->mUnknown4.mUnknown28;

        if (fn_8009B9A8(i)) {
            lbl_803EA984[i]->mUnknown4.mEntries[lbl_803EA984[i]->mUnknown4.mUnknown0].mpCallback8(pData);
            lbl_803EA984[i]->mUnknown4.mUnknown127 = 0;
            fn_8009B1B0(lbl_803EA984[i]);
        }
    }
    fn_8009B420(lbl_803EA984[i]);
}

extern "C" void fn_8009B87C(int index, Entry_8009B87C *pEntry)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        lbl_803EA984[i]->mUnknown4.mEntries[index] = *pEntry;
    }
}

extern "C" void fn_8009B8C4(int index)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback0 = 0;
        lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback4 = 0;
        lbl_803EA984[i]->mUnknown4.mEntries[index].mpCallback8 = 0;
    }
}

extern "C" unsigned int fn_8009B910(int index)
{
    return lbl_803EA984[index]->mUnknown4.mUnknown24;
}

extern "C" void fn_8009B924(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        int *pData = lbl_803EA984[i]->mUnknown4.mUnknown28;

        if (fn_8009B9A8(i)) {
            lbl_803EA984[i]->mUnknown4.mEntries[lbl_803EA984[i]->mUnknown4.mUnknown0].mpCallback8(pData);
            lbl_803EA984[i]->mUnknown4.mUnknown127 = 0;
        }
    }
}

extern "C" int fn_8009B9A8(int index)
{
    return lbl_803EA984[index]->mUnknown4.mUnknown127;
}

extern "C" int fn_8009B9BC(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        if (lbl_803EA984[i]->mUnknown4.mUnknown0 == 1) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_8009B9F0(int index)
{
    return lbl_803EA984[index] != 0;
}

extern "C" void fn_8009BA10(int value)
{
    int args[4];

    args[0] = 0;
    args[2] = 2;
    lbl_8030E6D0.mpText = lbl_803EA994;
    args[1] = value;
    args[3] = (int)&lbl_8030E6D0;
    lbl_8030E6D0.mLength = fn_801C3180(lbl_803EA994);
    if (fn_8002B5A8()) {
        fn_8021D7B8(lbl_803EB688, 0x80000019, 4, args);
    }
    lbl_803EA99B = value;
}

extern "C" unsigned char fn_8009BA94(void)
{
    return lbl_803EA99B;
}

extern "C" void fn_8009BA9C(int value)
{
    RecordList_8002E7C0 list;
    unsigned int i;

    lbl_803EA98C = 0;
    for (i = 0; i <= 1; i++) {
        lbl_803EA984[i]->mUnknown4.mUnknown128 = value;
    }
    fn_8002E890(&list);
    if (fn_8009B448(value, 0)) {
        lbl_803EA984[0]->mUnknown4.mUnknown127 = 1;
    }
    fn_8002C9A8(lbl_803EA368, 3, 0);
    fn_8002CF34(lbl_803EA368);
    for (i = 0; i <= 1; i++) {
        if (lbl_803EA984[i]->mUnknown4.mUnknown127 == 0) {
            fn_8009B1B0(lbl_803EA984[i]);
        }
    }
}

extern "C" void fn_8009BB50(int a, int b)
{
}

extern "C" void fn_8009BBD8(int value)
{
    if (fn_8009B448(value, 1)) {
        lbl_803EA984[1]->mUnknown4.mUnknown127 = 1;
        if (fn_80025708()) {
            fn_8009D924(4);
        }
    } else {
        lbl_803EA984[1]->mUnknown4.mUnknown127 = 0;
    }
}

extern "C" void fn_8009BC30(int value)
{
    lbl_803EA990 = value;
}

extern "C" Object_80039F5C *fn_8009BCE8(int *pRef)
{
    int ref = *pRef;
    int index = ref >> 16 & 0xFF;
    int team = ref >> 8 & 0xFF;
    Object_80039F5C *p = 0;

    if ((ref & 0xFF) == 1) {
        p = fn_80039F5C(team, index);
    }
    return p;
}

extern "C" void fn_8009BD2C(Object_80039F5C *p, int *pRef)
{
    if (p != 0) {
        *pRef = p->mId;
    } else {
        *pRef = 0;
    }
}

extern "C" void fn_8009BD48(int *pRef, int a, int b, int c)
{
    *pRef = a | b << 8 | c << 16;
}

extern "C" void fn_8009CC28(void)
{
}

extern "C" void fn_8009D00C(int value, int *pState)
{
    switch (*pState) {
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        *pState = 3;
        break;
    case 0:
        *pState = 1;
        break;
    }
}

extern "C" int fn_8009D338(Timer_8009D338 *p)
{
    return p->mUnknown8 == 0;
}

extern "C" void fn_8009D348(Timer_8009D338 *p)
{
    p->mUnknown8--;
    p->mUnknown10 = p->mUnknown4;
}

extern "C" void fn_8009D360(Timer_8009D338 *p, unsigned int time)
{
    if (!(p->mUnknown14 & 1)) {
        while (time >= p->mUnknown10) {
            if (p->mUnknown8 != 0) {
                time -= p->mUnknown10;
                fn_8009D348(p);
            } else {
                time = 0;
            }
        }
        p->mUnknown10 -= time;
    }
}

extern "C" void fn_8009D3D8(Timer_8009D338 *p)
{
    p->mUnknown8++;
    p->mUnknown10 = p->mUnknown4;
}

extern "C" void fn_8009D3F0(Timer_8009D338 *p, unsigned int time)
{
    while (time >= p->mUnknown10) {
        if (p->mUnknown8 <= 86399) {
            time += p->mUnknown10;
            fn_8009D3D8(p);
            if (p->mUnknown8 > 86399) {
                p->mUnknown8 = 0;
            }
        } else {
            p->mUnknown8 = 0;
        }
    }
    p->mUnknown10 -= time;
}