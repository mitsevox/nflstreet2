#include <string.h>

#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80064864.h"
#include "game/cu_8008E978.h"
#include "game/fn_8007F828.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C68FC.h"
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

/* 20-byte records of the .data table at 0x802D82E0. */
struct Record_802D82E0 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2[2];
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    unsigned char mUnknownA[2];
    unsigned int mUnknownC;
    int mUnknown10;
};

/* 620-byte block allocated under the id 'hrte' (fn_800AEB1C). */
struct Block_800AEB1C {
    Message_800F01CC mMessages[2][7][10];
    Object_80039F5C *mpObjects[2][7];
    unsigned char mUnknown268[2];
    unsigned char mUnknown26A[2];
};

extern "C" {
void fn_800ADA1C(void);
void fn_800AE138(int index);
int fn_800B65A0(int team);
int fn_800B6644(int index);
int fn_80177C38(void);
int fn_80178308(void);
int fn_80178348(void);
int fn_80178360(void);
unsigned char fn_80194F24(void);
void fn_80194F1C(unsigned char enabled);
void fn_80194C5C(int a, int b, int c);
int fn_801C6458(int a, int b);
int fn_801E195C(int a);
void fn_8017DDDC(int index);
void fn_800EFE1C(int a, State_80039F5C *pQueue);
void fn_8011E3EC(Object_80039F5C *p, int a);
void fn_8011E240(Object_80039F5C *p);

extern void (*lbl_8030F51C[6])(void);
extern unsigned char lbl_8030F9DC[15];
extern unsigned char lbl_8030F9EC[15];
extern Record_802D82E0 lbl_802D82E0[15];
extern unsigned char lbl_803EAAE8;
extern unsigned char lbl_803EAAE9;
extern int lbl_803EAAEC;
extern unsigned char lbl_803EAAF0;
extern unsigned char lbl_803EAAF1;
extern Block_800AEB1C *lbl_803EAAF4;
extern int lbl_803EAAF8[2];
extern int lbl_803EC96C;
extern int lbl_803EC970;
}

extern "C" void fn_800AE10C(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        lbl_8030F51C[i] = fn_800ADA1C;
    }
}

extern "C" void fn_800AE65C(void)
{
    unsigned char saved = fn_80194F24();

    fn_80194F1C(1);
    if (fn_8007F828(9) != 0) {
        unsigned int i;

        for (i = 0; i <= 9; i++) {
            if (fn_801E195C(fn_801C6458(i, 0)) == 2 && fn_800B6644(i) != 255) {
                fn_80194C5C(i, 127, 20);
            }
        }
    }
    fn_80194F1C(saved);
}

extern "C" void fn_800AE6F0(void)
{
    if (lbl_803EAAE8 != 0) {
        int index;

        fn_800AE138(lbl_803EAAEC);
        index = lbl_803EAAEC;
        lbl_803EC970 = 0;
        lbl_8030F9DC[index] = 1;
        if (index == 1 || index == 2) {
            lbl_8030F9DC[1] = 1;
            lbl_8030F9DC[2] = 1;
        }
    }
}

extern "C" void fn_800AE750(int index, int team)
{
    if (fn_800B65A0(team) != 255) {
        lbl_8030F9DC[index] = 1;
    }
}

extern "C" void fn_800AE798(int index, int team)
{
    if (fn_800B65A0(team) != 255 && lbl_8030F9DC[index] == 0) {
        lbl_8030F9EC[index] = 0;
    }
}

extern "C" void fn_800AE7F0(int index, int team, Object_80039F5C *p)
{
    if (fn_800B65A0(team) == 255 && (index == 1 || index == 2)) {
        index = 3;
        team = team == 0;
    }
    if (fn_800B65A0(team) != 255) {
        int flag = 0;

        if (lbl_802D82E0[index].mUnknown9 == 0 || p == 0 || (p->mFlags & 0x4000) != 0) {
            flag = 1;
        }
        if (flag && lbl_8030F9EC[index] != 1) {
            lbl_8030F9EC[index] = 1;
        }
    }
}

extern "C" void fn_800AE8B4(void)
{
    lbl_803EC96C = 0;
    lbl_803EC970 = 0;
    if (lbl_803EAAF1 != 0) {
        int i;

        for (i = 0; i < 15; i++) {
            lbl_8030F9DC[i] = 0;
            lbl_8030F9EC[i] = 0;
        }
        lbl_803EAAF1 = 1;
    }
}

extern "C" void fn_800AE904(int index)
{
    if ((fn_8007F828(15) != 0 || index == 14) && lbl_8030F9DC[index] == 0) {
        lbl_803EAAEC = index;
        lbl_803EAAE8 = 1;
        fn_800AE6F0();
    }
}

extern "C" int fn_800AE968(int index)
{
    return lbl_8030F9DC[index];
}

extern "C" int fn_800AE978(void)
{
    return lbl_803EAAE8;
}

extern "C" int fn_800AE980(void)
{
    return lbl_803EAAE9;
}

extern "C" void fn_800AE988(void)
{
    lbl_803EAAE8 = 0;
    lbl_803EAAE9 = 0;
}

extern "C" void fn_800AE9A4(void)
{
    int team;

    if ((fn_80177C38() & 1) == 0) {
        team = fn_80178348();
    } else {
        team = fn_80178360();
    }
    if (fn_800B65A0(team) != 255) {
        lbl_803EAAF0 = 1;
    }
}

extern "C" void fn_800AE9EC(void)
{
    lbl_803EAAF0 = 0;
}

extern "C" void fn_800AEA70(Object_80039F5C *p, Message_800F01CC *pMessages)
{
    int count = 0;

    fn_801C1F94(&pMessages[count], 0, sizeof(Message_800F01CC));
    pMessages[count].mId = 31;
    pMessages[count].mUnknown1[0] = 48;
    count++;
    fn_801C1F94(&pMessages[count], 0, sizeof(Message_800F01CC));
    pMessages[count].mId = 19;
    pMessages[count].mUnknown1[0] = 40;
    pMessages[count].mUnknown1[1] = 32;
    pMessages[count].mUnknown1[2] = 255;
    count++;
    fn_801C1F94(&pMessages[count], 0, sizeof(Message_800F01CC));
    pMessages[count].mId = 21;
    count++;
    fn_801C1F94(&pMessages[count], 0, sizeof(Message_800F01CC));
    pMessages[count].mId = 0;
}

extern "C" void fn_800AEB1C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAAF4, sizeof(Block_800AEB1C), 0, 0x68727465);
    Block_800AEB1C *pBlock = (Block_800AEB1C *)fn_8023816C(pHandle);

    fn_801C1F94(pBlock->mpObjects, 0, sizeof(pBlock->mpObjects));
    fn_801C1F94(pBlock->mMessages, 0, sizeof(pBlock->mMessages));
    pBlock->mUnknown268[0] = 0;
    pBlock->mUnknown268[1] = 0;
    fn_802381E0(pHandle);
}

extern "C" void fn_800AEB9C(void)
{
}

extern "C" Message_800F01CC *fn_800AEE20(Object_80039F5C *p)
{
    Message_800F01CC *pFound = 0;
    unsigned char team = p->mIdBytes[2];
    unsigned int count = fn_80178D18(team);
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *pObject = lbl_803EAAF4->mpObjects[team][i];

        if (pObject != 0 && pObject == p) {
            pFound = lbl_803EAAF4->mMessages[team][i];
            break;
        }
    }
    return pFound;
}

extern "C" void fn_800AEEDC(int team)
{
    fn_801C1F94(lbl_803EAAF4->mpObjects[team], 0, sizeof(lbl_803EAAF4->mpObjects[team]));
    fn_801C1F94(lbl_803EAAF4->mMessages[team], 0, sizeof(lbl_803EAAF4->mMessages[team]));
}

extern "C" void fn_800AEF38(int team)
{
    if (lbl_803EAAF4->mUnknown268[team] != 0) {
        lbl_803EAAF4->mUnknown268[team] = 0;
    }
    fn_8017DDDC(team);
}

extern "C" void fn_800AEF74(Object_80039F5C *p, Message_800F01CC *pMessages)
{
    unsigned char i;
    int result = 0xFFFF;

    for (i = 0; i <= 1 && result == 0xFFFF; i++) {
        result = fn_800F06F4(0, p->mpState, (unsigned char)lbl_803EAAF8[i], 0xFFFF);
    }
    if (result != 0xFFFF) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
    }
    fn_800EFE1C(0, p->mpState);
    for (i = 0; pMessages[i].mId != 0; i++) {
        if (i == 0) {
            fn_800F053C(0, p->mpState, &pMessages[i], p);
        } else {
            fn_800F03D8(0, p->mpState, &pMessages[i], p);
        }
    }
}

extern "C" int fn_800AF078(int team)
{
    return lbl_803EAAF4->mUnknown268[team];
}

extern "C" void fn_800AF088(void)
{
    int team = fn_80178308();
    unsigned int count = fn_80178D18(team);
    unsigned char i;

    for (i = 0; i < count; i++) {
        if (lbl_803EAAF4->mpObjects[team][i] != 0
            && (lbl_803EAAF4->mMessages[team][i][0].mId == 31 || lbl_803EAAF4->mMessages[team][i][1].mId == 31)) {
            lbl_803EAAF4->mpObjects[team][i] = 0;
            fn_801C1F94(lbl_803EAAF4->mMessages[team][i], 0, sizeof(lbl_803EAAF4->mMessages[team][i]));
        }
    }
}

/* 16-byte items of the pool at lbl_803EAB00 (fn_800AF1BC). */
struct Item_800AF13C {
    void *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknownC[4];
};

/* 6-byte records of the array that Mesh_800AF2AC +48 points to. */
struct Vertex_800AF2AC {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
};

/* 8-byte source records read by fn_800AF2AC; +6 indexes the destination. */
struct Source_800AF2AC {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
};

struct Count_800AF2AC {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
};

struct Mesh_800AF2AC {
    unsigned char mUnknown0[48];
    Vertex_800AF2AC *mpUnknown30;
};

/* 24-byte block allocated by fn_800AF630 at lbl_803EC978. */
struct Table_800AF71C {
    unsigned int mCount;
    void *mpUnknown4[5];
};

/* 64-byte entries; fn_800AF804 clears three of them. */
struct Entry_800AF82C {
    void *mpUnknown0;
    unsigned char mUnknown4[44];
    int mUnknown30[3];
    unsigned char mUnknown3C;
    unsigned char mUnknown3D[3];
};

/* 8-byte block allocated under the id 'jmsg' (fn_800AFCB8). */
struct Block_800AFCB8 {
    int mUnknown0;
    void *mpUnknown4;
};

typedef void (*Callback_800AFC5C)(int a, int b, float c);

/* Items of the pool at Block_800AFCB8 +4. */
struct Item_800AFC5C {
    Callback_800AFC5C mpCallback0;
};

/* Arguments that fn_800AFD58 passes to each item callback. */
struct Context_800AFC5C {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
};

/* 72-byte entries of Block_800B0CFC. */
struct Entry_800B0CFC {
    void *mpUnknown0[5];
    void *mpUnknown14[5];
    int mUnknown28[5];
    unsigned char mUnknown3C[5];
    unsigned char mUnknown41[5];
    unsigned char mUnknown46;
    unsigned char mUnknown47;
};

/* 744-byte block allocated under the id 'mmot' (fn_800B0CFC). */
struct Block_800B0CFC {
    Entry_800B0CFC mEntries[2][5];
    int mUnknown2D0;
    int mUnknown2D4;
    int mUnknown2D8;
    int mUnknown2DC;
    int mUnknown2E0;
    unsigned char mUnknown2E4;
    unsigned char mUnknown2E5;
    unsigned char mUnknown2E6[2];
};

/* Three words passed by address to fn_80238388. */
struct Args_800B1478 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int fn_801D27A0(void);
int fn_801C6858(int a, int b, int c);
int fn_801C1FEC(const void *pA, const void *pB, int size);
void fn_801C1FBC(void *pDest, void *pSrc, unsigned int size);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6D34(void *pool, void *pItem, void *pContext, void *pResult, int (*pMatch)(void *pItem, void *pContext, void *pResult), int d);
int fn_801C6DCC(void *pool, void *pItem, void *pContext, void *pResult, int (*pMatch)(void *pItem, void *pContext, void *pResult));
int fn_801C4E98(void *p, const char *pName);
void *fn_801C47EC(void *p, int a, int b, int c);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
Object_800670B4 *fn_80168708(int team);
int fn_80164E30(Record_80067338 *pRecord, Object_800670B4 *pObject, Object_80039F5C *p, int value);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238388(Args_800B1478 *pArgs);
int fn_800AF198(void *pItem, void *pContext, void *pResult);
void fn_800AF264(int key);
void fn_800AF4A8(Entry_800AF82C *p);
void fn_800B0090(void);
void fn_800B03A4(int value);
int fn_800B0A2C(Object_80039F5C *p, int value);
void fn_800B0730(Object_80039F5C *p, int value);

extern void *lbl_803EAB00;
extern unsigned char lbl_803EAB04;
extern Block_800AFCB8 *lbl_803EAB0C;
extern unsigned char lbl_803EAB10[4];
extern Block_800B0CFC *lbl_803EAB14;
extern int lbl_803EAB18;
extern int lbl_803EC974;
extern Table_800AF71C *lbl_803EC978;
extern void *lbl_803EC97C;
}

extern "C" Item_800AF13C *fn_800AF13C(int key)
{
    Item_800AF13C *pFound;

    if (lbl_803EAB00 == 0 || fn_801C6DCC(lbl_803EAB00, 0, &key, &pFound, fn_800AF198) != 2) {
        pFound = 0;
    }
    return pFound;
}

extern "C" int fn_800AF198(void *pItem, void *pContext, void *pResult)
{
    int result = -1;

    if (((Item_800AF13C *)pItem)->mUnknown8 == *(int *)pContext) {
        *(Item_800AF13C **)pResult = (Item_800AF13C *)pItem;
        result = 0;
    }
    return result;
}

extern "C" void fn_800AF1BC(int a, int count)
{
    lbl_803EC974 = a;
    lbl_803EAB00 = fn_801C68FC(a, 0, count, sizeof(Item_800AF13C), 0, 0);
}

extern "C" void fn_800AF1FC(void)
{
    Item_800AF13C *pItem = (Item_800AF13C *)fn_801C6B4C(lbl_803EAB00, 0);

    while (pItem != 0) {
        Item_800AF13C *pNext = (Item_800AF13C *)fn_801C6C84(lbl_803EAB00, pItem);

        fn_800AF264(pItem->mUnknown8);
        pItem = pNext;
    }
    fn_801C69E4(lbl_803EAB00);
    lbl_803EAB00 = 0;
}

extern "C" void fn_800AF264(int key)
{
    Item_800AF13C *pItem = fn_800AF13C(key);

    if (pItem != 0) {
        fn_801F010C(pItem->mpUnknown0, pItem->mUnknown4);
        fn_801C6C0C(lbl_803EAB00, pItem);
    }
}

extern "C" void fn_800AF2AC(Count_800AF2AC *pCount, Mesh_800AF2AC *pMesh, Source_800AF2AC *pSource)
{
    unsigned int count = pCount->mUnknown8;
    unsigned int i;

    for (i = 0; i < count; i++) {
        int index = pSource->mUnknown6;

        pMesh->mpUnknown30[index].mUnknown0 = pSource->mUnknown0;
        pMesh->mpUnknown30[index].mUnknown2 = pSource->mUnknown2;
        pMesh->mpUnknown30[index].mUnknown4 = pSource->mUnknown4;
        pSource++;
    }
}

extern "C" void fn_800AF71C(void)
{
    unsigned int count = lbl_803EC978->mCount;
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_801D2BD0(lbl_803EC978->mpUnknown4[i]);
    }
    fn_801D2BD0(lbl_803EC978);
    fn_801D2BD0(lbl_803EC97C);
    lbl_803EAB04 = 0;
}

extern "C" void fn_800AF790(int index, void *p, const char *pNameA, const char *pNameB, int value)
{
    int a = fn_801C4E98(p, pNameA);
    int b = fn_801C4E98(p, pNameB);

    lbl_803EC978->mpUnknown4[index] = fn_801C47EC(p, a, b, value);
}

extern "C" void fn_800AF804(Entry_800AF82C *p)
{
    fn_801C1F94(p, 0, 3 * sizeof(Entry_800AF82C));
}

extern "C" void fn_800AF9C0(Entry_800AF82C *p, int index, int *pValue)
{
    Entry_800AF82C *pEntry = p + index;

    pEntry->mUnknown30[0] = pValue[0];
    pEntry->mUnknown30[1] = pValue[1];
    pEntry->mUnknown30[2] = pValue[2];
}

extern "C" int fn_800AF9E4(Entry_800AF82C *p, int index)
{
    Entry_800AF82C *pEntry = p + index;

    return pEntry->mUnknown3C;
}

extern "C" void fn_800AF9F4(Entry_800AF82C *p)
{
    unsigned int count = lbl_803EC978->mCount;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (p[i].mpUnknown0 != 0 && p[i].mUnknown3C != 0) {
            fn_800AF4A8(&p[i]);
        }
    }
}

extern "C" int fn_800AFA60(void *p, int value)
{
    Block_800AFCB8 *pBlock = (Block_800AFCB8 *)p;

    pBlock->mpUnknown4 = fn_801C68FC(fn_801D27A0(), 0, pBlock->mUnknown0, 4, 0, 0);
    return 0;
}

extern "C" int fn_800AFAAC(void *p, int value)
{
    fn_801C69E4(((Block_800AFCB8 *)p)->mpUnknown4);
    return 0;
}

extern "C" int fn_800AFAD4(void *p, void *q)
{
    Block_800AFCB8 *pBlock = (Block_800AFCB8 *)p;
    Block_800AFCB8 *pOther = (Block_800AFCB8 *)q;
    int result;

    if (pOther != 0) {
        result = fn_801C1FEC(pBlock->mpUnknown4, pOther->mpUnknown4, fn_801C6858(0, pBlock->mUnknown0, 4));
    } else {
        result = fn_80238278(pBlock, 4, 0);
        result = fn_80238278(pBlock->mpUnknown4, fn_801C6858(0, pBlock->mUnknown0, 4), result);
    }
    return result;
}

extern "C" int fn_800AFB70(void *p, void *pBuffer)
{
    Block_800AFCB8 *pBlock = (Block_800AFCB8 *)p;
    char *pDest = (char *)pBuffer;

    fn_801C1FBC(pDest, pBlock, sizeof(Block_800AFCB8));
    pDest += sizeof(Block_800AFCB8);
    fn_801C1FBC(pDest, pBlock->mpUnknown4, fn_801C6858(0, pBlock->mUnknown0, 4));
    return 1;
}

extern "C" int fn_800AFBD8(void *p, void *pBuffer)
{
    Block_800AFCB8 *pBlock = (Block_800AFCB8 *)p;

    fn_801C1FBC(pBlock->mpUnknown4, (char *)pBuffer + sizeof(Block_800AFCB8), fn_801C6858(0, pBlock->mUnknown0, 4));
    return 1;
}

extern "C" int fn_800AFC28(void *p)
{
    return fn_801C6858(0, lbl_803EAB0C->mUnknown0, 4) + sizeof(Block_800AFCB8);
}

extern "C" int fn_800AFC5C(void *pItem, void *pContext, void *pResult)
{
    Context_800AFC5C *pArgs = (Context_800AFC5C *)pContext;

    ((Item_800AFC5C *)pItem)->mpCallback0(pArgs->mUnknown0, pArgs->mUnknown4, pArgs->mUnknown8);
    return 1;
}

extern "C" int fn_800AFC94(void *pItem, void *pContext, void *pResult)
{
    if (((Item_800AFC5C *)pItem)->mpCallback0 == ((Item_800AFC5C *)pContext)->mpCallback0) {
        *(void **)pResult = pItem;
        return 0;
    }
    return 1;
}

extern "C" void fn_800AFCB8(int value)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAB0C, sizeof(Block_800AFCB8), 0, 0x6A6D7367);

    fn_80238234(pHandle, fn_800AFA60, fn_800AFAAC, 0, fn_800AFAD4);
    fn_80238248(pHandle, fn_800AFB70, fn_800AFC28, fn_800AFBD8);
    ((Block_800AFCB8 *)fn_8023816C(pHandle))->mUnknown0 = value;
    fn_802381E0(pHandle);
}

extern "C" void fn_800AFD54(void)
{
}

extern "C" void fn_800AFD58(int a, int b, float c)
{
    Block_800AFCB8 *pBlock = lbl_803EAB0C;

    if (pBlock != 0 && pBlock->mpUnknown4 != 0) {
        Context_800AFC5C args;
        void *pool;

        args.mUnknown0 = a;
        args.mUnknown4 = b;
        args.mUnknown8 = c;
        pool = pBlock->mpUnknown4;
        fn_801C6D34(pool, fn_801C6B4C(pool, 0), &args, 0, fn_800AFC5C, 1);
    }
}

extern "C" void fn_800AFDD4(Callback_800AFC5C pCallback)
{
    Item_800AFC5C *pItem = (Item_800AFC5C *)fn_801C6A20(lbl_803EAB0C->mpUnknown4);

    pItem->mpCallback0 = pCallback;
    fn_801C6AA4(lbl_803EAB0C->mpUnknown4, pItem, 1);
}

extern "C" void fn_800AFE20(Callback_800AFC5C pCallback)
{
    Item_800AFC5C key;
    void *pFound;
    void *pool;

    key.mpCallback0 = pCallback;
    pool = lbl_803EAB0C->mpUnknown4;
    fn_801C6D34(pool, fn_801C6B4C(pool, 0), &key, &pFound, fn_800AFC94, 1);
    fn_801C6C0C(lbl_803EAB0C->mpUnknown4, pFound);
}

extern "C" int fn_800AFF20(int group, int index, int ref)
{
    Entry_800B0CFC *pEntry = &lbl_803EAB14->mEntries[group][index];
    int none;

    fn_8009BD2C(0, &none);
    if (ref != none && pEntry->mUnknown28[0] == ref) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800AFF88(Object_80039F5C *p)
{
    unsigned int i = 0;
    Record_80067338 *pRecord = fn_8016871C(p->mIdBytes[2]);
    Object_800670B4 *pObject = fn_80168708(p->mIdBytes[2]);

    for (; i <= 3; i++) {
        if (fn_80164E30(pRecord, pObject, p, lbl_803EAB10[i]) == 1) {
            return 0;
        }
    }
    return 1;
}

extern "C" void fn_800B0004(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 4; j++) {
            Entry_800B0CFC *pEntry = &lbl_803EAB14->mEntries[i][j];
            Object_80039F5C *p = fn_8009BCE8(&pEntry->mUnknown28[0]);

            if (p != 0 && fn_800AFF88(p) == 0) {
                fn_801C1F94(pEntry, 0, sizeof(Entry_800B0CFC));
            }
        }
    }
}

extern "C" void fn_800B0A28(void)
{
}

extern "C" int fn_800B0C70(void *p, void *q)
{
    Block_800B0CFC *pBlock = (Block_800B0CFC *)p;
    int result;
    int i;
    int j;

    if (q != 0) {
        result = fn_80238258(p, q, sizeof(Block_800B0CFC));
    } else {
        result = fn_80238278(&pBlock->mUnknown2D0, 22, 0);
        for (i = 0; i <= 1; i++) {
            for (j = 0; j < 5; j++) {
                result = fn_80238278(pBlock->mEntries[i][j].mUnknown28, 31, result);
            }
        }
    }
    return result;
}

extern "C" void fn_800B0CFC(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAB14, sizeof(Block_800B0CFC), 0, 0x6D6D6F74);
    Block_800B0CFC *pBlock;

    fn_80238234(pHandle, 0, 0, 0, fn_800B0C70);
    pBlock = (Block_800B0CFC *)fn_8023816C(pHandle);
    fn_801C1F94(pBlock, 0, sizeof(Block_800B0CFC));
    fn_8009BD2C(0, &pBlock->mUnknown2D0);
    pBlock->mUnknown2E4 = 1;
    pBlock->mUnknown2D4 = 0;
    pBlock->mUnknown2E5 = 0;
    pBlock->mUnknown2E0 = 2;
    fn_802381E0(pHandle);
}

extern "C" void fn_800B0DA0(void)
{
}

extern "C" void fn_800B0E68(void)
{
    fn_800B0090();
    if (lbl_803EAB14->mUnknown2E4 != 0 && lbl_803EAB14->mUnknown2E5 == 0) {
        fn_800B03A4(0);
        lbl_803EAB14->mUnknown2E0 = 2;
    }
}

extern "C" void fn_800B0EB8(void)
{
    Object_80039F5C *p = fn_8009BCE8(&lbl_803EAB14->mUnknown2D0);

    if (fn_800B0A2C(p, 0) != 0 && lbl_803EAB14->mUnknown2E0 != 0) {
        fn_800B0090();
        fn_800B0730(p, 0);
        lbl_803EAB14->mUnknown2E0 = 0;
    }
}

extern "C" void fn_800B0F28(void)
{
    Object_80039F5C *p = fn_8009BCE8(&lbl_803EAB14->mUnknown2D0);

    if (fn_800B0A2C(p, 1) != 0 && lbl_803EAB14->mUnknown2E0 != 1) {
        fn_800B0090();
        fn_800B0730(p, 1);
        lbl_803EAB14->mUnknown2E0 = 1;
    }
}

extern "C" int fn_800B0F98(void)
{
    return lbl_803EAB14->mUnknown2D0;
}

extern "C" int fn_800B146C(void)
{
    return lbl_803EAB14->mUnknown2E5;
}

extern "C" void fn_800B1478(void)
{
    Args_800B1478 args;

    args.mUnknown0 = 75;
    args.mUnknown4 = 28;
    args.mUnknown8 = 1;
    lbl_803EAB18 = fn_80238388(&args);
}
