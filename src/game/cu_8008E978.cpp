#include <string.h>

#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Input_800B6D34.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Record_800B15FC.h"
#include "game/cu_80064864.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8008E978.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
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

/* 3080-byte records of the .bss array at 0x8030C2B8. */
struct Record_80097518 {
    unsigned char mUnknown0[3048];
    void *mpUnknownBE8;
    unsigned char mUnknownBEC[28];
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
