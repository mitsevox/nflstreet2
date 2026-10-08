#include <string.h>

#include "engine/vptmanager.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80041210.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8007F828.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/fn_80195EFC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"
#include "game/fn_80218FC4.h"
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

/* 8-byte records from +12 of Table_800AA80C. */
struct Entry_800AA80C {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5[3];
};

typedef void (*Callback_800AAE20)(Entry_800AA80C *pEntries, int index);

/* The .data table whose address fn_800AA80C stores at +0 of
   Block_800AACD4: three callbacks, then the records. */
struct Table_800AA80C {
    Callback_800AAE20 mpCallback0;
    Callback_800AAE20 mpCallback4;
    Callback_800AAE20 mpCallback8;
    Entry_800AA80C mEntries[1];
};

/* 24-byte block allocated under the id 'gend' at 0x800AACFC. */
struct Block_800AACD4 {
    Table_800AA80C *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    unsigned int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    signed char mUnknown16;
    unsigned char mUnknown17[1];
};

/* 8-byte block allocated under the id 'gskl' by fn_800ABD1C. */
struct Block_800ABD1C {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
};

/* 16-byte block allocated under the id 'gply' at 0x800AD664. Only the
   word +0 is declared. */
struct Block_800AD634 {
    int mUnknown0;
    unsigned char mUnknown4[12];
};

extern "C" {
void fn_8004A230(unsigned char value);
void fn_8003AB08(Object_80039F5C *p, int a);
void fn_800EFE1C(int a, State_80039F5C *pQueue);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800A9F64(void);
void fn_800AA010(int value);
char *fn_800A9F4C(int index);
void fn_800AA1B0(int a, int b);
void fn_800AA348(Entry_800AA80C *pEntries, int index);
void fn_800AA510(Entry_800AA80C *pEntries, int index);
void fn_80092F98(int handle);
void fn_800940F0(int handle);
void fn_80093348(int handle);
void fn_8013FB44(void);
int fn_800737B8(void);
int fn_80025708(void);
void fn_8017DC08(void);
int fn_80059004(void);
void fn_80059014(void);
void fn_800C1CA0(void);
void fn_8009D964(int index, int value);
void fn_8005BC10(int a);
void fn_80031A54(void);
void fn_802195E4(void *p, short a, short b);
unsigned char fn_8005B3CC(void);
Object_80039F5C *fn_8005A8AC(int index);
void fn_800ABA0C(void);
void fn_800ABAF0(void);
int fn_800B65A0(int team);
int fn_80178308(void);
int fn_8017F60C(void);
void fn_800B8608(void);
int fn_801C601C(int a);
int fn_801C6458(int a, int b);
int fn_801E195C(int a);
int fn_801C60BC(int a);
void fn_800BA574(void);
void fn_800C3170(void);
void fn_800CA14C(void);
void fn_800398B4(void);
void fn_800CA228(void);
int fn_800BA6F8(void);
void fn_80039B2C(float dt);
void fn_80039A38(float dt);
Set_8003EE6C *fn_8003A078(void);
Set_8003EE6C *fn_801442F0(void);
void fn_80039C64(void);
void fn_8005122C(float dt);
void fn_80039CB0(float dt);
void fn_80039D08(float dt);
void fn_801BF8DC(void);

extern Block_800AACD4 *lbl_803EAA88;
extern int lbl_803EAA90;
extern unsigned char lbl_803EAA99;
extern unsigned int lbl_803EAA9C;
extern Block_800ABD1C *lbl_803EAAB8;
extern Block_800AD634 *lbl_803EAAD4;
extern void *lbl_803EB688;
extern char *lbl_803EC960;
extern char *lbl_803EC964[2];
extern Table_800AA80C lbl_802D8194;
}

extern "C" void fn_800AA124(void)
{
    unsigned short count = 7;
    unsigned short i;

    for (i = 0; i < count; i++) {
        Block_80170E64 *p = fn_80039F5C(0, i)->mpUnknown4;

        p->mUnknown20 |= 1;
    }
    for (i = 0; i < count; i++) {
        Block_80170E64 *p = fn_80039F5C(1, i)->mpUnknown4;

        p->mUnknown20 |= 1;
    }
    fn_8004A230(1);
}

extern "C" void fn_800AA2B4(void)
{
    fn_800AA1B0(lbl_803EAA88->mpUnknown0->mEntries[lbl_803EAA90 + 1].mUnknown0,
                lbl_803EAA88->mpUnknown0->mEntries[lbl_803EAA90 + 1].mUnknown4);
}

extern "C" void fn_800AA2F8(void)
{
    if (lbl_803EAA88->mUnknown4 != 13) {
        fn_8013FB44();
    }
    fn_80092F98(lbl_803EAA88->mUnknownC);
    lbl_803EAA88->mUnknown8 = lbl_803EAA88->mUnknownC;
    lbl_803EAA88->mUnknownC = -1;
}

extern "C" void fn_800AA6D8(Entry_800AA80C *pEntries, int index)
{
    if (fn_800737B8() != 0) {
        fn_80067E3C(109, 0, 0, 0, 0, 0);
    }
    fn_800A9F64();
}

extern "C" int fn_800AA80C(void *p)
{
    int i;

    lbl_803EAA88->mpUnknown0 = &lbl_802D8194;
    for (i = 0; i <= 4; i++) {
        int value = fn_80094564(lbl_803EAA88->mUnknown16, i);

        if (value == -1) {
            lbl_803EAA88->mpUnknown0->mEntries[i].mUnknown0 = 9999;
        } else {
            lbl_803EAA88->mpUnknown0->mEntries[i].mUnknown0 = value;
        }
    }
    lbl_803EAA99 = 1;
    fn_800AA010(1);
    return 1;
}

extern "C" void fn_800AA8B8(void)
{
    unsigned char i;

    for (i = 0; i <= 6; i++) {
        Object_80039F5C *p = fn_80039F5C(0, i);

        fn_8003AB08(p, 0);
        fn_800EFE1C(0, &p->mUnknown3048);
        p = fn_80039F5C(1, i);
        fn_8003AB08(p, 0);
        fn_800EFE1C(0, &p->mUnknown3048);
    }
}

extern "C" void fn_800AA93C(int a, unsigned int value)
{
    if (lbl_803EAA88->mUnknown15 == 0) {
        switch (value) {
        case 0:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            if (lbl_803EAA88->mUnknown10 > 90) {
                switch (lbl_803EAA88->mUnknown4) {
                case 3:
                    break;
                case 13:
                case 14:
                case 15:
                    if (fn_8017F60C() == 0 && lbl_803EAA99 == 0) {
                        fn_800ABA0C();
                        fn_800A9F64();
                        lbl_803EAA88->mUnknown4 = 16;
                    }
                    break;
                case 0:
                case 1:
                case 2:
                    if (fn_8017F60C() == 0) {
                        fn_800ABA0C();
                        fn_800A9F64();
                        lbl_803EAA88->mUnknown4 = 3;
                    }
                    break;
                }
            }
            break;
        }
    }
}

extern "C" void fn_800AAA00(void)
{
    fn_800AA8B8();
    fn_800940F0(lbl_803EAA88->mUnknown8);
    fn_80093348(lbl_803EAA88->mUnknown8);
    fn_80093410(lbl_803EAA88->mUnknown8);
    fn_80092F98(lbl_803EAA88->mUnknownC);
    lbl_803EAA88->mUnknown8 = lbl_803EAA88->mUnknownC;
    lbl_803EAA88->mUnknownC = -1;
    fn_80092830(lbl_803EAA88->mUnknown8);
    fn_80092830(lbl_803EAA88->mUnknown8);
}

extern "C" int fn_800AAA78(void)
{
    int result = 0;

    if (lbl_803EAA88->mUnknown8 != -1 && fn_80092830(lbl_803EAA88->mUnknown8) != 0) {
        result = 1;
    }
    return result;
}

extern "C" int fn_800AAAC4(void)
{
    int result = 1;

    if (lbl_803EAA88->mUnknownC != -1) {
        result = fn_800927BC((unsigned char)lbl_803EAA88->mUnknownC);
    }
    return result;
}

extern "C" void fn_800AAAFC(void)
{
    int i;

    lbl_803EC960 = fn_800A9F4C(0);
    if (lbl_803EC960 != 0) {
        lbl_803EAA88->mUnknown14 = 1;
    } else {
        lbl_803EAA88->mUnknown14 = 0;
    }
    for (i = 0; i <= 1; i++) {
        lbl_803EC964[i] = lbl_803EC960 + i * 0x16000;
    }
    fn_800AA010(0);
}

extern "C" int fn_800AAE20(void *p, float dt)
{
    int result = 0;
    Table_800AA80C *pTable;

    if (lbl_803EAA88->mpUnknown0 != 0) {
        lbl_803EAA90 = 0;
        fn_800AA010(0);
        pTable = lbl_803EAA88->mpUnknown0;
        if (pTable->mpCallback0 != 0) {
            pTable->mpCallback0(pTable->mEntries, lbl_803EAA90);
            if (lbl_803EAA88->mUnknown14 == 0) {
                fn_800ABA0C();
                return 0;
            }
        }
        pTable = lbl_803EAA88->mpUnknown0;
        if (pTable->mpCallback4 != 0) {
            result = 1;
            pTable->mpCallback4(pTable->mEntries, lbl_803EAA90);
        } else {
            result = 2;
        }
    } else {
        fn_800ABA0C();
    }
    return result;
}

extern "C" int fn_800AAEE0(void *p, float dt)
{
    int result;

    if (fn_800AAAC4() != 0) {
        if (fn_80137B40() != 0) {
            fn_8013791C(fn_801374BC(), 5, 0);
        }
        fn_800AA2F8();
        fn_800AA2B4();
        result = 2;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_800AAF38(void *p, float dt)
{
    int result = 2;

    if (fn_800AAA78() == 0) {
        lbl_803EAA90++;
        if (lbl_803EAA88->mpUnknown0->mEntries[lbl_803EAA90].mUnknown0 == 9999) {
            Table_800AA80C *pTable;

            fn_80094608(0);
            pTable = lbl_803EAA88->mpUnknown0;
            if (pTable->mpCallback8 != 0) {
                pTable->mpCallback8(pTable->mEntries, lbl_803EAA90);
            }
            result = 0;
        } else {
            fn_800AA348(lbl_803EAA88->mpUnknown0->mEntries, lbl_803EAA90);
            fn_800AAA00();
            fn_800AA2B4();
            fn_800AA510(lbl_803EAA88->mpUnknown0->mEntries, lbl_803EAA90);
        }
    }
    return result;
}

extern "C" int fn_800AAFEC(void *p, float dt)
{
    if (fn_80025708() != 0) {
        lbl_803EAA88->mUnknown4 = 16;
        fn_8017DC08();
        if (fn_80059004() != 0) {
            fn_800C1CA0();
            fn_8009D964(4, 1);
            fn_80059014();
        } else {
            fn_80195EFC(1, 30, 0x808080, 0);
            fn_8005BC10(4);
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_800AB190(void *p)
{
    lbl_803EAA9C = 0;
    fn_80031A54();
}

extern "C" void fn_800AB29C(void *p)
{
    fn_80218FC4(lbl_803EB688, 3, 7, 0, 0);
    fn_802195E4(lbl_803EB688, 3, 7);
    fn_80195EFC(1, 20, 0x808080, 0);
    fn_800ABAF0();
}

extern "C" int fn_800AB2FC(void *p, float dt)
{
    int result = 0;

    if (fn_8005B3CC() != 0) {
        if (fn_80092830(lbl_803EAA88->mUnknown8) == 0) {
            Message_800F01CC message;
            Object_80039F5C *pObject;

            fn_801C1F94(&message, 0, sizeof(message));
            message.mId = 9;
            message.mUnknown1[0] = 203;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 255;
            pObject = fn_8005A8AC(0);
            fn_800F00D4(0, pObject->mpState, &message, pObject);
            pObject = fn_8005A8AC(1);
            fn_800F00D4(0, pObject->mpState, &message, pObject);
        }
        result = 1;
    }
    return result;
}

extern "C" void fn_800AB944(void *p)
{
}

extern "C" void fn_800ABA0C(void)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        unsigned char team = i;
        unsigned int count = fn_80178D18(team);
        unsigned int index;

        for (index = 0; index < count; index++) {
            Object_80039F5C *p = fn_80039F5C(team, index);

            fn_800EFE60(0, p->mpState, p);
        }
    }
    fn_8004A230(0);
}

extern "C" int fn_800ABCC0(void)
{
    return lbl_803EAA88->mUnknown4 < 5 || lbl_803EAA88->mUnknown4 > 12;
}

extern "C" int fn_800ABCDC(void)
{
    return lbl_803EAA90 & 1;
}

extern "C" void fn_800ABCE8(Block_800ABD1C *p)
{
    p->mUnknown0 = fn_8007F828(0);
}

extern "C" void fn_800ABD1C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAAB8, sizeof(Block_800ABD1C), 0, 0x67736B6C);
    Block_800ABD1C *p = (Block_800ABD1C *)fn_8023816C(pHandle);

    fn_800ABCE8(p);
    p->mUnknown4 = 1;
    fn_802381E0(pHandle);
}

extern "C" void fn_800ABD7C(void)
{
}

extern "C" void fn_800ABD80(void)
{
    fn_800ABCE8(lbl_803EAAB8);
}

extern "C" unsigned int fn_800ABDA4(int team)
{
    if (fn_8002892C() != 0) {
        return 1;
    }
    if (fn_800B65A0(team) != 255) {
        return lbl_803EAAB8->mUnknown4;
    }
    return lbl_803EAAB8->mUnknown0;
}

extern "C" void fn_800ABE00(void)
{
    lbl_803EAAB8->mUnknown4 = 1;
}

extern "C" int fn_800AC218(int team)
{
    int result;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = 20;
        break;
    case 2:
        result = 6;
        break;
    case 1:
    default:
        result = 12;
        break;
    }
    return result;
}

extern "C" int fn_800AC268(int team)
{
    int result;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = 25;
        break;
    case 1:
        result = 15;
        break;
    case 2:
        result = 0;
        break;
    default:
        result = 12;
        break;
    }
    return result;
}

extern "C" int fn_800AC2C0(int team)
{
    int result;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = 12;
        break;
    case 1:
        result = 6;
        break;
    case 2:
        result = 6;
        break;
    default:
        result = 6;
        break;
    }
    if (fn_800B65A0(team ^ 1) == 255) {
        result += 2;
    }
    return result;
}

extern "C" int fn_800AC324(int team)
{
    int result;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = 35;
        break;
    case 1:
        result = 15;
        break;
    case 2:
        result = 10;
        break;
    default:
        result = 6;
        break;
    }
    if (fn_800B65A0(team ^ 1) == 255) {
        result += 2;
    }
    return result;
}

extern "C" int fn_800AC3A0(void)
{
    int result;

    switch (fn_800ABDA4(fn_80178308())) {
    case 0:
        result = 35;
        break;
    case 1:
        result = 20;
        break;
    case 2:
        result = 0;
        break;
    default:
        result = 6;
        break;
    }
    return result;
}

extern "C" int fn_800AC3FC(int a, unsigned int value)
{
    int level = fn_800ABDA4(fn_80178308());

    if (level == 1) {
        return value < 50;
    }
    return level == 0;
}

extern "C" int fn_800ACA70(int team, int value)
{
    switch (fn_800ABDA4(team)) {
    case 0:
        break;
    case 1:
        value = value * 7 / 6;
        break;
    case 2:
        value = value * 7 / 5;
        break;
    }
    return value;
}

extern "C" void fn_800ACAF8(int team, unsigned int *pValue)
{
    switch (fn_800ABDA4(team)) {
    case 0:
        *pValue = *pValue * 6 / 5;
        break;
    case 1:
        *pValue = *pValue * 3 / 4;
        break;
    case 2:
        *pValue = *pValue * 2 / 3;
        break;
    }
}

extern "C" unsigned int fn_800ACBFC(int team)
{
    unsigned int result = 1000000000;

    if (fn_800B65A0(team) == 255) {
        switch (fn_800ABDA4(team ^ 1)) {
        case 0:
            result = 500000000;
            break;
        case 2:
            result = 1250000000;
            break;
        case 1:
        default:
            result = 1000000000;
            break;
        }
    }
    return result;
}

extern "C" int fn_800ACF40(Object_80039F5C *p, signed char value)
{
    int team = p->mIdBytes[2];
    int flag = 0;

    if (fn_800B65A0(team) != 255) {
        flag = 1;
    }
    if (flag == 0 && fn_800ABDA4(team) == 0) {
        value += 20;
    }
    return value;
}

extern "C" int fn_800ACFA8(Object_80039F5C *p)
{
    int result;

    switch (fn_800ABDA4(p->mIdBytes[2])) {
    case 0:
        result = 76;
        break;
    case 2:
        result = 229;
        break;
    case 1:
    default:
        result = 153;
        break;
    }
    return result;
}

extern "C" int fn_800AD0E4(int team)
{
    int result = 0;

    switch (fn_800ABDA4(team)) {
    case 0:
        result = fn_802372EC(0, 3) + 2;
        break;
    case 1:
        result = fn_802372EC(0, 5) + 3;
        break;
    case 2:
        result = fn_802372EC(0, 4) + 4;
        break;
    }
    return result;
}

extern "C" int fn_800AD2CC(int team, int flag)
{
    int result;

    if (fn_800ABDA4(team) != 0) {
        if (flag != 0) {
            result = 0x400000;
        } else {
            result = 0x2AAAAA;
        }
    } else {
        result = 0x200000;
    }
    return result;
}

extern "C" void fn_800AD3A8(float dt)
{
    unsigned int count = 10;
    unsigned int i;

    fn_800B8608();
    fn_801C601C(-1);
    for (i = 0; i < count; i++) {
        int handle = fn_801C6458(i, 0);

        if (handle != -1 && fn_801E195C(handle) == 2) {
            fn_801C60BC(i);
        }
    }
    fn_8002B270();
    fn_800BA574();
}

extern "C" void fn_800AD4B8(float dt)
{
    fn_800C3170();
    fn_8004183C();
    fn_800CA14C();
    fn_800398B4();
    fn_800CA228();
    if (fn_800BA6F8() == 0) {
        fn_80094EDC();
    }
    fn_801376B8(dt);
}

extern "C" void fn_800AD50C(float dt)
{
    fn_80041664();
    fn_80039B2C(dt);
    fn_80039A38(dt);
    fn_80137758(dt);
}

extern "C" void fn_800AD550(float dt)
{
    int mode = fn_800AD9B4();

    if (mode != 5 && mode != 1 && mode != 6 && mode != 7) {
        fn_8003F04C(fn_8003A078());
        fn_8003F04C(fn_801442F0());
        fn_80039C64();
    }
    fn_8005122C(dt);
    fn_801377C4(dt);
}

extern "C" void fn_800AD5C0(float dt)
{
    fn_800416CC(dt);
    fn_80039CB0(dt);
    fn_80039D08(dt);
    fn_801BF8DC();
}

extern "C" int fn_800AD9B4(void)
{
    return lbl_803EAAD4->mUnknown0;
}
