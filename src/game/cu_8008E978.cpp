#include <string.h>

#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Input_800B6D34.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
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

extern "C" int fn_800A9648(void)
{
    return fn_800927BC((unsigned char)lbl_8030F42C.mUnknown14[lbl_8030F42C.mUnknownC]);
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
