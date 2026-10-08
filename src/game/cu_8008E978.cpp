#include <string.h>

#include "engine/vptmanager.h"
#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Entry_800B206C.h"
#include "game/Entry_80219044.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Input_800B6D34.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8017886C.h"
#include "game/RecordList_8002E7C0.h"
#include "game/Record_800B15FC.h"
#include "game/Team_80167A8C.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8007F828.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"

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

struct Object_80144CE0;

/* Three code pointers at 0x8030E6DC. */
struct Callbacks_8030E6DC {
    void (*mpCallback0)(void);
    void (*mpCallback4)(void);
    void (*mpCallback8)(float value);
};

/* Object whose pointer is the word +2240 of Block_8030E6E8; the size is not
   established. */
struct Record_8030EFA8 {
    unsigned char mUnknown0[12];
    float mUnknownC;
    int mUnknown10;
};

/* Object at 0x8030E6E8. Only the accessed members are typed; the size is
   not established. */
struct Block_8030E6E8 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned short mUnknownC;
    unsigned char mUnknownE[2];
    unsigned char mUnknown10[12];
    Vector_80039F5C mUnknown1C;
    float mUnknown28;
    float mUnknown2C;
    float mUnknown30;
    float mUnknown34;
    unsigned char mUnknown38[8];
    int mUnknown40;
    unsigned char mUnknown44[4];
    int mUnknown48;
    float mUnknown4C;
    float mUnknown50;
    unsigned char mUnknown54[8];
    int mUnknown5C;
    float mUnknown60;
    int mUnknown64;
    unsigned char mUnknown68[4];
    int mUnknown6C[20];
    Object_80144CE0 *mpUnknownBC[30];
    unsigned char mUnknown134[1920];
    unsigned char mUnknown8B4[8];
    unsigned char mUnknown8BC;
    unsigned char mUnknown8BD;
    unsigned char mUnknown8BE[2];
    Record_8030EFA8 *mpUnknown8C0;
    int mUnknown8C4;
    void *mpUnknown8C8;
};

/* Stack block whose address fn_800A4E8C passes as the fourth argument of the
   callbacks of the .data table 0x802D7E20. */
struct Params_800A4E8C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
};

/* Halfword pair of the array returned by fn_8011F50C; fn_800A554C passes one
   to the callbacks of the .data table 0x802D7E4C. */
struct Pair_800A554C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
void fn_801469A0(void);
void fn_800540E0(void);
int fn_801486A0(void);
void fn_80146E78(void);
void fn_8005412C(void);
void fn_800A2B40(void);
int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle);
void fn_80144E38(Object_80144CE0 *pObject);

extern unsigned char lbl_803EA9F8;
extern unsigned char lbl_803EA9F0;
extern void *lbl_803EA9F4;
extern int lbl_803EC948;
extern Callbacks_8030E6DC lbl_8030E6DC;
extern Block_8030E6E8 lbl_8030E6E8;
}

extern "C" int fn_800A2624(void)
{
    return lbl_803EA9F8;
}

extern "C" int fn_800A2760(void)
{
    switch (lbl_8030E6E8.mUnknown0) {
    case 0:
        return 0;
    case 1:
        return 9;
    case 3:
        return 72;
    case 2:
        return 36;
    case 4:
        return 81;
    case 5:
        return 18;
    case 9:
        return 54;
    case 6:
        return 45;
    case 7:
        return 27;
    case 8:
        return 63;
    case 10:
        return 90;
    case 11:
        return 99;
    }
    return 54;
}

extern "C" void fn_800A29AC(void)
{
    if (fn_801485D4() != 0) {
        fn_801486A0();
    }
}

extern "C" void fn_800A2F3C(int value)
{
    lbl_8030E6E8.mUnknown0 = value;
}

extern "C" void fn_800A30B8(void)
{
    fn_801469A0();
    fn_800540E0();
    if (lbl_8030E6DC.mpCallback4 != 0) {
        lbl_8030E6DC.mpCallback4();
    }
    fn_801EEFAC(lbl_803EA9F4);
    lbl_803EA9F4 = 0;
    lbl_8030E6DC.mpCallback0 = 0;
    lbl_8030E6DC.mpCallback4 = 0;
    lbl_8030E6DC.mpCallback8 = 0;
    lbl_803EA9F0 = 0;
}

extern "C" void fn_800A3120(float value)
{
    fn_80146E78();
    fn_8005412C();
    fn_800A2B40();
    if (lbl_8030E6DC.mpCallback8 != 0) {
        lbl_8030E6DC.mpCallback8(value);
    }
}

extern "C" float fn_800A32B4(void)
{
    return lbl_8030E6E8.mUnknown28;
}

extern "C" float fn_800A32C0(void)
{
    return lbl_8030E6E8.mUnknown2C;
}

extern "C" float fn_800A32CC(void)
{
    return lbl_8030E6E8.mUnknown30;
}

extern "C" float fn_800A32D8(void)
{
    return lbl_8030E6E8.mUnknown34;
}

extern "C" void *fn_800A3360(void)
{
    return lbl_8030E6E8.mpUnknown8C8;
}

extern "C" void *fn_800A336C(void)
{
    return lbl_803EA9F4;
}

extern "C" int fn_800A3374(void)
{
    return lbl_8030E6E8.mUnknown4;
}

extern "C" int fn_800A3380(void)
{
    return lbl_8030E6E8.mUnknown6;
}

extern "C" int fn_800A338C(void)
{
    return lbl_8030E6E8.mUnknown8;
}

extern "C" int fn_800A3398(void)
{
    return lbl_8030E6E8.mUnknownA;
}

extern "C" int fn_800A33A4(void)
{
    return lbl_8030E6E8.mUnknownC;
}

extern "C" int fn_800A33B0(void)
{
    return 1;
}

extern "C" int fn_800A33B8(void)
{
    return lbl_8030E6E8.mUnknown48;
}

extern "C" float fn_800A33C4(void)
{
    return lbl_8030E6E8.mUnknown4C;
}

extern "C" float fn_800A33D0(void)
{
    return lbl_8030E6E8.mUnknown50;
}

extern "C" int fn_800A33DC(void)
{
    return lbl_8030E6E8.mUnknown40;
}

extern "C" int fn_800A33E8(void)
{
    return lbl_8030E6E8.mUnknown5C;
}

extern "C" float fn_800A33F4(void)
{
    return lbl_8030E6E8.mUnknown60;
}

extern "C" float fn_800A3400(void)
{
    return lbl_8030E6E8.mpUnknown8C0->mUnknownC;
}

extern "C" int fn_800A3410(void)
{
    return lbl_8030E6E8.mpUnknown8C0->mUnknown10;
}

extern "C" int fn_800A3420(void)
{
    return lbl_8030E6E8.mUnknown64;
}

extern "C" void *fn_800A342C(void)
{
    return lbl_8030E6E8.mUnknown10;
}

extern "C" Vector_80039F5C *fn_800A3438(void)
{
    return &lbl_8030E6E8.mUnknown1C;
}

extern "C" int fn_800A3444(void)
{
    return lbl_8030E6E8.mUnknown0;
}

extern "C" void fn_800A3450(void)
{
    unsigned char i;

    for (i = 0; i < 30; i++) {
        if (lbl_8030E6E8.mpUnknownBC[i] != 0) {
            fn_80144E38(lbl_8030E6E8.mpUnknownBC[i]);
        }
        lbl_8030E6E8.mpUnknownBC[i] = 0;
    }
}

extern "C" int fn_800A34B0(void)
{
    return lbl_8030E6E8.mUnknown8BC;
}

extern "C" int fn_800A34BC(void)
{
    return lbl_8030E6E8.mUnknown8BD;
}

extern "C" int fn_800A34C8(int index)
{
    return lbl_8030E6E8.mUnknown6C[index];
}

extern "C" int fn_800A34E0(void)
{
    return lbl_8030E6E8.mUnknown8C4;
}

extern "C" Record_8030EFA8 *fn_800A34EC(void)
{
    return lbl_8030E6E8.mpUnknown8C0;
}

extern "C" int fn_800A34F8(int index)
{
    return lbl_8030E6E8.mUnknown8B4[index];
}

extern "C" int fn_800A350C(void)
{
    int result = 1;

    if (lbl_8030E6E8.mUnknown0 == 5 || lbl_8030E6E8.mUnknown0 == 9) {
        result = 0;
    }
    return result;
}

extern "C" void fn_800A3B58(Object_80039F5C *p, int a, int b)
{
}

extern "C" void fn_800A3D68(int value)
{
    lbl_803EC948 = value;
}

extern "C" int fn_800A3DC4(int value)
{
    switch (value) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 9:
        return 1;
    }
    return 0;
}

extern "C" int fn_800A432C(Key_80110630 *pA, Key_80110630 *pB)
{
    int result = pA->mUnknown0 == pB->mUnknown0;

    if (pA->mUnknown1 != pB->mUnknown1) {
        result = 0;
    }
    return result;
}

extern "C" void fn_800A4950(Object_80039F5C *p, Object_80039F5C *pOther, int index,
                            Params_800A4E8C *pParams)
{
    if (p->mpState->mId == 2 || p->mpState->mId == 30) {
        pParams->mUnknown8 = 400;
    } else {
        pParams->mUnknown8 = 300;
    }
}

extern "C" void fn_800A4E64(Object_80039F5C *p, Object_80039F5C *pOther, int index,
                            Params_800A4E8C *pParams)
{
    pParams->mUnknown8 = 100000;
    pParams->mUnknown0 = 30;
    pParams->mUnknown4 = 0;
    pParams->mUnknownC = 5;
}

extern "C" int fn_800A506C(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int result = 0;

    if (pPair->mUnknown0 == 0 && fn_8009F058(p, pTarget, 0x400000) != 0) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800A50B8(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int limit = 256 / (pPair->mUnknown0 + 1);

    return fn_802372EC(0, 256) < limit;
}

extern "C" int fn_800A55C0(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    p->mUnknown512.mUnknown14 = 0;
    return 1;
}

extern "C" int fn_800A5A60(void)
{
    return 0;
}

extern "C" void fn_800A5A68(Pair_800A554C *pPairs)
{
    int i;

    for (i = 0; i < 11; i++) {
        pPairs[i].mUnknown0 = 0;
        pPairs[i].mUnknown2 = 0;
    }
}

extern "C" void fn_800A5A88(Pair_800A554C *pPairs)
{
}

/* Partial view of the object whose word +0x28 fn_800C6640 decodes as a
   player reference. The size is unknown. */
struct Object_800C6640 {
    unsigned char mUnknown0[0x28];
    int mUnknown28;
};

/* Record whose address fn_8011F4EC returns. Only the bytes fn_800C8CE8
   reads are declared. */
struct Record_8011F4EC {
    unsigned char mUnknown0[0x199];
    unsigned char mUnknown199[3];
    unsigned char mUnknown19C[3];
};

/* One of the five 24-byte entries per team of Block_800C9D6C. */
struct Entry_800C9D6C {
    int mRef;
    unsigned int mUnknown4;
    int mUnknown8;
    unsigned int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned short mUnknown12;
    unsigned int mUnknown14;
};

/* Allocated through fn_80238174 under the id 'turb' (fn_800C9D6C). */
struct Block_800C9D6C {
    int mRefs[3];
    unsigned int mCounts[2];
    Entry_800C9D6C mEntries[2][5];
    unsigned char mUnknown104;
    unsigned char mUnknown105;
};

extern "C" {
int fn_8022E558(void);
int fn_8022E560(void);
void fn_800B852C(void);
void fn_80043DD8(void);
void fn_801624D0(void *arg);
void fn_80163274(int handle);
void fn_80030F38(int handle);
void fn_80148048(void *pOwner);
void fn_800C4410(int value);
void fn_80046E30(int handle);
void fn_80163DD0(int handle);
void fn_80043D68(void);
void fn_8019B320(int handle);
void fn_80046504(int handle);
void fn_800B8538(void);
void fn_800C442C(void);
void fn_80046FD0(void);
void fn_80163E54(int handle);
void fn_801626A4(void *arg);
void fn_80163300(int handle);
void fn_80030FD8(int handle);
void fn_801480B0(void *pOwner);
void fn_8019B368(void);
void fn_8004659C(void);
void fn_8016172C(void);
void fn_80047050(void);
void fn_80162794(void);
void fn_801635E8(void);
void fn_8015C114(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_800A7F30(int team);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_80170140(Object_80039F5C *p);
int fn_800CA5CC(Object_80039F5C *p, int kind, int value);
void fn_800E9504(Object_80039F5C *p);
void fn_80178718(Object_80039F5C *p);
void fn_800C8688(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
int fn_800C5BF0(Object_80039F5C *p, int value);
int fn_800C5DE4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80111354(Object_80039F5C *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_801486A0(void);
int fn_801783AC(int bit);
int fn_8011F1CC(void);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
int fn_800E1554(Object_80039F5C *p);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A578(int handle);
int fn_800EE7C8(Object_80039F5C *p);
unsigned int fn_8011E188(void);
int fn_801CFFD0(int a, int b);
int fn_801BE648(void *p);
Record_8011F4EC *fn_8011F4EC(void);
int fn_800C8C1C(Object_80039F5C *p);
Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
Object_80039F5C *fn_800C8DBC(int team, Vector_80039F5C *pPos, Object_80039F5C *p, int mode);
void fn_800C9E4C(unsigned char a, unsigned char b);
int fn_800C95DC(int team, int index, int *pRef);
int fn_800BA6F8(void);
int fn_800BAA24(void);
int fn_80178C9C(void);
int fn_800B65A0(int team);
int fn_800B6644(int index);
Object_80039F5C *fn_800B6544(int index);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_800C4E18(Object_80039F5C *p);
Object_80039F5C *fn_800C9070(int team, Object_80039F5C *p, Object_80039F5C *pOther, int mode);
int fn_800C91F0(Object_80039F5C *p, unsigned char *pOut, int second);
int fn_800CA288(Object_80039F5C *p);
void fn_800CA4A8(void);

extern float lbl_802DA2BC[14];
extern float lbl_802DA2F4[14];
extern float lbl_802DA32C[14];
extern float lbl_802DA39C[14][2];
extern float lbl_802DA40C[14][2];
extern float lbl_802DA47C[14][2];
extern float lbl_802DA4EC[14][2];
extern float lbl_802DA55C[14][2];
extern float lbl_802DA5CC[14][2];
extern Block_800C9D6C *lbl_803EAC3C;
extern unsigned int lbl_8030C084[];
}

extern "C" void fn_800C46B0(int handle)
{
    fn_8022E558();
    fn_800B852C();
    fn_80043DD8();
    fn_801624D0((void *)handle);
    fn_80163274(handle);
    fn_80030F38(handle);
    fn_80148048((void *)handle);
    fn_800C4410(0);
    fn_80046E30(handle);
    fn_80163DD0(handle);
}

extern "C" void fn_800C471C(int handle)
{
    fn_80043D68();
    fn_8019B320(handle);
    fn_80046504(handle);
    fn_800B8538();
    fn_800C442C();
    fn_80046FD0();
    fn_80163E54(handle);
    fn_801626A4((void *)handle);
    fn_80163300(handle);
    fn_80030FD8(handle);
    fn_801480B0((void *)handle);
}

extern "C" void fn_800C478C(void)
{
    fn_8019B368();
    fn_8004659C();
    fn_8016172C();
    fn_80047050();
    fn_80162794();
    fn_801635E8();
    fn_8015C114();
}

extern "C" void *fn_800C47C4(void)
{
    return gStaData.fn_80033FD4();
}

extern "C" float fn_800C48CC(int index, float value)
{
    return value * lbl_802DA2BC[index];
}

extern "C" float fn_800C48E4(int index, float value)
{
    return value * lbl_802DA2F4[index];
}

extern "C" float fn_800C48FC(int index, float value)
{
    return value * lbl_802DA32C[index];
}

extern "C" float fn_800C4914(Object_80039F5C *p, float value)
{
    if (p->mpUnknown780 != 0) {
        value = fn_800C48CC(fn_800C4E18(p), value);
    }
    return value;
}

extern "C" float fn_800C495C(Object_80039F5C *p, float value)
{
    if (p->mpUnknown780 != 0) {
        value = fn_800C48E4(fn_800C4E18(p), value);
    }
    return value;
}

extern "C" float fn_800C49A4(Object_80039F5C *p, float value)
{
    if (p->mpUnknown780 != 0) {
        value = fn_800C48FC(fn_800C4E18(p), value);
    }
    return value;
}

extern "C" float fn_800C4A70(Object_80039F5C *p, int index)
{
    int kind = fn_800C4E18(p);
    float result;

    switch (p->mpState->mId) {
    case 35:
        result = lbl_802DA39C[kind][index];
        break;
    case 34:
        result = lbl_802DA40C[kind][index];
        break;
    case 36:
        result = lbl_802DA47C[kind][index];
        break;
    case 20:
        result = lbl_802DA4EC[kind][index];
        break;
    case 28:
        result = lbl_802DA55C[kind][index];
        break;
    default:
        result = lbl_802DA5CC[kind][index];
        break;
    }
    return result;
}

extern "C" int fn_800C4E18(Object_80039F5C *p)
{
    if (p->mpUnknown780 == 0) {
        return 3;
    }
    return p->mpUnknown780->mUnknown8;
}

extern "C" int fn_800C4E30(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;

    if (fn_800A851C(fn_80178320(), p) && fn_800A7F30(fn_80178308()) == 0) {
        result = fn_802372EC(0, 100) < 100;
    }
    if (fn_80170140(pOther)) {
        result = 0;
    }
    if (result) {
        if (fn_80137B40() != pOther) {
            result = 0;
        }
        if (p->mpState->mId == 12 || p->mpState->mId == 94) {
            result = 0;
        }
    }
    return result;
}

extern "C" void fn_800C51DC(Object_80039F5C *p, Object_80039F5C *pOther)
{
    if (p->mUnknown528.mUnknown15 != 7 && p->mUnknown528.mUnknown15 != 9) {
        fn_800CA5CC(p, 10, 1);
    }
    fn_800CA5CC(pOther, 9, 1);
}

extern "C" int fn_800C53D8(Object_80039F5C *p)
{
    int result = 0;

    if (p != 0) {
        result = fn_800A7F30(p->mIdBytes[2]) == 2;
    }
    return result;
}

extern "C" void fn_800C561C(Object_80039F5C *p, int value)
{
    Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);

    fn_800E9504(p);
    if (p->mpState->mId == 10) {
        fn_80178718(fn_8009BCE8(&p->mUnknown560.mUnknown48));
        p->mFlags |= 0x10000;
        p->mFlags &= ~0x80000;
        fn_800C8688(p, pOther, 0, 0);
    }
    if (pOther != 0 && fn_800C5BF0(pOther, value)) {
        fn_800E9504(pOther);
    }
}

extern "C" void fn_800C5B20(Object_80039F5C *p, int value)
{
    Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    Record_800B15FC *pRecord;

    fn_80111354(p);
    if (p->mpState->mId == 58 && fn_800C53D8(p) == 0) {
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 38;
        pRecord->mUnknown16 = 0;
        fn_800B1508();
    }
    if (pOther != 0 && fn_802372EC(0, 255) > pOther->mRatings[0] && fn_800C5BF0(pOther, value)) {
        fn_80111354(pOther);
    }
}

extern "C" void fn_800C5F80(Object_80039F5C *p, int value, int *pA, int *pB, int *pC)
{
    if (value == 0 && fn_801486A0() && !fn_801783AC(0) && fn_8011F1CC() && fn_80137B40() == p) {
        *pA = 94;
        *pB = 93;
        *pC = 164;
    } else {
        *pA = 95;
        *pB = 96;
        if (p->mpState->mId == 16 && fn_80114E7C(p)) {
            *pC = 247;
        } else {
            *pC = 164;
        }
    }
}

extern "C" int fn_800C6640(Object_80039F5C *p, Object_800C6640 *pSource, Object_80039F5C *pOther, int value,
                           int chance)
{
    int result = 0;

    if (p->mFlags & 0x2000) {
        return 0;
    }
    if (pSource != 0 && pOther == 0) {
        pOther = fn_8009BCE8(&pSource->mUnknown28);
    }
    if (pOther != 0 && fn_800C5BF0(p, value) && fn_800C5DE4(pOther, p)) {
        if (fn_800D0B90(p) || (pOther != 0 && fn_800E1554(pOther))) {
            return 0;
        }
        if (fn_800A7F30(p->mIdBytes[2]) == 0 && fn_800A851C(pOther->mIdBytes[2], pOther)) {
            return 0;
        }
        result = 100 - chance;
    }
    return result;
}

extern "C" int fn_800C6738(Object_80039F5C *p, Object_80039F5C *pOther)
{
    void *pA;
    int b;

    if (pOther == 0 || fn_800AD9B4() != 3 || (p->mFlags & 0x800) || (pOther->mFlags & 0x800)
        || p->mIdBytes[2] != fn_80178320() || pOther == p || (pOther->mId & 0xFF) != 1
        || (pOther->mId >> 8 & 0xFF) == p->mIdBytes[2]) {
        return 0;
    }
    switch (p->mpState->mId) {
    case 17:
        if (fn_80114E7C(pOther) == p) {
            break;
        }
        return 0;
    case 10:
    case 11:
        return 0;
    case 28:
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &pA, &b);
        if (fn_8009A578(b) == 5) {
            return 0;
        }
        break;
    }
    switch (pOther->mpState->mId) {
    case 28:
        fn_8009A5DC(pOther->mpState->mUnknown1, pOther->mpState->mUnknown2, &pA, &b);
        if (fn_8009A578(b) == 5) {
            return 0;
        }
        break;
    case 26:
        if (fn_800EE7C8(pOther)) {
            return 0;
        }
        break;
    }
    if (!fn_800C5DE4(p, pOther) || !fn_800C5BF0(pOther, pOther->mUnknown2914)) {
        return 0;
    }
    fn_8011E188();
    return 1;
}

extern "C" void fn_800C68B8(Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
}

extern "C" int fn_800C769C(Object_80039F5C *p, int value)
{
    if (p->mUnknown1220 != 0 && p->mUnknown1224 == value) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800C76C0(Object_80039F5C *p)
{
    if (p->mUnknown1220 != 0) {
        return 1;
    }
    return 0;
}

extern "C" void fn_800C76D8(Object_80039F5C *p, int value, unsigned char a, unsigned char b)
{
    if (p->mUnknown1220 != 0 && p->mUnknown1224 == value) {
        return;
    }
    p->mUnknown1220 = 15;
    p->mUnknown1221 = a;
    p->mUnknown1222 = b;
    p->mUnknown1224 = value;
}

extern "C" void fn_800C7708(Object_80039F5C *p)
{
    p->mUnknown1224 = 0;
    p->mUnknown1221 = 0;
    p->mUnknown1222 = 0;
    p->mUnknown1220 = 0;
}

extern "C" int fn_800C7720(Object_80039F5C *pOther, Object_80039F5C *p)
{
    int result = 0;

    if (fn_801486A0()) {
        result = fn_801CFFD0(0xC00000, p->mMotion.mFacing) <= 0x1FFFFF;
        if (fn_80114E7C(p)) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800C8694(Object_80039F5C *p)
{
    switch (fn_801BE648(p->mpUnknown792)) {
    case 94:
    case 95:
    case 164:
    case 175:
    case 181:
    case 247:
        return 1;
    }
    return 0;
}

extern "C" int fn_800C8704(int *pA, int *pB)
{
    *pA = fn_8022E558();
    *pB = fn_8022E560();
    return 0;
}

extern "C" int fn_800C8744(int team)
{
    if (team == 0) {
        return fn_8022E558();
    }
    return fn_8022E560();
}

extern "C" int fn_800C8BBC(Object_80039F5C *p)
{
    int result = 0;

    fn_80177FE0();
    if (fn_8011F1CC() && p != 0) {
        result = fn_801783AC(0) == 0;
    }
    return result;
}

extern "C" Object_80039F5C *fn_800C8CE8(void)
{
    Record_8011F4EC *pRecord = fn_8011F4EC();
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned char i;
    int other = fn_80178320();
    Object_80039F5C *p;
    Object_80039F5C *pTarget;
    int found;
    unsigned char flag;

    for (i = 0; i <= 2; i++) {
        p = fn_80039F5C(team, pRecord->mUnknown199[i]);
        found = fn_800C91F0(p, &flag, 1);
        if (pRecord->mUnknown19C[i] != 0 && found && flag && !fn_800C8C1C(p)) {
            pTarget = fn_800FB9D4(p);
            if (pTarget == 0) {
                pTarget = fn_800C9070(other, p, p, 0);
            }
            pResult = pTarget;
            break;
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_800C9070(int team, Object_80039F5C *p, Object_80039F5C *pOther, int mode)
{
    return fn_800C8DBC(team, &p->mMotion.mPos, pOther, mode);
}

extern "C" Object_80039F5C *fn_800C9094(int team, Object_80039F5C *p, Object_80039F5C *pOther)
{
    return fn_800C8DBC(team, &p->mMotion.mPos, pOther, 1);
}

extern "C" Object_80039F5C *fn_800C90BC(int team, Object_80039F5C *pOther)
{
    Vector_80039F5C pos;

    fn_80137D58(fn_801374BC(), &pos);
    return fn_800C8DBC(team, &pos, pOther, 0);
}

extern "C" int fn_800C9108(Object_80039F5C *p, unsigned char *pTeam)
{
    int result = -1;
    int ref;
    unsigned char i;

    fn_8009BD2C(p, &ref);
    *pTeam = (ref & 0xFF00) >> 8;
    for (i = 0; i < lbl_803EAC3C->mCounts[(ref & 0xFF00) >> 8]; i++) {
        if (lbl_803EAC3C->mEntries[(ref & 0xFF00) >> 8][i].mRef == ref) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int fn_800C91B0(Object_80039F5C *p)
{
    unsigned char team;
    int index = fn_800C9108(p, &team);

    return lbl_803EAC3C->mEntries[team][index].mUnknown10;
}

extern "C" int fn_800C91F0(Object_80039F5C *p, unsigned char *pOut, int second)
{
    int found = 0;
    int ref;
    unsigned char team;
    unsigned char i;

    fn_8009BD2C(p, &ref);
    team = ref >> 8 & 0xFF;
    for (i = 0; i < lbl_803EAC3C->mCounts[team]; i++) {
        if (lbl_803EAC3C->mEntries[team][i].mRef == ref) {
            found = 1;
            if (pOut != 0) {
                if (second) {
                    *pOut = lbl_803EAC3C->mEntries[team][i].mUnknown11 == 1;
                } else {
                    *pOut = lbl_803EAC3C->mEntries[team][i].mUnknown10 == 1;
                }
            }
            break;
        }
    }
    return found;
}

extern "C" int fn_800C92CC(void *p, void *q)
{
    Block_800C9D6C *pBlock = (Block_800C9D6C *)p;
    Block_800C9D6C *pOther = (Block_800C9D6C *)q;
    int result = 0;
    unsigned char i;
    unsigned char team;

    if (pOther != 0) {
        for (i = 0; i <= 2; i++) {
            result |= pBlock->mRefs[i] != pOther->mRefs[i];
        }
        for (team = 0; team <= 1; team++) {
            for (i = 0; i < lbl_803EAC3C->mCounts[team]; i++) {
                result |= pBlock->mEntries[team][i].mUnknown4 != pOther->mEntries[team][i].mUnknown4;
                result |= pBlock->mEntries[team][i].mUnknown14 != pOther->mEntries[team][i].mUnknown14;
                result |= pBlock->mEntries[team][i].mRef != pOther->mEntries[team][i].mRef;
                result |= pBlock->mEntries[team][i].mUnknownC != pOther->mEntries[team][i].mUnknownC;
                result |= pBlock->mEntries[team][i].mUnknown8 != pOther->mEntries[team][i].mUnknown8;
                result |= pBlock->mEntries[team][i].mUnknown10 != pOther->mEntries[team][i].mUnknown10;
                result |= pBlock->mEntries[team][i].mUnknown12 != pOther->mEntries[team][i].mUnknown12;
                result |= pBlock->mEntries[team][i].mUnknown11 != pOther->mEntries[team][i].mUnknown11;
                result |= pBlock->mEntries[team][i].mUnknown14 != pOther->mEntries[team][i].mUnknown14;
            }
        }
    } else {
        result = fn_80238278(pBlock, sizeof(Block_800C9D6C), 0);
    }
    return result;
}

extern "C" int fn_800C94BC(void *p, void *pBuffer)
{
    *(Block_800C9D6C *)pBuffer = *(Block_800C9D6C *)p;
    return 1;
}

extern "C" int fn_800C9508(void *p, void *pBuffer)
{
    *(Block_800C9D6C *)p = *(Block_800C9D6C *)pBuffer;
    return 1;
}

extern "C" int fn_800C9554(void *p)
{
    return sizeof(Block_800C9D6C);
}

extern "C" unsigned int fn_800C955C(Object_80039F5C *p, int kind)
{
    return lbl_8030C084[kind];
}

extern "C" Object_80039F5C *fn_800C9570(int team)
{
    unsigned char i;
    unsigned int count = fn_80178D18(team);
    Object_80039F5C *p;

    for (i = 0; i < count; i++) {
        p = fn_80039F5C(team, i);
        if (p->mpState->mId == 90) {
            return p;
        }
    }
    return 0;
}

extern "C" void fn_800C9A80(int team)
{
    unsigned char i;

    for (i = 0; i < lbl_803EAC3C->mCounts[team]; i++) {
        if (i < (unsigned int)fn_80178D70(team)) {
            if (lbl_803EAC3C->mEntries[team][i].mUnknown8 == -1
                && (!fn_800BA6F8() || team == fn_80178308() || !fn_800BAA24())) {
                fn_800C95DC(team, i, &lbl_803EAC3C->mEntries[team][i].mRef);
            }
        } else {
            lbl_803EAC3C->mEntries[team][i].mRef = 0;
        }
    }
}

extern "C" void fn_800C9B78(void)
{
    fn_800C9A80(fn_80178308());
    if (fn_80178C9C()) {
        fn_800C9A80(fn_80178320());
    }
}

extern "C" void fn_800C9BB0(void)
{
    unsigned char team;
    unsigned char count;
    int i;
    Object_80039F5C *p;
    int ref;

    for (team = 0; team <= 1; team++) {
        if (fn_800B65A0(team) != 255) {
            count = 0;
            if (!fn_800BA6F8() || team == fn_80178308() || !fn_800BAA24()) {
                for (i = 0; i <= 9; i++) {
                    if (team == fn_800B6644(i)) {
                        p = fn_800B6544(i);
                        if (p != 0) {
                            fn_8009BD2C(p, &ref);
                            if (count < lbl_803EAC3C->mCounts[team]) {
                                lbl_803EAC3C->mEntries[team][count].mRef = ref;
                                lbl_803EAC3C->mEntries[team][count].mUnknown8 = i;
                                count++;
                            }
                        }
                    }
                }
            }
        } else {
            for (count = 0; count < lbl_803EAC3C->mCounts[team]; count++) {
                lbl_803EAC3C->mEntries[team][count].mUnknown8 = -1;
            }
        }
    }
}

extern "C" void fn_800C9D6C(unsigned char a, unsigned char b)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAC3C, sizeof(Block_800C9D6C), 0, 0x74757262);
    Block_800C9D6C *pBlock;
    unsigned char i;

    fn_80238234(pHandle, 0, 0, 0, fn_800C92CC);
    fn_80238248(pHandle, fn_800C94BC, fn_800C9554, fn_800C9508);
    pBlock = (Block_800C9D6C *)fn_8023816C(pHandle);
    pBlock->mCounts[0] = a;
    pBlock->mCounts[1] = b;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    for (i = 0; i <= 2; i++) {
        pBlock->mRefs[i] = 0;
    }
    fn_802381E0(pHandle);
    fn_800C9E4C(a, b);
}

extern "C" void fn_800C9E40(void)
{
    lbl_803EAC3C = 0;
}

extern "C" void fn_800CA228(void)
{
    fn_800CA4A8();
}

extern "C" Object_80039F5C *fn_800CA248(void)
{
    int ref = lbl_803EAC3C->mRefs[lbl_803EAC3C->mUnknown105++];

    return fn_8009BCE8(&ref);
}

extern "C" int fn_800CA288(Object_80039F5C *p)
{
    int result = 0;
    int busy = 0;
    Input_800B6D34 input;

    if (p != 0) {
        if (p->mUnknown8 != 255) {
            if (p->mFlags & 0x4000) {
                fn_800B6D34(p, &input);
                busy = input.mUnknown95 >> 3 & 1;
            }
        } else {
            busy = 0;
        }
        if (!busy) {
            switch (fn_801BE648(p->mpUnknown792)) {
            case 74:
                if (p->mUnknown528.mUnknown15 == 7 || p->mUnknown528.mUnknown15 == 9) {
                    result = 0;
                    break;
                }
            case 44:
            case 48:
            case 67:
            case 70:
            case 84:
            case 165:
            case 193:
            case 195:
            case 196:
            case 197:
            case 207:
            case 208:
            case 209:
            case 210:
            case 224:
            case 225:
            case 227:
                result = 1;
                break;
            }
        }
    }
    return result;
}

extern "C" void fn_800CA3C4(void)
{
    int ref = 0;
    unsigned char i;
    int team = fn_80178308();
    unsigned char out;
    int index;
    unsigned char j;
    int tmp;

    for (i = 0; i <= 2; i++) {
        index = fn_80168E00(team, i, &out);
        if (index != 255) {
            fn_8009BD2C(fn_80039F5C(team, index), &ref);
            lbl_803EAC3C->mRefs[i] = ref;
        } else {
            lbl_803EAC3C->mRefs[i] = 0;
        }
    }
    for (i = 0; i <= 2; i++) {
        j = fn_802372EC(0, 3);
        if (j != i) {
            tmp = lbl_803EAC3C->mRefs[i];
            lbl_803EAC3C->mRefs[i] = lbl_803EAC3C->mRefs[j];
            lbl_803EAC3C->mRefs[j] = tmp;
        }
    }
}

extern "C" void fn_800CA4A8(void)
{
    unsigned char team;
    unsigned char i;
    Object_80039F5C *p;

    for (team = 0; team <= 1; team++) {
        for (i = 0; i < lbl_803EAC3C->mCounts[team]; i++) {
            if (lbl_803EAC3C->mEntries[team][i].mUnknown12 != 0) {
                lbl_803EAC3C->mEntries[team][i].mUnknown12--;
            }
            p = fn_8009BCE8(&lbl_803EAC3C->mEntries[team][i].mRef);
            if (lbl_803EAC3C->mEntries[team][i].mUnknown10 == 0 && fn_800CA288(p)) {
                lbl_803EAC3C->mEntries[team][i].mUnknown4 =
                    lbl_803EAC3C->mEntries[team][i].mUnknown4 + lbl_803EAC3C->mEntries[team][i].mUnknownC
                            > lbl_803EAC3C->mEntries[team][i].mUnknown14
                        ? lbl_803EAC3C->mEntries[team][i].mUnknown14
                        : lbl_803EAC3C->mEntries[team][i].mUnknown4 + lbl_803EAC3C->mEntries[team][i].mUnknownC;
            }
            lbl_803EAC3C->mEntries[team][i].mUnknown11 = lbl_803EAC3C->mEntries[team][i].mUnknown10;
            lbl_803EAC3C->mEntries[team][i].mUnknown10 = 0;
        }
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
/* 164-byte block allocated for each team by fn_800A70F4; the two block
   pointers are the .sbss words lbl_803EC954. */
struct Block_800A70F4 {
    unsigned char mUnknown0[8];
    int mUnknown8;
    int mUnknownC;
    unsigned char mUnknown10[8];
    int mUnknown18;
    unsigned char mUnknown1C[64];
    int mUnknown5C;
    int mUnknown60;
    unsigned char mUnknown64;
    unsigned char mUnknown65[3];
    int mUnknown68;
    int mUnknown6C;
    unsigned char mUnknown70[4];
    int mUnknown74[11];
    int mUnknownA0;
};

/* .sbss words at 0x803EC94C: a player pointer followed by two bytes. */
struct Block_803EC94C {
    Object_80039F5C *mpUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
};

/* .bss block at 0x8030F42C; only the accessed prefix is declared. */
struct Block_8030F42C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14[2];
    int mUnknown1C[2];
    char *mpUnknown24[2];
    char *mpUnknown2C;
};

extern "C" {
int fn_800A3E00(Object_80039F5C *p);
void fn_800A2E80(int a, int b);
int fn_800A3444(void);
int fn_800B7F88(Object_80039F5C *p);
int fn_800B78DC(Object_80039F5C *p);
int fn_800B7F34(Object_80039F5C *p);
int fn_800B7E60(Object_80039F5C *p);
int fn_800B65A0(int team);
int fn_80178308(void);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013C438(Camera_8013F738 *pCamera);
void fn_8013FA8C(int a);
void fn_8013C384(void *pCamera, int a, int b, int c);
void fn_8013F97C(int a);
void fn_8013C6F0(Camera_8013F738 *pCamera);
int fn_8011F1CC(void);
void fn_80148108(int mode);
void fn_80162FB8(int index, int ref);
void fn_80163020(void);
int fn_80156704(void);
void fn_801574DC(int value);
void fn_800C0330(void *p);
void fn_80047874(unsigned char enable);
void fn_800A636C(int team, Object_80039F5C **ppOut);
void fn_800A7A0C(int team);
void fn_800A9330(void);
void fn_800A9478(int a);

extern Block_803EC94C lbl_803EC94C;
extern Block_800A70F4 *lbl_803EC954[2];
extern int lbl_803EC95C;
extern unsigned char lbl_803EAA18;
extern void (*lbl_803EAA24[2])(int team);
extern int lbl_803EAA44[2];
extern unsigned char lbl_803EAA4C;
extern unsigned char lbl_803EAA4D;
extern unsigned char lbl_803EAA4F;
extern unsigned char lbl_803EAA50;
extern unsigned char lbl_803EAA51;
extern unsigned char lbl_803EAA84;
extern unsigned char lbl_803EAA85;
extern int lbl_803EAA94;
extern unsigned char lbl_803EAA98;
extern void *lbl_803EABA4;
extern Object_80039F5C *lbl_8030F404[2][2];
extern Block_8030F42C lbl_8030F42C;
}

extern "C" int fn_800A5DD0(Object_80039F5C *p)
{
    return p->mUnknown1156;
}

extern "C" void fn_800A5DD8(Object_80039F5C *p)
{
    if (fn_800A5DD0(p)) {
        fn_800B7F88(p);
    } else {
        fn_800B78DC(p);
    }
}

extern "C" void fn_800A5E20(Object_80039F5C *p)
{
    if (fn_800A5DD0(p)) {
        fn_800B7F34(p);
    } else {
        fn_800B7E60(p);
    }
}

extern "C" void fn_800A5E68(Object_80039F5C *p)
{
    if ((p->mFlags & 0x20000) && fn_800A3E00(p) == 0) {
        p->mUnknown1156 = 0;
        p->mFlags &= ~0x20000;
    }
}

extern "C" int fn_800A5EB8(Object_80039F5C *a, Object_80039F5C *b)
{
    int result = 0;

    if (a != 0 && b != 0) {
        if (a->mpState->mId == 26 && b->mpState->mId == 27) {
            result = 1;
        } else if (a->mpState->mId == 25 && (b->mpState->mId == 68 || b->mpState->mId == 90)) {
            result = 1;
        }
    }
    return result;
}

extern "C" unsigned char fn_800A5F20(Object_80039F5C *p)
{
    short average;

    fn_80137B40();
    average = (p->mRatings[2] + p->mRatings[4]) / 2;
    return (average + 168) * 20 / 510 + 20;
}

extern "C" int fn_800A5F80(void)
{
    Object_80039F5C *p = fn_80137B40();
    Input_800B6D34 input;

    if (lbl_803EC94C.mUnknown4 == 0) {
        return 1;
    }
    if (p != 0) {
        Object_80039F5C *pOther;

        fn_800B6D34(p, &input);
        if (input.mUnknown94 & 1) {
            return 1;
        }
        pOther = lbl_803EC94C.mpUnknown0;
        if ((p->mFlags & 0x10000) || (pOther->mFlags & 0x10000) || (p->mFlags & 0x800)
            || (pOther->mFlags & 0x800) || p->mpState->mId == 15) {
            return 1;
        }
        if (p->mMotion.mPos.mY >= fn_80177FE0().mY) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_800A61A8(void);

extern "C" void fn_800A6044(void)
{
    Object_80039F5C *p;
    int team;

    fn_800A61A8();
    fn_8013C438(fn_8013FA04(5));
    p = fn_80137B40();
    team = fn_80178308();
    if (p == 0) {
        fn_8013FA8C(1);
    } else if (fn_8011F1CC() && fn_800B65A0(team) != 255 && p->mpState->mId == 18) {
        fn_80148108(0);
        fn_8013FA8C(2);
    }
}

extern "C" void fn_800A60D8(Object_80039F5C *a, Object_80039F5C *b)
{
    fn_800A61A8();
    if (fn_800A5EB8(a, b)) {
        lbl_803EC94C.mpUnknown0 = b;
        lbl_803EC94C.mUnknown5 = 1;
        lbl_803EC94C.mUnknown4 = fn_800A5F20(b);
        fn_80162FB8(fn_800B65A0(b->mIdBytes[2]), b->mId);
        fn_8013C384(fn_8013FA04(5), 2, b->mId, 0);
    }
}

extern "C" int fn_800A61E0(void);

extern "C" void fn_800A615C(void)
{
    if (fn_800A61E0()) {
        if (fn_800A5F80()) {
            fn_800A6044();
        } else {
            lbl_803EC94C.mUnknown4--;
        }
    }
}

extern "C" void fn_800A61A8(void)
{
    lbl_803EC94C.mpUnknown0 = 0;
    lbl_803EC94C.mUnknown4 = 0;
    lbl_803EC94C.mUnknown5 = 0;
    fn_80163020();
}

extern "C" int fn_800A61E0(void)
{
    return lbl_803EC94C.mUnknown5;
}

extern "C" void fn_800A61E8(int value)
{
    if (fn_80156704() && (value == 0 || lbl_803EC954[0]->mUnknown68 != 2 || lbl_803EC954[1]->mUnknown68 != 2)) {
        fn_801574DC(value);
    }
}

extern "C" int fn_800A6590(int value)
{
    switch (value) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
    default:
        return 16;
    }
}

extern "C" void fn_800A6750(int team)
{
    lbl_803EC954[team]->mUnknown74[2] = 2;
    lbl_803EC954[team]->mUnknown74[0] = 2;
    lbl_803EC954[team]->mUnknown74[1] = 2;
    lbl_803EC954[team]->mUnknownA0 = lbl_803EAA18;
    lbl_803EC954[team]->mUnknown74[5] = 2;
    lbl_8030F404[team][0] = 0;
    lbl_8030F404[team][1] = 0;
}

extern "C" void fn_800A67B8(int team)
{
    int other = (team + 1) & 1;

    lbl_803EC954[other]->mUnknown74[2] = 0;
    lbl_803EC954[other]->mUnknown74[0] = 0;
    lbl_803EC954[team]->mUnknown74[9] = 2;
    lbl_803EC954[team]->mUnknown74[8] = 2;
    lbl_8030F404[team][0] = 0;
    lbl_8030F404[team][1] = 0;
}

extern "C" void fn_800A6D5C(int team)
{
    lbl_803EAA4C = team;
    lbl_803EAA4D = 1;
    lbl_803EAA4F = 0;
    fn_800C0330(lbl_803EABA4);
    fn_800A61E8(0);
    fn_80047874(0);
}

extern "C" void fn_800A6DA4(void)
{
    lbl_803EAA50 = fn_802372EC(0, 2);
}

extern "C" void fn_800A7274(void)
{
    if (lbl_803EC95C != -1) {
        fn_80093410(lbl_803EC95C);
        lbl_803EC95C = -1;
    }
    lbl_803EAA4D = 0;
    fn_800A9330();
}

extern "C" int fn_800A7E40(int team)
{
    return lbl_803EC954[team]->mUnknown5C;
}

extern "C" int fn_800A7E54(int team)
{
    return lbl_803EC954[team]->mUnknown60;
}

extern "C" void fn_800A7E68(void)
{
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        lbl_803EC954[team]->mUnknown5C = 0;
        lbl_803EC954[team]->mUnknown60 = 0;
        lbl_803EC954[team]->mUnknown6C = 0;
    }
}

extern "C" int fn_800A7EA4(int team)
{
    return lbl_803EC954[team]->mUnknown74[7];
}

extern "C" int fn_800A7EB8(int team)
{
    return lbl_803EC954[team]->mUnknown74[0];
}

extern "C" int fn_800A7ECC(int team)
{
    return lbl_803EC954[team]->mUnknown74[3];
}

extern "C" int fn_800A7EE0(int team)
{
    return lbl_803EC954[team]->mUnknown74[5];
}

extern "C" int fn_800A7EF4(int team)
{
    return lbl_803EC954[team]->mUnknown74[6];
}

extern "C" int fn_800A7F08(int team)
{
    return lbl_803EC954[team]->mUnknown74[4];
}

extern "C" int fn_800A7F1C(int team)
{
    return lbl_803EC954[team]->mUnknown74[1];
}

extern "C" int fn_800A7F30(int team)
{
    return lbl_803EC954[team]->mUnknown74[2];
}

extern "C" int fn_800A7F44(int team)
{
    return lbl_803EC954[team]->mUnknown74[8];
}

extern "C" int fn_800A7F58(int team)
{
    return lbl_803EC954[team]->mUnknown74[9];
}

extern "C" void fn_800A7F6C(void)
{
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        if (lbl_803EC954[team]->mUnknown68 != 0) {
            lbl_803EAA24[lbl_803EC954[team]->mUnknown8](team);
        }
    }
}

extern "C" int fn_800A7FD8(void)
{
    return lbl_803EAA4D;
}

extern "C" int fn_800A83E0(int team)
{
    Block_800A70F4 *pBlock = lbl_803EC954[team];
    int result = -1;

    if (pBlock->mUnknown6C == 1 || pBlock->mUnknown6C == 2) {
        result = pBlock->mUnknownC;
    }
    return result;
}

extern "C" int fn_800A8408(int team)
{
    Block_800A70F4 *pBlock = lbl_803EC954[team];
    int result = 3;

    if (pBlock->mUnknown6C == 1 || pBlock->mUnknown6C == 2) {
        result = pBlock->mUnknown8;
    }
    return result;
}

extern "C" int fn_800A8430(int team)
{
    return lbl_803EC954[team]->mUnknown18;
}

extern "C" int fn_800A8444(int team)
{
    int result = 1;

    if (lbl_803EC954[team]->mUnknown68 == 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800A8468(int team)
{
    return lbl_803EC954[team]->mUnknown68 == 2;
}

extern "C" int fn_800A8488(int team)
{
    return lbl_803EC954[team]->mUnknown6C == 1 || lbl_803EC954[team]->mUnknown6C == 2;
}

extern "C" int fn_800A84AC(int team)
{
    return lbl_803EC954[team]->mUnknown64;
}

extern "C" int fn_800A84C0(void)
{
    return 1;
}

extern "C" int fn_800A84C8(void)
{
    int result = 0;
    unsigned char team;
    unsigned char i;

    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 10; i++) {
            if (lbl_803EC954[team]->mUnknown74[i] != 1) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" int fn_800A851C(int team, Object_80039F5C *p)
{
    Object_80039F5C *pair[2];
    int result;

    fn_800A636C(team, pair);
    result = 0;
    if (p == pair[0] || p == pair[1]) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800A861C(void)
{
    fn_800A2E80(fn_800A3444(), 60);
}

extern "C" void fn_800A8644(void)
{
    fn_800A2E80(fn_800A3444(), 1);
}

extern "C" void fn_800A8738(int value)
{
    lbl_803EAA51 = value;
}

extern "C" int fn_800A8EA4(int team)
{
    return lbl_803EC954[team]->mUnknown6C;
}

extern "C" void fn_800A8EB8(void)
{
    int i;

    for (i = 0; i <= 1; i++) {
        unsigned char team = i;

        if (fn_800A8444(team)) {
            fn_800A7A0C(team);
        }
    }
}

extern "C" void fn_800A8F08(void)
{
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        if (fn_800A8444(team)) {
            lbl_803EAA44[team] = fn_800A8EA4(team);
        } else {
            lbl_803EAA44[team] = 0;
        }
    }
}

extern "C" void fn_800A8F70(void)
{
    lbl_803EAA44[0] = 0;
    lbl_803EAA44[1] = 0;
}

extern "C" int fn_800A8F84(int team)
{
    return lbl_803EAA44[team];
}

extern "C" int fn_800A8F94(void)
{
    return lbl_803EAA4C;
}

extern "C" void fn_800A8F9C(void)
{
}

extern "C" void fn_800A92E4(void)
{
    char *p = (char *)fn_801D2B7C(0x33000, 0, 0);

    lbl_8030F42C.mpUnknown24[0] = p;
    lbl_8030F42C.mpUnknown24[1] = p + 0x19800;
    lbl_8030F42C.mpUnknown2C = p;
}

extern "C" void fn_800A9330(void)
{
    fn_800A9478(0);
    fn_801D2BD0(lbl_8030F42C.mpUnknown2C);
    lbl_8030F42C.mpUnknown2C = 0;
    lbl_8030F42C.mpUnknown24[0] = 0;
    lbl_8030F42C.mpUnknown24[1] = 0;
}

extern "C" int fn_800A937C(void)
{
    return lbl_803EAA84;
}

extern "C" void fn_800A9648(void)
{
    fn_800927BC((unsigned char)lbl_8030F42C.mUnknown14[lbl_8030F42C.mUnknownC]);
}

extern "C" int fn_800A9680(void)
{
    return lbl_803EAA85;
}

extern "C" void fn_800A981C(void)
{
    fn_8013F97C(0);
    fn_8013FA8C(1);
    fn_8013C6F0(fn_8013FA04(5));
}

extern "C" char *fn_800A9F4C(int index)
{
    return lbl_8030F42C.mpUnknown24[index];
}

extern "C" void fn_800AA010(int value)
{
    lbl_803EAA98 = value;
    lbl_803EAA94 = 0;
}

/* The 96 bytes after the first word of Block_800B21D0, compared by
   fn_800B19E8. */
struct State_800B19E8 {
    Entry_800B206C mUnknown0[1];
    Entry_800B206C mUnknown24[1];
    unsigned char mUnknown48[4];
    short mUnknown4C;
    unsigned char mUnknown4E[12];
    unsigned char mUnknown5A;
    unsigned char mUnknown5B;
    unsigned char mUnknown5C;
    unsigned char mUnknown5D;
    unsigned char mUnknown5E;
    unsigned char mUnknown5F[1];
};

/* Allocated through fn_80238174 under the id 'penl' (fn_800B21D0). */
struct Block_800B21D0 {
    void *mpUnknown0;
    State_800B19E8 mUnknown4;
};

/* 72-byte block allocated through fn_80238174 under the id 'pcal'. */
struct Block_800B3660 {
    unsigned char mUnknown0[8];
    unsigned int mUnknown8;
    unsigned char mUnknownC[8];
    int mUnknown14;
    int mUnknown18;
    unsigned char mUnknown1C;
    unsigned char mUnknown1D;
    unsigned char mUnknown1E;
    unsigned char mUnknown1F;
    unsigned char mUnknown20[4];
    int mUnknown24;
    unsigned char mUnknown28[27];
    unsigned char mUnknown43;
    unsigned char mUnknown44[4];
};

/* 20-byte records copied whole by fn_800B49EC. */
struct Record_800B49EC {
    int mUnknown0[5];
};

extern "C" {
void fn_80238420(int handle);
void fn_8023861C(int handle);
unsigned int fn_80238604(int handle);
void *fn_80238540(int handle, int index);
void *fn_8023850C(int handle);
void fn_80238570(int handle, int unknown);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_8009D990(int index);
void fn_800D6F3C(Record_800B15FC *pRecord);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800AFDD4(void (*pCallback)(int, unsigned int));
void fn_800AFE20(void (*pCallback)(int, unsigned int));
void fn_801789F8(void);
unsigned char fn_801735EC(void);
void fn_80177F88(int value);
void fn_8017EBFC(void);
int fn_8017ED6C(void);
void fn_8017EFB4(void);
void fn_8017EF20(void);
void fn_80139274(void);
void fn_800AD910(int a, float b);
unsigned char fn_8017F2EC(unsigned char value);
void fn_800B1900(Block_800B21D0 *p);
int fn_800B1F58(Block_800B21D0 *p, float value);
int fn_8010A254(Object_80039F5C *p, int kind);
int fn_80177C38(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801783AC(int bit);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
int fn_80177F70(void);
void fn_8016DDDC(int team);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013C6F0(Camera_8013F738 *pCamera);
int fn_80169EF4(int mode);
void fn_80167EA0(int team);
void fn_800B3EFC(int team);
void fn_80168640(int team, int kind);
void fn_800B31B0(int a);
void fn_800B34BC(void);

extern int lbl_803EAB18;
extern int *lbl_803EAB1C;
extern Block_800B21D0 *lbl_803EAB20;
extern int lbl_803EAB24;
extern unsigned char lbl_803EAB2C;
extern unsigned char lbl_803EAB2D;
extern Block_800B3660 *lbl_803EAB34;
extern int *lbl_803EAB38;
extern int lbl_803EC908;
extern Block_800B21D0 lbl_8030FAFC;
}

extern "C" void fn_800B14B8(void)
{
    fn_80238420(lbl_803EAB18);
    lbl_803EAB18 = 0xFF;
}

extern "C" void fn_800B14E4(void)
{
    fn_8023861C(lbl_803EAB18);
}

extern "C" void fn_800B1508(void)
{
    if (fn_80238604(lbl_803EAB18) < 74) {
        Record_800B15FC *pRecord = (Record_800B15FC *)fn_80238540(lbl_803EAB18, fn_80238604(lbl_803EAB18));

        pRecord->mUnknown18 = fn_8009D990(1);
        fn_80238570(lbl_803EAB18, pRecord->mUnknown14 <= 61);
        fn_800D6F3C(pRecord);
    }
}

extern "C" void fn_800B1584(int a, const float *pPos)
{
    Record_800B15FC *pRecord = fn_800B15FC();

    pRecord->mUnknown14 = a;
    if (pPos != 0) {
        pRecord->mUnknownC = pPos[0];
        pRecord->mUnknown10 = pPos[1];
    }
    fn_800B1508();
}

extern "C" unsigned short fn_800B15D4(void)
{
    return fn_80238604(lbl_803EAB18);
}

extern "C" Record_800B15FC *fn_800B15FC(void)
{
    Record_800B15FC *pRecord = (Record_800B15FC *)fn_8023850C(lbl_803EAB18);

    fn_801C1F94(pRecord, 0, sizeof(Record_800B15FC));
    fn_8009BD2C(0, &pRecord->mUnknown0);
    return pRecord;
}

extern "C" Record_800B15FC *fn_800B1648(unsigned short index)
{
    return (Record_800B15FC *)fn_80238540(lbl_803EAB18, index);
}

extern "C" void fn_800B1758(int a, unsigned int b)
{
}

extern "C" void fn_800B175C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAB1C, sizeof(int), 0, 0x6F767274);
    int *pState = (int *)fn_8023816C(pHandle);

    *pState = 1;
    fn_802381E0(pHandle);
}

extern "C" void fn_800B17B4(void)
{
    fn_800B14E4();
    *lbl_803EAB1C = 0;
    fn_800AFDD4(fn_800B1758);
    fn_801789F8();
}

extern "C" void fn_800B17F0(float value)
{
    switch (*lbl_803EAB1C) {
    case 0:
        if (fn_801735EC()) {
            *lbl_803EAB1C = 1;
        } else {
            *lbl_803EAB1C = 4;
        }
        break;
    case 1:
        fn_80177F88(1);
        fn_8017EBFC();
        *lbl_803EAB1C = 2;
        break;
    case 2:
        if (fn_8017ED6C() == 0) {
            *lbl_803EAB1C = 3;
        }
        break;
    case 3:
        fn_8017EFB4();
        fn_8017EF20();
        *lbl_803EAB1C = 4;
        break;
    case 4:
        fn_80139274();
        fn_800AD910(5, value);
        break;
    }
}

extern "C" void fn_800B18D0(void)
{
    fn_800B14E4();
    fn_800AFE20(fn_800B1758);
    fn_801789F8();
}

extern "C" int fn_800B19E8(void *p, void *q)
{
    Block_800B21D0 *pBlock = (Block_800B21D0 *)p;
    Block_800B21D0 *pOther = (Block_800B21D0 *)q;
    int result;

    if (pOther != 0) {
        result = fn_80238258(&pBlock->mUnknown4, &pOther->mUnknown4, sizeof(State_800B19E8));
    } else {
        result = fn_80238278(&pBlock->mUnknown4, sizeof(State_800B19E8), 0);
    }
    return result;
}

extern "C" void fn_800B1BF8(void)
{
    lbl_803EAB20->mpUnknown0 = 0;
    fn_8017F2EC(0);
}

extern "C" void fn_800B206C(Entry_800B206C *p, Object_80039F5C *pA, int kind, Object_80039F5C *pB)
{
    p->mUnknown0 = kind;
    fn_8009BD2C(pA, &p->mUnknown4);
    fn_8009BD2C(pB, &p->mUnknown8);
    p->mUnknownC = pA->mMotion.mPos.mX;
    p->mUnknown10 = pA->mMotion.mPos.mY;
    p->mUnknown14 = lbl_803EAB24++;
    p->mUnknown18 = fn_800AD9B4();
    p->mUnknown1C = fn_80177C38();
    p->mUnknown22 = pA->mIdBytes[2] == fn_80178308();
    p->mUnknown20 = fn_801783AC(14);
    p->mUnknown21 = fn_801783AC(15);
}

extern "C" void fn_800B211C(Block_800B21D0 *p, Object_80039F5C *pA, int kind, Object_80039F5C *pB)
{
    fn_800B206C(&p->mUnknown4.mUnknown0[p->mUnknown4.mUnknown5A], pA, kind, pB);
    if (p->mUnknown4.mUnknown0[p->mUnknown4.mUnknown5A].mUnknown22 == 0) {
        p->mUnknown4.mUnknown5D = 1;
    }
    p->mUnknown4.mUnknown5A++;
}

extern "C" void fn_800B2184(Block_800B21D0 *p, Object_80039F5C *pA, int kind, Object_80039F5C *pB)
{
    fn_800B206C(&p->mUnknown4.mUnknown24[p->mUnknown4.mUnknown5B], pA, kind, pB);
    p->mUnknown4.mUnknown5B++;
}

extern "C" void fn_800B21CC(Block_800B21D0 *p, int index)
{
}

extern "C" void fn_800B21D0(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAB20, sizeof(Block_800B21D0), 0, 0x70656E6C);
    Block_800B21D0 *p;
    unsigned char i;

    fn_80238234(pHandle, 0, 0, 0, fn_800B19E8);
    p = (Block_800B21D0 *)fn_8023816C(pHandle);
    p->mUnknown4.mUnknown5A = 0;
    p->mUnknown4.mUnknown5B = 0;
    p->mUnknown4.mUnknown5D = 0;
    p->mUnknown4.mUnknown5E = 1;
    for (i = 0; i < 1; i++) {
        p->mUnknown4.mUnknown0[i].mUnknown0 = 18;
        fn_8009BD2C(0, &p->mUnknown4.mUnknown0[i].mUnknown4);
    }
    for (i = 0; i < 1; i++) {
        p->mUnknown4.mUnknown24[i].mUnknown0 = 18;
        fn_8009BD2C(0, &p->mUnknown4.mUnknown24[i].mUnknown4);
    }
    p->mpUnknown0 = 0;
    lbl_803EAB24 = 0;
    fn_800B1900(p);
    fn_802381E0(pHandle);
}

extern "C" void fn_800B22D4(void)
{
    lbl_803EAB20 = 0;
}

extern "C" void fn_800B22E0(void)
{
    fn_800B1900(lbl_803EAB20);
}

extern "C" void fn_800B2304(void)
{
    lbl_803EAB20->mUnknown4.mUnknown5C = 0;
}

extern "C" int fn_800B2320(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown5A;
}

extern "C" int fn_800B232C(int index)
{
    return lbl_803EAB20->mUnknown4.mUnknown0[index].mUnknown0;
}

extern "C" void fn_800B2370(Object_80039F5C *pA, int kind, Object_80039F5C *pB, float value)
{
    Block_800B21D0 *p = lbl_803EAB20;

    if (p->mUnknown4.mUnknown5E != 0 && p->mUnknown4.mUnknown5A == 0) {
        lbl_8030FAFC = *p;
        fn_800B211C(lbl_803EAB20, pA, kind, pB);
        if (fn_800B1F58(lbl_803EAB20, value) == 0) {
            *lbl_803EAB20 = lbl_8030FAFC;
            if (lbl_803EAB20->mUnknown4.mUnknown5B == 0) {
                fn_800B2184(lbl_803EAB20, pA, kind, pB);
            }
        } else {
            fn_8017F2EC(1);
        }
    }
}

extern "C" void fn_800B24C8(void)
{
    unsigned char i;

    for (i = 0; i < lbl_803EAB20->mUnknown4.mUnknown5B; i++) {
        Object_80039F5C *pObject = fn_8009BCE8(&lbl_803EAB20->mUnknown4.mUnknown24[i].mUnknown8);

        if (pObject != 0 && fn_8010A254(pObject, lbl_803EAB20->mUnknown4.mUnknown24[i].mUnknown0) != 0) {
            fn_800B21CC(lbl_803EAB20, i);
        }
    }
    lbl_803EAB20->mUnknown4.mUnknown5B = 0;
}

extern "C" int fn_800B2600(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown4C;
}

extern "C" void fn_800B260C(short value)
{
    lbl_803EAB20->mUnknown4.mUnknown4C = value;
}

extern "C" int fn_800B2624(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown5D;
}

extern "C" void fn_800B2630(void)
{
    lbl_803EAB20->mUnknown4.mUnknown5D = 0;
}

extern "C" void fn_800B2640(int mask, int set)
{
    if (set != 0) {
        lbl_803EAB20->mUnknown4.mUnknown5C |= mask;
    } else {
        lbl_803EAB20->mUnknown4.mUnknown5C &= ~mask;
    }
}

extern "C" void fn_800B2670(unsigned char value)
{
    lbl_803EAB20->mUnknown4.mUnknown5E = value;
}

extern "C" void fn_800B26D0(Object_800B26B0 *pMotion, int a, int b, float c)
{
    pMotion->mUnknown56 = a;
    pMotion->mUnknown52 = c;
    pMotion->mFacing = b;
}

extern "C" void fn_800B2D9C(Object_800B26B0 *pMotion)
{
    Point_80167910 point;

    fn_80227538(&point, pMotion->mFacing, pMotion->mUnknown28);
    pMotion->mUnknown40 = point.mX;
    pMotion->mUnknown44 = point.mY;
    pMotion->mUnknown32 = pMotion->mFacing;
    pMotion->mUnknown56 = pMotion->mFacing;
}

extern "C" void fn_800B2DF4(void)
{
    if (lbl_803EAB34->mUnknown1F == 0) {
        if (fn_80177F70() != 0) {
            fn_8016DDDC(fn_80178308());
            fn_8016DDDC(fn_80178320());
            fn_8013C6F0(fn_8013FA04(5));
        }
        lbl_803EAB34->mUnknown1F = 1;
    }
}

extern "C" void fn_800B3074(void)
{
}

extern "C" int fn_800B30B8(void)
{
    return 3;
}

extern "C" int fn_800B30C0(void)
{
    return 2;
}

extern "C" void fn_800B3420(void)
{
    int team = fn_80178320();

    fn_80169EF4(0);
    fn_80167EA0(team);
    lbl_803EAB34->mUnknown24 = fn_8016871C(team)->mUnknown4;
}

extern "C" void fn_800B3470(void)
{
}

extern "C" void fn_800B3474(void)
{
    fn_800B3EFC(fn_80178308());
}

extern "C" void fn_800B3498(void)
{
    fn_800B3EFC(fn_80178320());
}

extern "C" int fn_800B35E4(void)
{
    int result = 0;

    if (lbl_803EAB34->mUnknown14 != -1) {
        result = fn_80096B1C(lbl_803EAB34->mUnknown14);
        if (result == 0) {
            fn_80096D14(lbl_803EAB34->mUnknown14);
            lbl_803EAB34->mUnknown14 = -1;
        }
    }
    return result;
}

extern "C" void fn_800B3644(int *p)
{
    if (p == 0) {
        lbl_803EAB38 = &lbl_803EC908;
    } else {
        lbl_803EAB38 = p;
    }
}

extern "C" void fn_800B3C54(void)
{
    lbl_803EAB2C = 1;
    lbl_803EAB2D = 0;
}

extern "C" void fn_800B3EC0(int a, int b)
{
    fn_80168640(a, 1);
    fn_80168640(b, 11);
}

extern "C" void fn_800B40D8(unsigned char value)
{
    fn_800B2DF4();
    lbl_803EAB34->mUnknown43 = value;
}

extern "C" void fn_800B4184(int a)
{
    if (lbl_803EAB34->mUnknown8 & 1) {
        lbl_803EAB34->mUnknown8 |= 16;
        fn_800B31B0(a);
    }
}

extern "C" int fn_800B43A4(void)
{
    return 0;
}

extern "C" void fn_800B43AC(int value)
{
    lbl_803EAB34->mUnknown18 = value;
}

extern "C" void fn_800B43B8(void)
{
    lbl_803EAB34->mUnknown1D = 0;
}

extern "C" void fn_800B43C8(void)
{
    if (lbl_803EAB34->mUnknown14 != -1) {
        fn_80096D14(lbl_803EAB34->mUnknown14);
        lbl_803EAB34->mUnknown14 = -1;
        fn_80096E1C();
    }
}

extern "C" void fn_800B4408(void)
{
    fn_800B43C8();
    fn_800B34BC();
}

extern "C" void fn_800B4434(void)
{
    lbl_803EAB34->mUnknown8 &= ~6;
}

extern "C" void fn_800B49EC(Record_800B49EC *pDst, const Record_800B49EC *pSrc)
{
    *pDst = *pSrc;
}

/* Block allocated by fn_800BA3F0 through fn_80238174 under the id 'prac'
   (392 bytes); only the accessed fields are declared. */
struct Block_800BA3F0 {
    Object_800670B4 *mpUnknown0;
    Object_800670B4 *mpUnknown4;
    Record_80067338 *mpUnknown8;
    Record_80067338 *mpUnknownC;
    int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    Point_8017886C mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24[0x9C];
    int mUnknownC0;
    unsigned char mUnknownC4[0x1C];
    unsigned char mUnknownE0;
    unsigned char mUnknownE1[3];
    int mUnknownE4[37];
    unsigned char mUnknown178[4];
    int mUnknown17C;
    unsigned char mUnknown180;
    unsigned char mUnknown181[1];
    unsigned char mUnknown182;
    unsigned char mUnknown183;
    unsigned char mUnknown184;
    unsigned char mUnknown185;
    unsigned char mUnknown186[2];
};

extern "C" {
void fn_800B14E4(void);
void fn_800B2670(int value);
void fn_800B63B0(void);
unsigned char fn_800B9BFC(void);
void fn_800B9C3C(void);
unsigned char fn_800B9C70(void);
void fn_800B9CB0(void);
int fn_800B9CE4(void);
void fn_800B9D24(void);
void fn_800B9E44(void);
int fn_800B9F50(void);
Point_8017886C fn_800BA7A0(void);
void fn_800BA804(int value);
void fn_800BA8CC(int value);
int fn_800BA94C(void);
void fn_800BA9C0(int value);
void fn_800BAA30(int value);
int fn_800BAAB8(void);
int fn_8006D884(int idx);
Camera_8013F738 *fn_8013FA04(int index);
Object_800670B4 *fn_80168708(int team);
void fn_80177F88(int value);
void fn_801780A8(Point_8017886C pos);
int fn_80178308(void);
int fn_80178320(void);
void fn_8017833C(int value);
void fn_80178370(void);

extern Block_800BA3F0 *lbl_803EAB88;
}

extern "C" void fn_800B9F4C(void)
{
}

extern "C" void fn_800BA570(void)
{
}

extern "C" void fn_800BA574(void)
{
    if (lbl_803EAB88->mUnknown182 && lbl_803EAB88->mUnknown185) {
        fn_800B9D24();
    }
}

extern "C" void fn_800BA6F4(void);

extern "C" void fn_800BA5B0(void)
{
    if (lbl_803EAB88->mUnknown182) {
        fn_8013FA04(0);
        fn_800B9F4C();
        if (fn_800B9BFC() == 1) {
            fn_800BA804(1);
            fn_800B9C3C();
        }
        if (fn_800B9C70() == 1) {
            fn_800BA8CC(1);
            fn_800B9CB0();
        }
        switch (fn_800B9CE4()) {
        case 0:
            fn_800BAA30(1);
            fn_800BA9C0(0);
            break;
        case 1:
            fn_800BAA30(1);
            fn_800BA9C0(1);
            break;
        case 2:
            fn_800BAA30(0);
            break;
        }
        fn_800BA6F4();
    }
}

extern "C" void fn_800BA674(void)
{
    if (lbl_803EAB88->mUnknown182) {
        fn_801780A8(fn_800BA7A0());
        fn_8017833C(lbl_803EAB88->mUnknown180);
        fn_80177F88(lbl_803EAB88->mUnknown20);
        fn_800B2670(0);
        fn_800BA6F4();
        if (lbl_803EAB88->mUnknown185) {
            fn_800B9D24();
            fn_800BAA30(1);
        }
    }
}

extern "C" void fn_800BA6F4(void)
{
}

extern "C" int fn_800BA6F8(void)
{
    Block_800BA3F0 *p = lbl_803EAB88;
    int result = 0;

    if (p != 0 && p->mUnknown182) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800BA71C(void)
{
    return lbl_803EAB88->mUnknown17C;
}

extern "C" void fn_800BA728(void)
{
}

extern "C" void fn_800BA72C(void)
{
    lbl_803EAB88->mpUnknown0 = fn_80168708(fn_80178308());
    lbl_803EAB88->mpUnknown4 = fn_80168708(fn_80178320());
    lbl_803EAB88->mpUnknown8 = fn_8016871C(fn_80178308());
    lbl_803EAB88->mpUnknownC = fn_8016871C(fn_80178320());
    lbl_803EAB88->mUnknown14 = 1;
    lbl_803EAB88->mUnknown10 = 0;
    lbl_803EAB88->mUnknown184 = 0;
}

extern "C" void fn_800BA7E8(float x, float y)
{
    if (lbl_803EAB88->mUnknown20 != 0) {
        lbl_803EAB88->mUnknown18.mX = x;
        lbl_803EAB88->mUnknown18.mY = y;
    }
}

extern "C" int fn_800BA864(void)
{
    return lbl_803EAB88->mUnknown183;
}

extern "C" int fn_800BA870(void)
{
    int result;

    switch (fn_800AD9B4()) {
    case 3:
    case 5:
    case 8:
        result = 0;
        break;
    default:
        if (fn_800BAAB8() != 0) {
            result = 1;
        } else {
            result = 0;
        }
        break;
    }
    return result;
}

extern "C" void fn_800BA8CC(int value)
{
    if (fn_800BA94C() != 0 && value != 0) {
        lbl_803EAB88->mUnknown184 = value;
        fn_800B63B0();
        fn_800B14E4();
        fn_80178370();
        lbl_803EAB88->mUnknown184 = value;
        lbl_803EAB88->mUnknown14 = 0;
    } else {
        lbl_803EAB88->mUnknown184 = 0;
    }
}

extern "C" int fn_800BA940(void)
{
    return lbl_803EAB88->mUnknown184;
}

extern "C" int fn_800BA94C(void)
{
    int result;

    switch (fn_800AD9B4()) {
    case 5:
    case 8:
        result = 0;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" void fn_800BA988(void)
{
    if (fn_800BA6F8()) {
        lbl_803EAB88->mUnknown10++;
    }
}

extern "C" void fn_800BA9C0(int value)
{
    if (lbl_803EAB88->mUnknown185 != value) {
        if (value != 0) {
            fn_800B9D24();
        } else {
            fn_800B9E44();
        }
        lbl_803EAB88->mUnknown185 = value;
        fn_800BAA30(1);
        fn_800BA8CC(1);
    }
}

extern "C" int fn_800BAA24(void)
{
    return lbl_803EAB88->mUnknown185;
}

extern "C" void fn_800BAA30(int value)
{
    if (lbl_803EAB88->mUnknown20 != value) {
        if (value == 0) {
            fn_800B9E44();
            lbl_803EAB88->mUnknown185 = value;
        }
        lbl_803EAB88->mUnknown20 = value;
        fn_80177F88(value);
        lbl_803EAB88->mUnknown184 = 1;
        lbl_803EAB88->mUnknown14 = 0;
        fn_800B63B0();
        fn_800B14E4();
        fn_80178370();
        lbl_803EAB88->mUnknown184 = 1;
    }
}

extern "C" int fn_800BAAB8(void)
{
    return lbl_803EAB88->mUnknown20;
}

extern "C" void fn_800BAAC4(void)
{
    fn_800BA988();
}

extern "C" void fn_800BACF4(void)
{
}

extern "C" void fn_800BACF8(void)
{
    fn_8006D884(4);
}

extern "C" void fn_800BAD9C(void)
{
    if (lbl_803EAB88->mUnknownE0 == 0) {
        lbl_803EAB88->mUnknownE0 = fn_800B9F50();
    }
}

extern "C" void fn_800BAE40(void)
{
    fn_8006D884(4);
}

extern "C" int fn_800BAE64(void)
{
    return lbl_803EAB88->mUnknownE4[lbl_803EAB88->mUnknownC0];
}

/* One of the 80-byte records that the word +16 of Block_800BC538 points
   to; only the accessed fields are declared. */
struct Record_800BAE7C {
    int mUnknown0;
    unsigned char mUnknown4[0x48];
    unsigned char mUnknown4C;
    unsigned char mUnknown4D[3];
};

/* Block allocated by 0x800BC538 (entry 1 of the Class_80297BF8 vtable)
   through fn_80238174 under the id 'preg' (52 bytes); only the fields
   accessed here are declared. */
struct Block_800BC538 {
    int mUnknown0;
    unsigned char mUnknown4[4];
    int mUnknown8;
    int mUnknownC;
    Record_800BAE7C *mpUnknown10;
    unsigned char mUnknown14[4];
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    unsigned char mUnknown24[5];
    unsigned char mUnknown29;
    unsigned char mUnknown2A[2];
    int mUnknown2C;
    unsigned char mUnknown30[4];
};

extern "C" {
void fn_800BB504(void);
void fn_800BB840(int a, int b, int c);
void fn_800BB8D4(void);
void fn_800BBCF0(Record_800BAE7C *p);
void fn_800BBDE0(void);
void fn_8004A230(unsigned char value);
unsigned char fn_800744A8(void);
void fn_80092F98(int handle);
void fn_80093348(int handle);
void fn_800940F0(int handle);
int fn_800A9F4C(int index);
void fn_800CC560(int a);
void fn_8013F3FC(void);
int fn_801F3E28(void);

extern Block_800BC538 *lbl_803EC98C;
extern int lbl_803EC990[2];
extern unsigned char lbl_803EAB94;
extern unsigned char lbl_803EAB95;
extern Class_80297BF8 *lbl_803EAB90;
extern unsigned char lbl_803EABA1;
extern Class_80297BF8 lbl_803EC910;
}

extern "C" unsigned char fn_800BB0C4(void);

extern "C" void fn_800BAE7C(Record_800BAE7C *p, int index)
{
    if (p[index].mUnknown0 != 9999) {
        int b = 0;
        int a = 0;

        if (p[index].mUnknown4C == 1) {
            a = lbl_803EC990[lbl_803EABA1];
            b = lbl_803EC98C->mUnknown2C;
            fn_800BB0C4();
        }
        if (lbl_803EC98C->mUnknown29 == 1) {
            fn_800BB840(8, a, b);
        } else {
            fn_800BB840(p[index].mUnknown0, a, b);
        }
        if (index == 0) {
            fn_800BBCF0(p);
        }
    }
}

extern "C" int fn_800BAF30(void)
{
    int result = 0;

    if (lbl_803EC98C->mUnknown18 != -1 && fn_80092830(lbl_803EC98C->mUnknown18) != 0) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800BBE98(void);

extern "C" void fn_800BAF7C(void)
{
    fn_8004A230(1);
    fn_8013F3FC();
    if (lbl_803EC98C->mpUnknown10[lbl_803EAB95].mUnknown0 == 9999) {
        fn_800BBE98();
    } else {
        lbl_803EC98C->mUnknown0 = 1;
        fn_800BB8D4();
        fn_800BAE7C(lbl_803EC98C->mpUnknown10, lbl_803EAB95 + 1);
    }
}

extern "C" void fn_800BB828(void);

extern "C" void fn_800BAFE8(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        lbl_803EC990[i] = fn_800A9F4C(i);
    }
    lbl_803EC98C->mUnknown29 = 2;
    lbl_803EC98C->mUnknown2C = 0x19000;
    fn_800BB828();
}

extern "C" int fn_800BB050(int value)
{
    int result = 0;

    if (fn_801F3E28() && fn_800744A8() && value == 0) {
        result = 1;
    } else if (!(fn_801F3E28() && fn_800744A8()) && value == 0) {
        result = 1;
    }
    return result;
}

extern "C" unsigned char fn_800BB0C4(void)
{
    lbl_803EABA1++;
    if (lbl_803EABA1 > 1) {
        lbl_803EABA1 = 0;
    }
    return lbl_803EABA1;
}

extern "C" int fn_800BB23C(int value)
{
    return value == 6;
}

extern "C" void fn_800BB5DC(void)
{
    unsigned int count;
    unsigned short i;

    if (!fn_800BA6F8()) {
        count = fn_80178D18(0);
        for (i = 0; i < count; i++) {
            fn_80039F5C(0, i)->mpUnknown4->mUnknown20 |= 1;
        }
        count = fn_80178D18(1);
        for (i = 0; i < count; i++) {
            fn_80039F5C(1, i)->mpUnknown4->mUnknown20 |= 1;
        }
    }
}

extern "C" void fn_800BB828(void)
{
    lbl_803EC98C->mUnknown18 = -1;
    lbl_803EC98C->mUnknown1C = -1;
    lbl_803EC98C->mUnknown20 = -1;
}

extern "C" void fn_800BB8D4(void)
{
    lbl_803EC98C->mUnknown18 = lbl_803EC98C->mUnknown1C;
    fn_800BBDE0();
    fn_80092F98(lbl_803EC98C->mUnknown18);
    fn_80092830(lbl_803EC98C->mUnknown18);
    fn_80092830(lbl_803EC98C->mUnknown18);
}

extern "C" void fn_800BB924(void)
{
    int handle;

    fn_800940F0(lbl_803EC98C->mUnknown18);
    fn_80093348(lbl_803EC98C->mUnknown18);
    fn_80093410(lbl_803EC98C->mUnknown18);
    handle = lbl_803EC98C->mUnknown1C;
    lbl_803EC98C->mUnknown1C = -1;
    lbl_803EC98C->mUnknown18 = handle;
    fn_800BBDE0();
    fn_80092F98(lbl_803EC98C->mUnknown18);
    fn_80092830(lbl_803EC98C->mUnknown18);
    fn_80092830(lbl_803EC98C->mUnknown18);
}

extern "C" void fn_800BB9A0(int, float)
{
}

extern "C" void fn_800BB9A4(int team, int value)
{
    unsigned int count = fn_80178D18(team);
    unsigned short i;

    for (i = 0; i < count; i++) {
        Object_8003DEC4 *p = fn_8003DEC4(team * 7 + i);

        if (value != 0) {
            p->mUnknown20 |= 1;
        } else {
            p->mUnknown20 &= ~1;
        }
    }
}

extern "C" void fn_800BBB4C(void)
{
    fn_800CC560(1);
    lbl_803EC98C->mUnknown0 = 2;
    lbl_803EAB94 = 1;
}

extern "C" void fn_800BBE98(void)
{
    fn_800BB504();
    fn_800BB5DC();
    fn_80096E1C();
    lbl_803EC98C->mUnknown8 = -1;
    lbl_803EC98C->mUnknownC = -1;
    fn_8004A230(1);
    fn_8013825C(fn_801374BC())->mUnknown20 &= ~2;
    fn_8013825C(fn_801374BC())->mUnknown20 |= 1;
    fn_800941B8();
    fn_8017CFB4(7);
    lbl_803EC98C->mUnknown0 = 2;
}

extern "C" void fn_800BC51C(Class_80297BF8 *pObject)
{
    if (pObject == 0) {
        lbl_803EAB90 = &lbl_803EC910;
    } else {
        lbl_803EAB90 = pObject;
    }
}

