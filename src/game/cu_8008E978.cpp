#include <string.h>

#include "game/Class_80148A58.h"
#include "game/Class_80297AB8.h"
#include "game/FELoop.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/cu_8008E978.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
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

struct Entry_8009D964 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
};

/* Allocated through fn_80238174 under the id 'clck' (fn_8009D474). */
struct Block_8009D474 {
    int mUnknown0;
    Entry_8009D964 mEntries[6];
    int mUnknown94;
    int mUnknown98;
};

/* Object whose address fn_8011F4EC returns. Only the accessed bytes are
   declared; the size is not established. */
struct State_8011F4EC {
    int mUnknown0;
    int mUnknown4[2];
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned char mUnknown16[386];
    unsigned char mUnknown198;
    unsigned char mUnknown199[3];
    unsigned char mUnknown19C[3];
    unsigned char mUnknown19F[3];
    unsigned char mUnknown1A2;
    unsigned char mUnknown1A3[5];
    unsigned char mUnknown1A8;
    unsigned char mUnknown1A9;
    unsigned char mUnknown1AA[2];
    float mUnknown1AC[3];
    unsigned char mUnknown1B8[13];
    unsigned char mUnknown1C5;
};

/* Record tested by fn_8009FE24; only its first three bytes are declared. */
struct Record_8009FE24 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

struct Block_8009FF94 {
    unsigned int mUnknown0;
    unsigned int mUnknown4;
};

/* 24 bytes cleared by fn_800A0624. */
struct Record_800A0624 {
    unsigned char mUnknown0;
    unsigned char mUnknown1[3];
    int mUnknown4;
    unsigned char mUnknown8[4];
    int mUnknownC;
    int mUnknown10;
    unsigned char mUnknown14[4];
};

/* 32 bytes cleared by fn_800A0684. */
struct Record_800A0684 {
    int mUnknown0;
    int mUnknown4;
    Point_8017886C mUnknown8;
    unsigned char mUnknown10[12];
    unsigned char mUnknown1C;
};

struct Pair_800A14A8 {
    int mUnknown0;
    int mUnknown4;
};

struct Block_802D7C64 {
    int mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
};

extern "C" {
unsigned int fn_801735C8(unsigned int mask);
void fn_8009D964(int index, int value);
State_8011F4EC *fn_8011F4EC(void);
int fn_8011F1CC(void);
int fn_80178308(void);
int fn_80178320(void);
Object_800670B4 *fn_80168708(int team);
int fn_80168E00(int team, int index, unsigned char *pOut);
void fn_801647A4(Object_800670B4 *pObject, int team, void *pArg);
int fn_800B65A0(int team);
void fn_800C1C34(void);
void fn_800FBAA8(void);
void fn_8009E674(void);
void fn_800A5D94(void);
int fn_8009DBB4(State_8011F4EC *p);
void fn_8009E58C(void);
Record_8009FE24 *fn_800AEE20(Object_80039F5C *p);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_80177F70(void);
int fn_800B2320(void);
int fn_800A1C50(void);
void fn_800A1C74(int a, int b);
void fn_80194F1C(unsigned char enabled);
int fn_800C8774(int team);
int fn_801787DC(int team);
void fn_801787FC(int team, short value);
void fn_800C87CC(int team, int value);
void fn_8017D6B8(int a, int b);
unsigned char fn_8017F384(unsigned char value);

extern Block_8009D474 *lbl_803EA9A8;
extern char lbl_803EB3B0[];
extern int lbl_803EA9D0;
extern int lbl_803EA9D4;
extern int lbl_803EA9D8;
extern Block_8009FF94 *lbl_8030C080[];
extern Class_80297AB8 *lbl_803EA9E4;
extern Class_80297AB8 lbl_803EC900;
extern Block_802D7C64 lbl_802D7C64[];
extern unsigned int lbl_803EA9EC;
}

extern "C" void fn_8009D474(int a, int b)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EA9A8, sizeof(Block_8009D474), 0, 0x636C636B);
    Block_8009D474 *p = (Block_8009D474 *)fn_8023816C(pHandle);

    p->mUnknown0 = 0;
    p->mUnknown98 = 0;
    p->mEntries[1].mUnknown0 = 0;
    p->mEntries[1].mUnknownC = a;
    p->mEntries[1].mUnknown8 = a;
    p->mEntries[1].mUnknown10 = b;
    p->mEntries[1].mUnknown4 = b;
    p->mEntries[0].mUnknown0 = 0;
    p->mEntries[0].mUnknownC = 1;
    p->mEntries[0].mUnknown8 = 1;
    p->mEntries[0].mUnknown10 = b;
    p->mEntries[0].mUnknown4 = b;
    p->mEntries[2].mUnknown0 = 0;
    p->mEntries[2].mUnknownC = 1;
    p->mEntries[2].mUnknown8 = 1;
    p->mEntries[2].mUnknown10 = b;
    p->mEntries[2].mUnknown4 = b;
    p->mEntries[3].mUnknown0 = 0;
    p->mEntries[3].mUnknownC = 1;
    p->mEntries[3].mUnknown8 = 1;
    p->mEntries[3].mUnknown10 = b;
    p->mEntries[3].mUnknown4 = b;
    p->mEntries[4].mUnknown0 = 0;
    p->mEntries[4].mUnknownC = 1;
    p->mEntries[4].mUnknown8 = 1;
    p->mEntries[4].mUnknown10 = b;
    p->mEntries[4].mUnknown4 = b;
    p->mEntries[5].mUnknown0 = 0;
    p->mEntries[5].mUnknownC = 1;
    p->mEntries[5].mUnknown8 = 1;
    p->mEntries[5].mUnknown10 = b;
    p->mEntries[5].mUnknown4 = b;
    fn_802381E0(pHandle);
}

extern "C" int fn_8009D86C(void)
{
    if (lbl_803EA9A8 != 0) {
        return lbl_803EA9A8->mUnknown0;
    }
    return 0;
}

extern "C" void fn_8009D888(int index, int value)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    if (value != 0) {
        fn_8009D964(index, value);
    }
    pEntry->mUnknown0 = 1;
}

extern "C" void fn_8009D8CC(int index)
{
    Block_8009D474 *p = lbl_803EA9A8;
    Entry_8009D964 *pEntry = &p->mEntries[index];

    if (p != 0) {
        if (index != 1 || fn_801735C8(0x800) == 0) {
            pEntry->mUnknown0 = 0;
        }
    }
}

extern "C" void fn_8009D924(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    pEntry->mUnknown14 |= 1;
}

extern "C" void fn_8009D944(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    pEntry->mUnknown14 &= ~1;
}

extern "C" void fn_8009D964(int index, int value)
{
    Entry_8009D964 *p = &lbl_803EA9A8->mEntries[index];

    p->mUnknown8 = value;
    p->mUnknown10 = p->mUnknown4;
}

extern "C" void fn_8009D984(int value)
{
    lbl_803EA9A8->mEntries[1].mUnknownC = value;
}

extern "C" int fn_8009D990(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    return pEntry->mUnknown8;
}

extern "C" int fn_8009D9A8(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    return pEntry->mUnknownC;
}

extern "C" int fn_8009D9C0(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    return pEntry->mUnknown4;
}

extern "C" int fn_8009D9D8(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    return pEntry->mUnknown0 == 1;
}

extern "C" int fn_8009D9F8(int index)
{
    Entry_8009D964 *pEntry = &lbl_803EA9A8->mEntries[index];

    return pEntry->mUnknown10;
}

extern "C" void fn_8009DA10(Object_80039F5C *p)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, sizeof(message));
    message.mId = 11;
    fn_800F053C(0, p->mpState, &message, p);
    fn_801C1F94(&message, 0, sizeof(message));
    message.mId = 2;
    fn_800F01CC(0, p->mpState, &message, p);
}

extern "C" void fn_8009DA90(void)
{
    int team = fn_80178308();
    State_8011F4EC *p = fn_8011F4EC();
    unsigned char i;

    p->mUnknown198 = 3;
    if (fn_8011F1CC() != 0) {
        for (i = 0; i < p->mUnknown198; i++) {
            p->mUnknown199[i] = fn_80168E00(team, i, &p->mUnknown19C[i]);
        }
    } else {
        for (i = 0; i < p->mUnknown198; i++) {
            p->mUnknown199[i] = i + 1;
            p->mUnknown19C[i] = 0;
        }
    }
}

extern "C" void fn_8009DB54(int flag)
{
    unsigned char team;
    Object_800670B4 *pObject;

    fn_8011F4EC();
    team = fn_80178320();
    pObject = fn_80168708(team);
    pObject->mUnknown8.mUnknownF ^= 1;
    if (flag != 0) {
        fn_801647A4(pObject, team, lbl_803EB3B0);
    }
}

extern "C" void fn_8009DD10(State_8011F4EC *p)
{
    unsigned int i;

    fn_801C1F94(p, 0, 20);
    p->mUnknown0 = 0;
    for (i = 0; i <= 1; i++) {
        p->mUnknown4[i] = 0;
    }
    if (fn_800B65A0(fn_80178320()) == 0xFF) {
        fn_802372EC(0, 100);
    }
}

extern "C" void fn_8009DE9C(void)
{
    State_8011F4EC *p = fn_8011F4EC();

    if (fn_802372EC(0, 100) < 75) {
        p->mUnknown1C5 = 1;
    } else {
        p->mUnknown1C5 = 0;
    }
    fn_800C1C34();
    fn_8009DD10(p);
    fn_800FBAA8();
    fn_8009E674();
}

extern "C" void fn_8009E0EC(void)
{
    State_8011F4EC *p = fn_8011F4EC();

    fn_8009DA90();
    p->mUnknown1A2 = 0;
    p->mUnknown1A8 = fn_8009DBB4(p);
    fn_8009E674();
    fn_800A5D94();
}

extern "C" void fn_8009E138(void)
{
    State_8011F4EC *p = fn_8011F4EC();

    fn_8009E58C();
    p->mUnknown14--;
    if (p->mUnknown14 & 0x8000) {
        fn_8009E674();
    }
}

extern "C" void fn_8009E58C(void)
{
    State_8011F4EC *p = fn_8011F4EC();
    int team = fn_80178308();

    if (fn_8011F1CC() == 1) {
        unsigned char i;
        int swapped;

        if (p->mUnknown1A2 == 0) {
            for (i = 0; i <= 2; i++) {
                p->mUnknown19F[i] = fn_80168E00(team, i, 0);
            }
        }
        do {
            swapped = 0;
            for (i = 0; i <= 1; i++) {
                Object_80039F5C *pA = fn_80039F5C(team, p->mUnknown19F[i]);
                Object_80039F5C *pB = fn_80039F5C(team, p->mUnknown19F[i + 1]);

                if (pA->mMotion.mPos.mY < pB->mMotion.mPos.mY) {
                    unsigned char temp = p->mUnknown19F[i];

                    swapped = 1;
                    p->mUnknown19F[i] = p->mUnknown19F[i + 1];
                    p->mUnknown19F[i + 1] = temp;
                }
            }
        } while (swapped == 1);
        p->mUnknown1A2 = 1;
    }
}

extern "C" int fn_8009E9A4(void)
{
    return fn_8011F4EC()->mUnknown0;
}

extern "C" int fn_8009E9C8(void)
{
    return fn_8011F4EC()->mUnknown1A8;
}

extern "C" int fn_8009F13C(Object_80039F5C *p)
{
    if (p->mpState->mId == 28 || p->mUnknown16 == 2) {
        return 1;
    }
    return 0;
}

extern "C" int fn_8009F6B4(void)
{
    int team = fn_80178320();
    int result = 0;
    unsigned char count = 0;
    int found = 0;
    unsigned int total = fn_80178D18(team);
    unsigned char i;

    for (i = 0; i < total; i++) {
        unsigned int value = fn_80039F5C(team, i)->mUnknown2914;
        switch (value) {
        case 16:
        case 17:
        case 18:
            count++;
            break;
        }
        if (value > 20) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        if (count == 5) {
            result = 1;
        } else if (count == 6) {
            result = 2;
        } else if (count == 7) {
            result = 3;
        }
    }
    return result;
}

extern "C" int fn_8009F778(void)
{
    return 0;
}

extern "C" int fn_8009F780(void)
{
    return fn_8011F4EC()->mUnknown10;
}

extern "C" int fn_8009FD7C(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    int value = p->mRatings[8] - (pOther->mRatings[0] / 8 + pOther->mRatings[3] / 8);

    if (value < lbl_803EA9D4) {
        value = lbl_803EA9D4;
    } else if (value > lbl_803EA9D8) {
        value = lbl_803EA9D8;
    }
    if (fn_802372EC(0, lbl_803EA9D0) < value) {
        result = 1;
    }
    return result;
}

extern "C" int fn_8009FE24(Object_80039F5C *p)
{
    int result = 0;
    Object_800670B4 *pObject = fn_80168708(p->mIdBytes[2]);

    if (p->mIdBytes[2] == fn_80178320()) {
        Record_8009FE24 *pRecord = fn_800AEE20(p);

        if (pRecord == 0) {
            if (pObject->mUnknown8.mUnknownF == 0) {
                pRecord = (Record_8009FE24 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
            } else {
                unsigned char index = fn_80163E94(pObject, p->mIdBytes[1], 0)->mUnknownB;

                pRecord = (Record_8009FE24 *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
            }
        }
        if ((pRecord->mUnknown0 & ~0x80) == 22 && (pRecord->mUnknown2 & 8)) {
            result = 1;
        }
    }
    return result;
}

extern "C" void fn_8009FF94(unsigned int value)
{
    lbl_8030C080[0]->mUnknown0 = value;
}

extern "C" unsigned int fn_8009FFA4(void)
{
    return lbl_8030C080[0]->mUnknown0;
}

extern "C" void fn_8009FFB4(unsigned int value)
{
    lbl_8030C080[0]->mUnknown4 = value;
}

extern "C" unsigned int fn_8009FFC4(void)
{
    return lbl_8030C080[0]->mUnknown4;
}

extern "C" void fn_800A0230(void)
{
    switch (fn_8009FFA4()) {
    case 0:
        break;
    case 1:
    case 4:
    case 6:
        fn_80067D4C(25, 0);
        break;
    case 2:
    case 5:
    case 7:
        fn_80067D4C(26, 0);
        break;
    }
}

extern "C" void fn_800A039C(Class_80297AB8 *pObject)
{
    if (pObject == 0) {
        lbl_803EA9E4 = &lbl_803EC900;
    } else {
        lbl_803EA9E4 = pObject;
    }
}

extern "C" void fn_800A061C(int a, int *p, int value)
{
    *p = value;
}

extern "C" void fn_800A0624(Record_800A0624 *p)
{
    fn_801D34D0(p, sizeof(Record_800A0624), 0, 4);
    p->mUnknown0 = 0;
    p->mUnknown4 = 0;
    fn_8009BD2C(0, &p->mUnknownC);
    fn_8009BD2C(0, &p->mUnknown10);
}

extern "C" void fn_800A0684(Record_800A0684 *p)
{
    fn_801D34D0(p, sizeof(Record_800A0684), 0, 4);
    fn_8009BD2C(0, &p->mUnknown0);
    p->mUnknown8 = fn_80177FE0();
    p->mUnknown4 = fn_80177F70();
    p->mUnknown1C = fn_80178308();
}

extern "C" int fn_800A1470(void)
{
    return 1;
}

extern "C" int fn_800A1478(void)
{
    return fn_800A1C50() != 1;
}

extern "C" void fn_800A14A8(Pair_800A14A8 *p)
{
    fn_800A1C74(p->mUnknown0, p->mUnknown4);
    fn_80194F1C(0);
    fn_80067D4C(124, 0);
}

extern "C" void fn_800A1A58(void)
{
    lbl_803EA9EC = 0;
    lbl_802D7C64[0].mUnknown4 = 1;
    lbl_802D7C64[0].mUnknown0 = 18;
    lbl_802D7C64[0].mUnknown5 = 0;
}

extern "C" void fn_800A1A80(void)
{
}

extern "C" int fn_800A1C50(void)
{
    fn_800B2320();
    return 1;
}

extern "C" void fn_800A20D0(int team, int delta)
{
    int value = fn_800C8774(team) + delta;

    fn_801787DC(team);
    value = value < -254 ? -254 : (value > 255 ? 255 : value);
    fn_801787FC(team, (short)value);
    fn_800C87CC(team, value);
    if (delta != 0) {
        fn_8017D6B8(team, value);
        fn_8017F384(1);
    }
}

extern "C" int fn_800A2160(void)
{
    return lbl_802D7C64[0].mUnknown4;
}

extern "C" void fn_800A216C(int value)
{
    lbl_802D7C64[0].mUnknown4 = value;
}

extern "C" int fn_800A2178(void)
{
    return lbl_802D7C64[0].mUnknown0;
}

extern "C" void fn_800A2184(void)
{
    lbl_803EA9EC = 0;
}

extern "C" void fn_800A2190(int bit)
{
    lbl_803EA9EC |= 1 << bit;
}
