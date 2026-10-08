#include <string.h>

#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/Class_80297CE8.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_801FCE10.h"
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

/* One of the two 32-byte records at the start of Block_800BFAD0. */
struct Slot_800BFAD0 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown1A[2];
    unsigned char mUnknown1C;
    unsigned char mUnknown1D[3];
};

/* Allocated through fn_80238174 under the id 'prep' (0x800BFAD0). */
struct Block_800BFAD0 {
    Slot_800BFAD0 mSlots[2];
    int mUnknown40;
    unsigned char mUnknown44[0x54];
    unsigned char mUnknown98[4];
    int mUnknown9C;
    unsigned char mUnknownA0[4];
    short mUnknownA4;
    short mUnknownA6;
    unsigned char mUnknownA8;
    unsigned char mUnknownA9[2];
    unsigned char mUnknownAB;
    unsigned int mUnknownAC;
    int mUnknownB0;
    int mUnknownB4;
    int mUnknownB8;
    int mUnknownBC;
    unsigned char mUnknownC0[5];
    unsigned char mUnknownC5;
    unsigned char mUnknownC6;
    unsigned char mUnknownC7;
};

/* Object whose first word fn_800C2F94 dereferences. */
struct Item_800C2F94 {
    unsigned char mUnknown0[8];
    float mUnknown8;
};

/* 8-byte records of the three 50-entry lists at 0x8030FF40. */
struct Entry_800C3130 {
    Item_800C2F94 *mpUnknown0;
    short mUnknown4;
    short mUnknown6;
};

/* Object returned by fn_8011F4EC; only the accessed bytes are declared and
   the size is unknown. */
struct Block_8011F4EC {
    unsigned char mUnknown0[0x1B8];
    unsigned char mUnknown1B8[3];
    unsigned char mUnknown1BB[3];
    unsigned char mUnknown1BE[3];
    unsigned char mUnknown1C1[3];
    unsigned char mUnknown1C4;
};

/* 3044-byte records of the array at 0x803103F0. */
struct Record_800C432C {
    unsigned char mUnknown0[3044];
};

/* One of the eight 32-byte steps of Sequence_800C4460. */
struct Step_800C4460 {
    int (*mpCallback0)(void *p);
    int (*mpCallback4)(void *p);
    void (*mpCallback8)(void *p);
    float mUnknownC;
    unsigned char mUnknown10[16];
};

/* 260-byte block cleared by fn_800C4438. */
struct Sequence_800C4460 {
    Step_800C4460 mSteps[8];
    unsigned char mUnknown100;
    unsigned char mUnknown101;
    unsigned char mUnknown102[2];
};

extern "C" {
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_800B65A0(int index);
int fn_80177F70(void);
int fn_801F0F18(int a);
void fn_800AD910(int a, float b);
int fn_8017D064(int a);
void fn_8013F9B8(void);
void fn_8010A220(void);
void fn_801789F8(void);
void fn_800B6B98(void);
void fn_800C1E5C(int a, unsigned int b);
void fn_800AFDD4(void (*pCallback)(int, unsigned int));
void fn_800AFE20(void (*pCallback)(int, unsigned int));
void fn_8013FA8C(int a);
void fn_8013F97C(int a);
unsigned char fn_801374D4(void);
void fn_8013FA58(int a, int b);
void fn_800BA804(int a);
int fn_8016E764(void);
int fn_80178308(void);
int fn_80178320(void);
Object_80039F5C *fn_800B6544(int index);
void fn_800B6868(unsigned char a, unsigned char b, unsigned char c, int d);
void fn_80148154(void);
void fn_80148108(int mode);
int fn_801481B0(void);
int fn_800744FC(void);
void fn_80162780(int a, int b);
int fn_8009D9D8(int index);
int fn_8011F32C(void);
int fn_8011F228(void);
int fn_800B119C(void);
int fn_800BA6F8(void);
int fn_8009D990(int index);
int fn_8013F9F8(void);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013C6F0(Camera_8013F738 *pCamera);
int fn_8019623C(int id);
int fn_800B6644(int index);
int fn_800A937C(void);
int fn_800A9648(void);
void fn_800BD35C(void);
void fn_8003A3F4(int a, int index);
int fn_80156704(void);
int fn_80025ACC(void);
void fn_800AE904(int a);
int fn_800AE980(void);
void fn_8017CBFC(int a);
short fn_8017CD44(unsigned char index);
void fn_8017CD20(void);
QueryCursor fn_800C0698(unsigned char index, unsigned short *pValues);
Block_8011F4EC *fn_8011F4EC(void);
int fn_801787A0(void);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_801BE648(void *p);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A578(int handle);
void fn_801BBC3C(unsigned short a, unsigned short b, Record_800C432C *pRecord);
void fn_801F51DC(int a, void *pBase, int count, int size,
                 int (*pCompare)(Entry_800C3130 *, Entry_800C3130 *),
                 void (*pSwap)(Entry_800C3130 *, Entry_800C3130 *), int b, int c);

extern Class_80297CE8 *lbl_803EABA4;
extern Block_800BFAD0 *lbl_803EABA8;
extern unsigned char lbl_803EABB4;
extern unsigned char lbl_803EABB8;
extern unsigned char lbl_803EABB9;
extern unsigned char lbl_803EABD4;
extern unsigned char lbl_803EABD5;
extern int lbl_803EABE4;
extern unsigned char lbl_803EABE8;
extern Class_80297CE8 lbl_803EC914;
extern int lbl_802D9E90[3];
extern Entry_800C3130 lbl_8030FF40[3][50];
extern Record_800C432C lbl_803103F0[10];
}

extern "C" void fn_800BE3E8(int a, int kind)
{
    int team = fn_80178308();
    int other = fn_80178320();
    int skip;

    if (a == 255) {
        skip = 1;
    } else {
        int found = 0;

        if (fn_800B65A0(team) == a || fn_800B65A0(other) == a) {
            found = 1;
        }
        skip = found;
    }
    if (skip == 0) {
        switch (kind) {
        case 6: {
            Object_80039F5C *p = fn_800B6544(a);

            fn_800B6868(p->mId >> 8, p->mId >> 16, p->mUnknown8, 0);
            break;
        }
        case 9: {
            Object_80039F5C *p = fn_800B6544(a);

            fn_800B6868(p->mId >> 8, p->mId >> 16, p->mUnknown8, 1);
            break;
        }
        }
    }
}

int Class_80297CE8::vfn_12()
{
    int result = 0;

    if (lbl_803EABA8->mUnknownC5 != 0 && fn_8016E764() != 0) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800BE8E4(int team)
{
    if (team == fn_80178308()) {
        fn_80148154();
        fn_80148108(0);
    }
    if (team == fn_80178320() && fn_801481B0() == 0) {
        fn_80148108(1);
    }
}

extern "C" void fn_800BEFAC(int index)
{
    int state = lbl_803EABA8->mUnknownBC;

    switch (state) {
    case 0:
        if (lbl_803EABA8->mSlots[index].mUnknown8 > 0) {
            lbl_803EABA8->mSlots[index].mUnknown8--;
        } else if (fn_800744FC() != 0) {
            lbl_803EABA8->mUnknownBC = 1;
            lbl_803EABA8->mSlots[index].mUnknown8 = 30;
        }
        break;
    case 1:
        if (lbl_803EABA8->mSlots[index].mUnknown8 > 0) {
            lbl_803EABA8->mSlots[index].mUnknown8--;
        } else if (fn_800744FC() != 0) {
            fn_80162780(1, 1);
            lbl_803EABA8->mUnknownC6 = state;
            lbl_803EABA8->mSlots[index].mUnknown0 = lbl_803EABA8->mSlots[index].mUnknown4;
        }
        break;
    }
}

extern "C" void fn_800BF07C(void)
{
    short value = 0;
    int mode = lbl_803EABA8->mUnknown40;

    if (fn_8009D9D8(1) == 0) {
        mode = 0;
    }
    if (fn_8011F32C() == 0 && fn_8011F228() == 0 && fn_800B119C() != 0) {
        switch (mode) {
        case 0:
            if (fn_800BA6F8() != 0) {
                value = fn_8009D990(0) - 3;
            } else {
                value = fn_8009D990(0) - 4;
                value -= fn_802372EC(0, 4);
            }
            break;
        case 1:
            value = fn_8009D990(0) - 6;
            value -= fn_802372EC(0, 8);
            break;
        }
        if (value <= 4) {
            value = 0;
        } else if (value > 39) {
            value = 39;
        }
    }
    lbl_803EABA4->fn_800C02D4(value);
}

void Class_80297CE8::vfn_09()
{
    int count = fn_801383C8();
    int i;

    for (i = 0; i < count; i++) {
        Object_80137ABC *pBall = fn_80137ABC(i);
        Object_80039F5C *p = fn_80137AD0(pBall);

        if (p != 0 && p->mIdBytes[3] == 1) {
            fn_8013791C(pBall, 5, 0);
        }
    }
}

void Class_80297CE8::vfn_11()
{
    fn_8013FA8C(1);
    if (fn_800B65A0(0) == 255 && fn_800B65A0(1) == 255 && fn_8019623C(0x23000) != 0) {
        fn_80195EFC(1, 20, 0x808080, 0);
    }
    if (fn_8013F9F8() != 3) {
        fn_8013F97C(0);
        fn_8013C6F0(fn_8013FA04(5));
    }
}

extern "C" int fn_800BF45C(void *p, void *q)
{
    Block_800BFAD0 *pBlock = (Block_800BFAD0 *)p;
    Block_800BFAD0 *pOther = (Block_800BFAD0 *)q;
    if (pOther == 0) {
        return 0;
    }
    return fn_80238258(pBlock, pOther, 72) | fn_80238258(pBlock->mUnknown98, pOther->mUnknown98, 48);
}

extern "C" void fn_800BF4B8(void)
{
    Params_80096A58 params;

    lbl_803EABA8->mUnknown9C = -1;
    if (fn_800B65A0(0) == 255 && fn_800B65A0(1) == 255) {
        int mode = fn_80177F70();

        if (mode == 0) {
            fn_801C1F94(&params, 0, sizeof(params));
            params.mUnknown40 = 0xFFFF;
            params.mUnknown42 = 0xFFFF;
            params.mUnknown0 = 27;
            params.mUnknown20 = 2;
            params.mUnknown24 = mode;
            params.mUnknown28 = fn_802372EC(1, 11);
            lbl_803EABA8->mUnknown9C = fn_80096A58(&params);
            fn_801F0F18(0);
        }
    }
}

extern "C" int fn_800BF574(int a, unsigned int kind)
{
    int result = 0;

    if (kind >= 51 && kind <= 54) {
        return 0;
    }
    switch (kind) {
    case 0:
    case 6:
    case 7:
    case 8:
    case 9:
    case 14:
    case 15:
    case 89:
    case 90:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 119:
    case 120: {
        Block_800BFAD0 *p = lbl_803EABA8;

        if (p->mUnknownB0 == 2 || p->mUnknownB0 == fn_800B6644(a)) {
            if (fn_800A937C() == 0 || fn_800A9648() != 0) {
                lbl_803EABA8->mUnknownA8 = 1;
                result = 1;
            }
        }
        break;
    }
    }
    return result;
}

extern "C" void fn_800BF6CC(int index)
{
    lbl_803EABA8->mSlots[index].mUnknown1C = 0;
    fn_800BD35C();
    fn_8003A3F4(0, index);
}

extern "C" int fn_800BF718(int index)
{
    return lbl_803EABA8->mSlots[index].mUnknown1C;
}

extern "C" int fn_800BF824(void)
{
    int result = 0;

    if (lbl_803EABA8->mUnknownB8 > 30) {
        if (fn_80156704() == 0 && fn_801485D4() == 0 && fn_80025ACC() != 0) {
            fn_800AE904(3);
        }
        lbl_803EABA8->mUnknownB8 = -1;
    }
    if (fn_800AE980() != 0) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800BFAB4(Class_80297CE8 *p)
{
    if (p == 0) {
        lbl_803EABA4 = &lbl_803EC914;
    } else {
        lbl_803EABA4 = p;
    }
}

void Class_80297CE8::vfn_03()
{
    fn_800BFAB4(0);
}

void Class_80297CE8::vfn_10()
{
    fn_800B6B98();
}

short Class_80297CE8::fn_800C02C8()
{
    return lbl_803EABA8->mUnknownA4;
}

void Class_80297CE8::fn_800C02D4(short value)
{
    lbl_803EABA8->mUnknownA4 = value;
}

short Class_80297CE8::fn_800C02E0()
{
    return lbl_803EABA8->mUnknownA6;
}

void Class_80297CE8::fn_800C02EC(short value)
{
    lbl_803EABA8->mUnknownA6 = value;
}

extern "C" void fn_800BF174(void);

void Class_80297CE8::fn_800C02F8(int value)
{
    lbl_803EABA8->mUnknown40 = value;
    if (fn_800AD9B4() == 2) {
        fn_800BF174();
    }
}

void Class_80297CE8::vfn_07()
{
}

int Class_80297CE8::fn_800C0414()
{
    return lbl_803EABA8->mUnknown40;
}

unsigned char Class_80297CE8::fn_800C0420(int index)
{
    return lbl_803EABA8->mSlots[index].mUnknown0 == 4;
}

unsigned char Class_80297CE8::fn_800C043C(int index)
{
    return lbl_803EABA8->mSlots[index].mUnknown0 == 8;
}

unsigned char Class_80297CE8::fn_800C0458()
{
    return lbl_803EABA8->mUnknownA8;
}

extern "C" int fn_800C0464(void)
{
    int result = 0;

    if (lbl_803EABA8 != 0 && lbl_803EABA8->mUnknownC5 != 0) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800C05F4(void)
{
    if (lbl_803EABA8->mUnknownAB != 0) {
        if (fn_800289A8() >= lbl_803EABA8->mUnknownAC + 15) {
            lbl_803EABA8->mUnknownAC = 0;
            lbl_803EABA8->mUnknownAB = 0;
            return 0;
        }
        return 1;
    }
    return 0;
}

extern "C" unsigned char fn_800C0658(void)
{
    return lbl_803EABB4;
}

extern "C" unsigned short fn_800C0660(unsigned short *p, int value)
{
    unsigned short i = 0;

    if (*p != value) {
        do {
            i++;
            p++;
        } while (i <= 6 && *p != value);
    }
    return i;
}

extern "C" QueryCursor fn_800C0750(unsigned char index, unsigned short *pValues)
{
    int i;

    fn_8017CBFC(index);
    for (i = 0; i <= 6; i++) {
        pValues[i] = fn_8017CD44(i);
    }
    fn_8017CD20();
    return fn_800C0698(index, pValues);
}

extern "C" void fn_800C07C4(QueryCursor cursor)
{
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
}

extern "C" int fn_800C1180(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;
    signed char result = 0;

    switch (pState->mId) {
    case 40:
        result = pState->mUnknown1;
        break;
    case 92:
        result = pState->mUnknown1;
        break;
    }
    return result;
}

extern "C" unsigned char fn_800C13A0(State_80039F5C *pState, unsigned char *pA, unsigned char *pB)
{
    unsigned char result = 2;
    Block_8011F4EC *pBlock = fn_8011F4EC();
    unsigned char i;
    int id = pState->mUnknown1;

    for (i = 0; i <= 2; i++) {
        if (pBlock->mUnknown1C1[i] == id) {
            break;
        }
    }
    if (i != 3 && fn_801787A0() == 0) {
        unsigned char state[4];

        fn_80168E00(fn_80178308(), i, state);
        if (id != 255 && state[0] != 0) {
            result = pBlock->mUnknown1B8[i];
            *pA = pBlock->mUnknown1BB[i];
            *pB = pBlock->mUnknown1BE[i];
        }
    }
    return result;
}

extern "C" void fn_800C1C34(void)
{
    Block_8011F4EC *pBlock = fn_8011F4EC();
    unsigned char i;

    pBlock->mUnknown1C4 = 0;
    for (i = 0; i <= 2; i++) {
        pBlock->mUnknown1B8[i] = 2;
        pBlock->mUnknown1BB[i] = 0;
        pBlock->mUnknown1BE[i] = 20;
        pBlock->mUnknown1C1[i] = 255;
    }
}

extern "C" int fn_800C1E40(void)
{
    return lbl_803EABB8;
}

extern "C" unsigned char fn_800C1E48(void)
{
    return lbl_803EABB9;
}

extern "C" void fn_800C1E50(void)
{
    lbl_803EABB8 = 0;
}

extern "C" void fn_800C2090(void)
{
    fn_8013FA8C(1);
    fn_8013F97C(0);
    fn_8013FA58(1, fn_801374D4());
    fn_800AFDD4(fn_800C1E5C);
}

extern "C" void fn_800C20D8(void)
{
}

extern "C" void fn_800C20DC(void)
{
    fn_800AFE20(fn_800C1E5C);
    fn_800BA804(0);
}

extern "C" int fn_800C210C(int *p, int offset, int *pValue)
{
    int changed = 0;
    int value = *pValue - offset;

    if (value > p[1]) {
        value = p[1];
        changed = 1;
    } else if (value < p[0]) {
        value = p[0];
        changed = 1;
    }
    *pValue = value + offset;
    return changed;
}

extern "C" int fn_800C2F94(Entry_800C3130 *pA, Entry_800C3130 *pB)
{
    if (pA->mpUnknown0->mUnknown8 > pB->mpUnknown0->mUnknown8) {
        return -1;
    }
    return 0;
}

extern "C" void fn_800C2FB8(Entry_800C3130 *pA, Entry_800C3130 *pB)
{
    Entry_800C3130 entry = *pA;

    *pA = *pB;
    *pB = entry;
}

extern "C" void fn_800C310C(void)
{
    unsigned int i;

    for (i = 0; i < 3; i++) {
        lbl_802D9E90[i] = 0;
    }
}

extern "C" void fn_800C3130(Item_800C2F94 *pItem, short a, unsigned short b, int index)
{
    lbl_8030FF40[index][lbl_802D9E90[index]].mpUnknown0 = pItem;
    lbl_8030FF40[index][lbl_802D9E90[index]].mUnknown4 = a;
    lbl_8030FF40[index][lbl_802D9E90[index]].mUnknown6 = b;
    lbl_802D9E90[index]++;
}

extern "C" void fn_800C3170(void)
{
    unsigned int i;

    for (i = 0; i < 3; i++) {
        fn_801F51DC(1, lbl_8030FF40[i], lbl_802D9E90[i], sizeof(Entry_800C3130), fn_800C2F94, fn_800C2FB8, 0, 0);
    }
}

extern "C" void fn_800C3610(float value)
{
    if (lbl_803EABD4 != 0) {
        lbl_803EABD4 = 0;
        fn_8002885C();
    } else {
        while (fn_8017D064(7) != 0) {
            fn_8017CFB4(7);
        }
        fn_800AD910(5, value);
    }
}

extern "C" void fn_800C3678(void)
{
    fn_8013F9B8();
    fn_8010A220();
    fn_801789F8();
    lbl_803EABD5 = 0;
}

extern "C" int fn_800C4184(Object_80039F5C *p)
{
    if (p->mUnknown8 != 255) {
        return 0;
    }
    if (p->mFlags & 0x800) {
        return 0;
    }
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 12:
    case 15:
    case 16:
    case 17:
    case 19:
    case 20:
    case 22:
    case 25:
    case 26:
    case 27:
    case 32:
    case 36:
    case 40:
    case 50:
    case 57:
    case 88:
    case 92:
    case 94:
        return 0;
    case 34:
    case 58: {
        unsigned int kind = fn_801BE648(p->mpUnknown792);

        switch (kind) {
        case 195:
        case 196:
        case 197:
        case 210:
        case 224:
        case 229:
        case 235:
            return 0;
        }
        break;
    }
    case 28: {
        int unknown;
        int handle;

        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        if (fn_8009A578(handle) == 5) {
            return 0;
        }
        if (((handle >> 29) & 3) == 1) {
            return 0;
        }
        break;
    }
    }
    return 1;
}

extern "C" void fn_800C432C(void)
{
    fn_801BBC3C(1, 196, &lbl_803103F0[0]);
    fn_801BBC3C(1, 197, &lbl_803103F0[1]);
    fn_801BBC3C(1, 195, &lbl_803103F0[2]);
    fn_801BBC3C(1, 210, &lbl_803103F0[3]);
    fn_801BBC3C(1, 224, &lbl_803103F0[4]);
    fn_801BBC3C(1, 228, &lbl_803103F0[5]);
    fn_801BBC3C(1, 230, &lbl_803103F0[6]);
    fn_801BBC3C(1, 229, &lbl_803103F0[7]);
    fn_801BBC3C(1, 235, &lbl_803103F0[8]);
    fn_801BBC3C(1, 237, &lbl_803103F0[9]);
}

extern "C" void fn_800C4410(int value)
{
    if (value > 41) {
        value = 41;
    }
    lbl_803EABE4 = value;
    lbl_803EABE8 = 1;
}

extern "C" void fn_800C442C(void)
{
    lbl_803EABE8 = 0;
}

extern "C" void fn_800C4438(Sequence_800C4460 *p)
{
    fn_801C1F94(p, 0, sizeof(Sequence_800C4460));
}

extern "C" void fn_800C4460(Sequence_800C4460 *p)
{
    if (p->mUnknown101 < p->mUnknown100) {
        Step_800C4460 *pStep = &p->mSteps[p->mUnknown101];

        if (pStep->mpCallback0 != 0 && pStep->mpCallback0(pStep->mUnknown10) == 0) {
            p->mUnknown101++;
            fn_800C4460(p);
        }
    } else {
        p->mUnknown100 = 0;
    }
}

extern "C" void fn_800C4568(Sequence_800C4460 *p);

extern "C" void fn_800C44E0(Sequence_800C4460 *p)
{
    if (p->mUnknown101 < p->mUnknown100) {
        Step_800C4460 *pStep = &p->mSteps[p->mUnknown101];

        if (pStep->mpCallback4 != 0 && pStep->mpCallback4(pStep->mUnknown10) == 0) {
            fn_800C4568(p);
            p->mUnknown101++;
            fn_800C4460(p);
        }
    } else {
        p->mUnknown100 = 0;
    }
}

extern "C" void fn_800C4568(Sequence_800C4460 *p)
{
    if (p->mUnknown101 < p->mUnknown100) {
        Step_800C4460 *pStep = &p->mSteps[p->mUnknown101];

        if (pStep->mpCallback8 != 0) {
            pStep->mpCallback8(pStep->mUnknown10);
        }
    } else {
        p->mUnknown100 = 0;
    }
}

extern "C" Step_800C4460 *fn_800C4658(Sequence_800C4460 *p)
{
    Step_800C4460 *pStep = &p->mSteps[p->mUnknown100];

    fn_801C1F94(pStep, 0, sizeof(Step_800C4460));
    return pStep;
}

extern "C" void fn_800C46A0(Sequence_800C4460 *p)
{
    p->mUnknown100++;
}

