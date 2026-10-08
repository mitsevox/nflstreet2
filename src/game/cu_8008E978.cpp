#include <string.h>

#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_803EC99C.h"
#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80064864.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8008E978.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_80178D18.h"
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

/* Halfword-counted set whose 20-byte entries start at +8. */
struct Entry_800CCBA0 {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
    unsigned char mUnknown3[17];
};

struct Set_800CCBA0 {
    unsigned char mUnknown0[4];
    unsigned short mCount;
    unsigned char mUnknown6[2];
    Entry_800CCBA0 mEntries[1];
};

/* One of the five 24-byte items per side of Table_800CA8EC. */
struct Item_800CAA8C {
    int mUnknown0;
    unsigned char mUnknown4[4];
    int mUnknown8;
    unsigned char mUnknown12[12];
};

/* Data that the .sdata word 0x803EAC3C points to. */
struct Table_800CA8EC {
    unsigned char mUnknown0[12];
    unsigned int mCounts[2];
    Item_800CAA8C mItems[2][5];
};

struct Info_800CAC14 {
    unsigned char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
};

/* Two floats written by fn_80227690. */
struct Delta_800CC6A8 {
    float mX;
    float mY;
};

/* Group of players: the first and up to seven others from +4. */
struct Group_800CC98C {
    Object_80039F5C *mpUnknown0;
    Object_80039F5C *mpUnknown4[7];
    unsigned char mUnknown32[4];
    int mUnknown36;
    unsigned char mUnknown40[12];
    unsigned short mUnknown52;
    unsigned char mUnknown54[3];
    unsigned char mUnknown57;
    unsigned char mUnknown58;
    unsigned char mUnknown59;
};

struct Node_800CCEBC {
    unsigned char mUnknown0[3];
    unsigned char mUnknown3;
    int mUnknown4;
};

struct Play_800CCEBC {
    unsigned char mUnknown0[16];
    Node_800CCEBC *mpUnknown16;
    Node_800CCEBC *mpUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
    int mUnknown36;
    unsigned char mUnknown40;
    unsigned char mUnknown41;
};

extern "C" {
int fn_800BA6F8(void);
void fn_801783D0(int bit, int on);
int fn_801783AC(int bit);
int fn_80178320(void);
void fn_800FF6D8(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
int fn_80113BCC(Object_80039F5C *p);
int fn_80114DE0(Object_80039F5C *p);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_800EC758(Object_80039F5C *p);
int fn_800C76C0(Object_80039F5C *p);
int fn_8011E9B4(Object_80039F5C *p);
int fn_801BE648(void *p);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
int fn_800C91B0(Object_80039F5C *p);
int fn_800C91F0(Object_80039F5C *p, unsigned char *pOut, int which);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
void fn_800CC0C0(int team);
void fn_800CC180(int team);
void fn_800CC2D4(void);
void fn_800CC388(Object_80039F5C *p);
int fn_800CCD20(Group_800CC98C *pGroup, Play_800CCEBC *pPlay);
int fn_800CD0BC(Group_800CC98C *pGroup, Play_800CCEBC *pPlay, int a);

extern Table_800CA8EC *lbl_803EAC3C;
extern int lbl_803EAC48;
extern int (*lbl_8029804C[])(Object_80039F5C *p);
}

extern "C" Table_800CA8EC *fn_800CA8EC(void)
{
    return lbl_803EAC3C;
}

extern "C" void fn_800CA8F4(Object_80039F5C *p)
{
    if (fn_800C91F0(p, 0, 0) != 0 && fn_800C91B0(p) != 2) {
        if ((p->mFlags & 0x4000) == 0 && p->mUnknown512.mUnknown15 == 1 && fn_800CA5CC(p, 0, 1) == 0) {
            p->mUnknown512.mUnknown15 = 0;
        }
    } else {
        switch (p->mUnknown512.mUnknown15) {
        case 1:
        case 7:
        case 9:
        case 21:
            p->mUnknown512.mUnknown15--;
            break;
        }
    }
}

extern "C" int fn_800CAA6C(int value)
{
    if (value == 9 || value == 7) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800CAA8C(int index, unsigned int item)
{
    int result = 0;

    if (item < lbl_803EAC3C->mCounts[index]) {
        result = lbl_803EAC3C->mItems[index][item].mUnknown0;
    }
    return result;
}

extern "C" int fn_800CAAC4(int index, unsigned int item)
{
    if (item >= lbl_803EAC3C->mCounts[index]) {
        return -1;
    }
    return lbl_803EAC3C->mItems[index][item].mUnknown8;
}

extern "C" int fn_800CABF4(Object_80039F5C *p, unsigned char *pOut, int which)
{
    return fn_800C91F0(p, pOut, which);
}

extern "C" int fn_800CAC14(Info_800CAC14 *p, int swap)
{
    int value;

    if (lbl_803EAC48 == 143) {
        value = p->mUnknown4;
    } else {
        value = p->mUnknown6;
    }
    if (swap != 0) {
        if (value == 1) {
            value = 2;
        } else if (value == 2) {
            value = 1;
        }
    }
    return value;
}

extern "C" void fn_800CC244(Object_80039F5C *p)
{
    if (p->mpState->mId == 63) {
        fn_800FF6D8(p);
    } else {
        if (fn_80137C48(p) != 0 && fn_80137B40() == p) {
            fn_8013791C(fn_80137C48(p), 5, 0);
        }
        fn_800EFE60(0, p->mpState, p);
        fn_800CC388(p);
        fn_800FF6D8(p);
    }
}

extern "C" void fn_800CC404(void)
{
    if (fn_800BA6F8() == 0) {
        fn_800CC0C0(0);
        fn_800CC0C0(1);
        fn_801783D0(18, 1);
    }
}

extern "C" void fn_800CC448(void)
{
    fn_801783D0(18, 0);
}

extern "C" void fn_800CC470(void)
{
    if (fn_801783AC(18)) {
        fn_800CC180(0);
        fn_800CC180(1);
        fn_800CC448();
    }
}

extern "C" void fn_800CC560(int mode)
{
    unsigned int i;
    unsigned int count;

    if (fn_800BA6F8() == 0) {
        switch (mode) {
        case 0:
            break;
        case 1:
            fn_800CC2D4();
            break;
        }
        fn_800CC448();
        fn_800CC404();
        count = fn_80178D70(0);
        for (i = 0; i < count; i++) {
            fn_800CC244(fn_80039F5C(0, i));
        }
        count = fn_80178D70(1);
        for (i = 0; i < count; i++) {
            fn_800CC244(fn_80039F5C(1, i));
        }
    }
}

extern "C" int fn_800CC618(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mpState->mId) {
    case 16:
        if (fn_80114DE0(p) != 0) {
            result = 1;
        } else {
            result = (p->mFlags >> 19) & 1;
        }
        break;
    case 17:
        break;
    case 32:
        if (p->mUnknown1032 == 6 && p->mUnknown344 != 0) {
            result = 1;
        }
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" int fn_800CC6A8(Object_80039F5C *p)
{
    int result = 0;
    int check = 0;

    switch (p->mpState->mId) {
    case 16:
        if (fn_80114DE0(p) != 0) {
            result = 1;
        } else {
            result = (p->mFlags >> 19) & 1;
        }
        break;
    case 17:
        break;
    case 32:
        if (p->mUnknown1032 == 6 && p->mUnknown344 != 0) {
            result = 1;
            check = 1;
        }
        break;
    default:
        result = 1;
        if (fn_8011E9B4(p) != 0) {
            check = 1;
        }
        break;
    }
    if (check && p->mIdBytes[2] == fn_80178320()) {
        Object_80039F5C *pCarrier = fn_80137B40();

        if (pCarrier != 0) {
            Object_80039F5C *pTarget = fn_8009BCE8(&p->mUnknown1036);

            if (pTarget != 0) {
                Delta_800CC6A8 delta;
                Delta_800CC6A8 carrierDelta;
                int angle;

                fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
                angle = fn_801CFE40(delta.mY, delta.mX);
                fn_80227690(&carrierDelta, &pCarrier->mMotion.mPos, &pTarget->mMotion.mPos);
                if (fn_801CFFD0(angle, fn_801CFE40(carrierDelta.mY, carrierDelta.mX)) > 0x4E38E3) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800CC800(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mpState->mId) {
    case 10:
    case 11:
    case 12:
    case 15:
    case 16:
        break;
    case 57:
        result = fn_800EC758(p);
        break;
    case 17:
        if (fn_80114E7C(p) != 0) {
            result = 1;
        }
        break;
    case 32:
        if (p->mUnknown1032 == 6) {
            if (p->mUnknown344 != 0) {
                result = 1;
            }
        } else if (p->mUnknown1032 == 7) {
            result = 1;
        }
        break;
    default:
        result = 1;
        break;
    }
    if (fn_801BE648(p->mpUnknown792) == 185) {
        result = 0;
    }
    if (fn_800C76C0(p) != 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_800CC8F0(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mpState->mId) {
    case 17:
        result = fn_80113BCC(p);
        break;
    case 16:
        if (fn_80114DE0(p) != 0) {
            result = 1;
        } else {
            result = (p->mFlags >> 19) & 1;
        }
        break;
    case 32:
        if (p->mUnknown1032 == 6 && p->mUnknown344 != 0) {
            result = 1;
        }
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" int fn_800CC98C(Group_800CC98C *pGroup, int index)
{
    int (*pCallback)(Object_80039F5C *p) = lbl_8029804C[index];
    int result = 0;
    unsigned short i;

    if (pCallback(pGroup->mpUnknown0) != 0 && pCallback(pGroup->mpUnknown4[0]) != 0) {
        result = 1;
        for (i = 0; i <= 6; i++) {
            if (pGroup->mpUnknown4[i] != 0 && i != 0 && lbl_8029804C[index](pGroup->mpUnknown4[i]) == 0) {
                pGroup->mpUnknown4[i] = 0;
            }
        }
    }
    return result;
}

extern "C" unsigned short fn_800CCBA0(Set_800CCBA0 *pSet, int kind)
{
    unsigned short second = 0;
    unsigned short first = 0;
    unsigned int i;

    for (i = 0; i < pSet->mCount; i++) {
        if (pSet->mEntries[i].mUnknown2 == 0) {
            first++;
        } else {
            second++;
        }
    }
    if (kind == 0) {
        return first;
    }
    return second;
}

extern "C" int fn_800CCC04(Group_800CC98C *pGroup, Play_800CCEBC *pPlay)
{
    int result = 0;
    int angle;

    if (pGroup->mUnknown57 != 0) {
        angle = (pPlay->mpUnknown16->mUnknown4 - pPlay->mpUnknown20->mUnknown4) & 0xFFFFFF;
    } else {
        angle = (pPlay->mpUnknown20->mUnknown4 - pPlay->mpUnknown16->mUnknown4) & 0xFFFFFF;
    }
    if (fn_801CFFD0(angle, (pPlay->mUnknown24 - pPlay->mUnknown28) & 0xFFFFFF) < pGroup->mUnknown36) {
        result = 1;
    }
    if (result == 0) {
        if (fn_801CFFD0(angle, (pPlay->mUnknown32 - pPlay->mUnknown36) & 0xFFFFFF) < pGroup->mUnknown36) {
            result = 1;
        }
        if (result == 0) {
            if (fn_801CFFD0(angle, (pPlay->mUnknown24 - pPlay->mUnknown36) & 0xFFFFFF) < pGroup->mUnknown36) {
                result = 1;
            }
            if (result == 0) {
                if (fn_801CFFD0(angle, (pPlay->mUnknown32 - pPlay->mUnknown28) & 0xFFFFFF) < pGroup->mUnknown36) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800CCEBC(Group_800CC98C *pGroup, Play_800CCEBC *pPlay)
{
    int result = 0;
    int a = pPlay->mpUnknown16->mUnknown3;
    int b = pPlay->mpUnknown20->mUnknown3;

    if (pPlay->mUnknown41 == 2) {
        result = a == 5;
    } else if (pGroup->mUnknown52 == 175) {
        result = 1;
    } else if (a != 5) {
        switch (pPlay->mUnknown40) {
        case 2:
            if (b == 3) {
                result = 1;
                break;
            }
        case 1:
            if (b == 2) {
                result = 1;
            }
            break;
        case 0:
            switch (pGroup->mUnknown52) {
            case 93:
            case 94:
                result = 1;
                break;
            default:
                if (b != 2 && b != 3) {
                    result = 1;
                }
                break;
            }
            break;
        default:
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int fn_800CD21C(Group_800CC98C *pGroup, Play_800CCEBC *pPlay, int a)
{
    int result = 0;

    if (fn_800CCEBC(pGroup, pPlay) != 0 && fn_800CCC04(pGroup, pPlay) != 0 && fn_800CCD20(pGroup, pPlay) != 0) {
        result = 1;
    }
    if (result != 0 && pGroup->mUnknown59 != 0) {
        result = fn_800CD0BC(pGroup, pPlay, a);
    }
    return result;
}

extern "C" void fn_800CE674(Object_800CE674 *p)
{
    p->mUnknown0 = -1;
    p->mUnknown2 = -1;
}

extern "C" void fn_800CE684(Object_800CE674 *p)
{
    p->mUnknown3 = -1;
}

extern "C" int fn_800CE690(Object_800CE674 *p)
{
    switch (p->mUnknown0) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 3;
    case 5:
        return 4;
    case 6:
        return 5;
    case 7:
        return 6;
    case 8:
        return 7;
    case 9:
        return 8;
    }
    return 0;
}

extern "C" int fn_800CF090(Object_80039F5C *p)
{
    int result = 0;

    if ((p->mpState->mId == 36 || fn_801BE648(p->mpUnknown792) == 229 || fn_801BE648(p->mpUnknown792) == 237)
        && p->mUnknown361[0] == 0) {
        result = 2;
    }
    return result;
}

extern "C" void fn_800CF35C(float dt)
{
    lbl_803EABA4->vfn_04(dt);
}

extern "C" void fn_800CF394(float dt)
{
    lbl_803EABA4->vfn_05(dt);
}

extern "C" void fn_800CF3CC(float dt)
{
    lbl_803EABA4->vfn_06(dt);
}

extern "C" void fn_800CF404(float dt)
{
    lbl_803EAB84->vfn_03(dt);
}

extern "C" void fn_800CF43C(float dt)
{
    lbl_803EAB84->vfn_04(dt);
}

extern "C" void fn_800CF474(float dt)
{
    lbl_803EAB84->vfn_05();
}

extern "C" void fn_800CF4AC(float dt)
{
    lbl_803EAB90->vfn_03();
}

extern "C" void fn_800CF4E4(float dt)
{
    lbl_803EAB90->vfn_04(dt);
}

extern "C" void fn_800CF51C(float dt)
{
    lbl_803EAB90->vfn_05();
}

extern "C" void fn_800CF554(float dt)
{
    lbl_803EAA8C->vfn_03();
}

extern "C" void fn_800CF58C(float dt)
{
    lbl_803EAA8C->vfn_04(dt);
}

extern "C" void fn_800CF5C4(float dt)
{
    lbl_803EAA8C->vfn_05();
}

extern "C" void fn_800CF5FC(float dt)
{
    lbl_803EAB38->vfn_03();
}

extern "C" void fn_800CF634(float dt)
{
    lbl_803EAB38->vfn_04(dt);
}

extern "C" void fn_800CF66C(float dt)
{
    lbl_803EAB38->vfn_05();
}

extern "C" void fn_800CF6A4(float dt)
{
    lbl_803EA9E4->vfn_03();
}

extern "C" void fn_800CF6DC(float dt)
{
    lbl_803EA9E4->vfn_04(dt);
}

extern "C" void fn_800CF714(float dt)
{
    lbl_803EA9E4->vfn_05();
}

extern "C" void fn_800CF74C(float dt)
{
    lbl_803EAC9C->fn_800CFF4C();
}

extern "C" void fn_800CF784(float dt)
{
    lbl_803EAC9C->fn_800CFFC4(dt);
}

extern "C" void fn_800CF7BC(float dt)
{
    lbl_803EAC9C->fn_800D0394();
}
