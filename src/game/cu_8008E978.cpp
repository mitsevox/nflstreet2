#include <string.h>

#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"
#include "game/Team_80167A8C.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
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

/* One of the 36-byte entries at +4 and +40 of Block_800B21D0, filled by
   fn_800B206C. */
struct Entry_800B206C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23[1];
};

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
        int handle = lbl_803EAB18;
        Record_800B15FC *pRecord = (Record_800B15FC *)fn_80238540(handle, fn_80238604(handle));

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
