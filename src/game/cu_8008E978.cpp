#include <string.h>

#include "engine/vptmanager.h"
#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/Class_80297BF8.h"
#include "game/Entry_800B206C.h"
#include "game/Entry_80219044.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_803EC99C.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Input_800B6D34.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/RecordList_8002E7C0.h"
#include "game/Record_800B15FC.h"
#include "game/Table_80089904.h"
#include "game/Team_80167A8C.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_80041210.h"
#include "game/cu_8003108C.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8008E978.h"
#include "game/fn_8007F828.h"
#include "game/fn_800670B4.h"
#include "game/fn_80096A58.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_80195EFC.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_80218FC4.h"
#include "game/fn_802270D4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80238174.h"
#include "game/fn_80094488.h"

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

/* 60-byte records that fn_80097440 copies into the buffer at +3048 of
   Record_80097518. */
struct Item_80097440 {
    unsigned char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    Vector_80039F5C mUnknown8;
    Vector_80039F5C mUnknown14;
    float mUnknown20;
    unsigned short mUnknown24;
    unsigned char mUnknown26[2];
    int mUnknown28;
    unsigned char mUnknown2C[12];
    int mUnknown38;
};

typedef Item_80097440 Item_8009A63C;

/* 8-byte entries from +8 of Record_80097518. */
struct Slot_80097440 {
    int mUnknown0;
    Item_80097440 *mpUnknown4;
};

/* 3080-byte records of the .bss array at 0x8030C2B8. */
struct Record_80097518 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned char mUnknown6[2];
    Slot_80097440 mUnknown8[380];
    Item_80097440 *mpUnknownBE8;
    unsigned short mUnknownBEC[7];
    unsigned short mUnknownBFA[7];
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

/* The 64-byte block fn_80099630 allocates under the id 'ctch'. */
struct Block_80099630 {
    int mUnknown0;
    unsigned char mUnknown4[60];
};

/* 24-byte entries at +44 of Block_8009C6F4. */
struct Entry_8009C684 {
    void (*mpCallback0)(Object_80039F5C *p, Vector_80039F5C *pVec, void *pData);
    Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[8];
};

/* Record passed to fn_8009C6F4, fn_8009C814 and fn_8009C88C. Only the
   accessed fields are declared; the size is unknown. */
struct Block_8009C6F4 {
    int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8[32];
    int mUnknown28;
    Entry_8009C684 mEntries[2];
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
int fn_800B9B18(void *p);
int fn_800C0458(void *p);
int fn_8009B9F0(int index);
int fn_800BD1BC(void *p);
int fn_800ABCDC(void);
void fn_801C1FBC(void *pDest, void *pSrc, unsigned int size);
void fn_800973AC(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_800975EC(int id, int flag, int index);
int fn_80097160(Object_80039F5C *p, float value);
void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);

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
extern Vector_80039F5C lbl_8030C0B4[];
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
extern Block_80099630 *lbl_803EC92C;
extern unsigned char lbl_803EA930;
extern float lbl_803EA934;

int fn_8005BE5C(int value);
void fn_8005BF18(void);
int fn_8005BFD4(void);
void fn_8005BF5C(void);
void fn_8002CFF4(Type_803EA368 *p);
void fn_8017DC44(void);
int fn_800B9B18(void *p);
void fn_8017DC88(void);
void fn_8013FA24(void);
void fn_8013FA8C(int a);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013C6F0(Camera_8013F738 *pCamera);
void fn_801D0508(void);
void fn_801D0C58(void *p);
void fn_801D0ADC(int a);
void fn_801D08FC(int a);
void fn_801D0CFC(float a);
void fn_801D0F80(float m[4][4]);
void fn_801D0544(void);
void fn_8009C3F8(Table_80089904 *pTable, void *a, void *b, void *pRecord, unsigned short c);
void fn_800AF87C(int a, int b, Vector_80039F5C *pVec, int c);
void fn_800AF82C(int a, int b, int c, int d, int e);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
int fn_8009C7B4(Vector_80039F5C *pVec);
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

extern "C" int fn_80091D34(void)
{
    unsigned char result = 0;

    if (fn_80027DF0() == 0) {
        switch (fn_800AD9B4()) {
        case 4:
            result = fn_800B9B18(lbl_803EAB84) != 0;
            break;
        case 2:
            result = fn_800C0458(lbl_803EABA4);
            break;
        }
    }
    return result;
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

extern "C" float fn_800921B0(Object_80039F5C *p, Camera_8013F738 *pCamera)
{
    Vector_80039F5C delta;

    fn_802276B4(&delta, &p->mpUnknown4->mUnknown4, pCamera->mHeader.mUnknown04);
    return fn_802270D4(&delta);
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

extern "C" void fn_800937CC(void)
{
    if (fn_8009B9F0(0)) {
        fn_8009B8C4(0);
    }
    fn_801F010C(lbl_803EC924->mpUnknown7C, 2);
    fn_800925A4();
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

extern "C" void fn_800943D8(void)
{
    if (fn_800AD9B4() == 1) {
        fn_80067DB8(108, 0, fn_800BD1BC(lbl_803EAB90), 0, 0);
    } else if (fn_800AD9B4() == 7) {
        fn_80067DB8(108, 0, fn_800ABCDC(), 0, 0);
    } else {
        fn_80067E3C(129, 0, 0, 0, 0, 0);
    }
}

extern "C" unsigned int fn_80094488(void)
{
    return lbl_803EA8C4;
}

extern "C" Vector_80039F5C *fn_80094490(int index)
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

extern "C" void fn_80095304(int id, Object_80039F5C **ppObject, unsigned short *pFound)
{
    int found = 0;

    if (fn_800312FC(lbl_803EA368, id) != 0) {
        Object_80039F5C *p = fn_80031294(lbl_803EA368, id);

        if (p->mUnknown9[2] != 0) {
            *ppObject = p;
            found = 1;
        }
    }
    *pFound = found;
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

extern "C" int fn_80096440(unsigned int id)
{
    int result = 0;

    switch (id) {
    case 0x50503031:
        result = 0;
        break;
    case 0x50503032:
        result = 1;
        break;
    case 0x50503033:
        result = 2;
        break;
    case 0x50503034:
        result = 3;
        break;
    case 0x50503035:
        result = 4;
        break;
    case 0x50503036:
        result = 5;
        break;
    case 0x50503037:
        result = 6;
        break;
    case 0x50503038:
        result = 7;
        break;
    case 0x50503039:
        result = 8;
        break;
    case 0x50503130:
        result = 9;
        break;
    case 0x50503131:
        result = 10;
        break;
    case 0x50503132:
        result = 11;
        break;
    case 0x50503133:
        result = 12;
        break;
    case 0x50503134:
        result = 13;
        break;
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

extern "C" void fn_80097028(Object_80039F5C *p)
{
    fn_80097160(p, lbl_803EA934);
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

extern "C" void fn_80097440(unsigned short count, int index)
{
    unsigned short i;

    lbl_8030C2B8[index].mpUnknownBE8 = (Item_80097440 *)fn_801D2B7C(count * sizeof(Item_80097440), 0, 0);
    for (i = 0; i < count; i++) {
        Item_80097440 *p = &lbl_8030C2B8[index].mpUnknownBE8[i];

        fn_801C1FBC(p, lbl_8030C2B8[index].mUnknown8[i].mpUnknown4, sizeof(Item_80097440));
        fn_800973AC(&p->mUnknown8, &p->mUnknown8);
        fn_800973AC(&p->mUnknown14, &p->mUnknown14);
        p->mUnknown28 = fn_80097430(p->mUnknown28);
        p->mUnknown38 = fn_80097430(p->mUnknown38);
        p->mUnknown24 = fn_8009740C(p->mUnknown24);
    }
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

/* Object whose word +0x328 points to a record with a halfword count at +4
   and whose word +0x32C points to that many 124-byte entries, as
   fn_800A3B10 reads them. Only these words are declared; the type is not
   established. */
struct Header_800A3B10 {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
};

struct Entry_800A3B10 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2[122];
};

struct Object_800A3B10 {
    unsigned char mUnknown0[0x328];
    Header_800A3B10 *mpUnknown328;
    Entry_800A3B10 *mpUnknown32C;
};

extern "C" {
Pair_800A554C *fn_8011F50C(void);
void fn_800A3530(void);
void fn_800A37D8(void);
void fn_800A3898(void);

extern void (*lbl_8030EFB4[11])(void);
extern int (*lbl_802D7E4C[21])(Object_80039F5C *p, Object_80039F5C *pTarget,
                                Object_80039F5C *pOther, Pair_800A554C *pPair);
}

extern "C" int fn_800A3B10(Object_800A3B10 *p)
{
    int count = 0;
    int i;

    if (p->mpUnknown328 != 0) {
        for (i = 0; i < p->mpUnknown328->mUnknown4; i++) {
            if (p->mpUnknown32C[i].mUnknown1 == 2) {
                count++;
            }
        }
    }
    return count;
}

extern "C" void fn_800A3D70(void)
{
    void (**ppCallback)(void) = lbl_8030EFB4;
    int i;

    for (i = 0; i < 11; i++) {
        *ppCallback++ = fn_800A3530;
    }
    lbl_8030EFB4[1] = fn_800A3898;
    lbl_8030EFB4[2] = fn_800A37D8;
    lbl_8030EFB4[3] = fn_800A3898;
    lbl_8030EFB4[4] = fn_800A3898;
    lbl_8030EFB4[5] = fn_800A3898;
}

extern "C" int fn_800A3E00(Object_80039F5C *p)
{
    int result = 0;

    switch ((unsigned int)p->mpState->mId) {
    case 2:
    case 22:
    case 30:
    case 40:
    case 62:
    case 85:
    case 92:
        if (p->mUnknown1032 < 4 || p->mUnknown1032 > 6) {
            result = 1;
        }
        break;
    }
    return result;
}

extern "C" int fn_800A554C(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           int index)
{
    int result = 1;
    Pair_800A554C *pPairs = fn_8011F50C();

    if (lbl_802D7E4C[index] != 0) {
        result = lbl_802D7E4C[index](p, pTarget, pOther, &pPairs[index]);
    }
    return result;
}

extern "C" void fn_800A5D94(void)
{
    Pair_800A554C *pPairs = fn_8011F50C();
    int i;

    for (i = 10; i >= 0; i--) {
        pPairs[i].mUnknown0 = 0;
    }
}

/* Partial view of the object whose word +0x28 fn_800C6640 decodes as a
   player reference. The size is unknown. */
struct Object_800C6640 {
    unsigned char mUnknown0[0x28];
    int mUnknown28;
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
    unsigned char mUnknown1B8[3];
    unsigned char mUnknown1BB[3];
    unsigned char mUnknown1BE[3];
    unsigned char mUnknown1C1[3];
    unsigned char mUnknown1C4;
    unsigned char mUnknown1C5;
};

typedef State_8011F4EC Record_8011F4EC;
typedef State_8011F4EC Block_8011F4EC;

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
int fn_8003DEB4(void);
void fn_80114D50(Object_80039F5C *p, Object_80039F5C *pOther);
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
State_8011F4EC *fn_8011F4EC(void);
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

extern "C" int fn_800C7084(Object_80039F5C *p, Object_80039F5C *pOther, int a, float value, int b)
{
    Query_800CE770 query;
    int result = 0;

    fn_800CE770(&query);
    query.mUnknown56 = result;
    query.mUnknown36 = b;
    query.mUnknown44 = value;
    query.mUnknown52 = a;
    query.mUnknown54 = 255;
    query.mpUnknown0 = p;
    query.mpUnknown4 = pOther;
    result = fn_800CE2B8(&query);
    if (result != 0) {
        p->mUnknown1219 = 1;
        fn_80114D50(p, pOther);
    }
    return result;
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

extern "C" void fn_800CA14C(void)
{
    unsigned int i;

    for (i = 0; i < fn_8003DEB4(); i++) {
        fn_8003DEC4(i)->mUnknown20 &= ~0x10000;
    }
    if (fn_800AD9B4() == 3) {
        unsigned char team;

        for (team = 0; team < 2; team++) {
            unsigned char j;

            for (j = 0; j < lbl_803EAC3C->mCounts[team]; j++) {
                lbl_803EAC3C->mEntries[team][j].mRef = 0;
            }
        }
        lbl_803EAC3C->mUnknown104 = 0;
        lbl_803EAC3C->mUnknown105 = 0;
        fn_800C9BB0();
        fn_800C9B78();
    }
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
        p = lbl_8030C2B8[record].mUnknown8[index].mpUnknown4;
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

extern "C" int fn_8009AD30(Object_80039F5C *p, int value)
{
    return value;
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

extern "C" int fn_8009B288(unsigned int *pState)
{
    int result = 1;

    switch (*pState) {
    case 0:
        fn_80067D4C(126, 0);
        if (fn_8005BE5C(0) == 0) {
            fn_8005BF18();
            fn_8005BE5C(0);
        }
        fn_800655B8();
        *pState = 1;
        break;
    case 1:
        if (fn_8005BFD4() == 1) {
            if (fn_800655F8() == 0) {
                fn_800655D0();
            }
            fn_8005BF5C();
            fn_8002CFF4(lbl_803EA368);
            fn_8017DC44();
            *pState = 2;
        }
        break;
    case 2:
        if (fn_800B9B18(lbl_803EAB84) == 2) {
            fn_8002CA74(lbl_803EA368, 9, 0);
        }
        if (fn_8002D060(lbl_803EA368) == 0) {
            Camera_8013F738 *pCamera;

            fn_8017DC88();
            result = 0;
            fn_8013FA8C(1);
            pCamera = fn_8013FA04(0);
            if (pCamera != 0) {
                fn_8013C6F0(pCamera);
            }
            fn_8013FA24();
        }
        break;
    default:
        result = 0;
        break;
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

extern "C" void fn_8009BDA0(float m[4][4], Vector_80039F5C *pPos, int angle, float scale)
{
    fn_801D0508();
    fn_801D0C58(pPos);
    fn_801D0ADC(angle + 0x400000);
    fn_801D08FC(0x400000);
    fn_801D0CFC(scale);
    fn_801D0F80(m);
    fn_801D0544();
}

extern "C" int fn_8009C470(Table_80089904 *pTable, unsigned short c, void *a, void *b, void *pRecord,
                           unsigned int count)
{
    if (count <= 1) {
        fn_8009C3F8(pTable, a, b, pRecord, c);
    }
    return 0;
}

extern "C" int fn_8009C56C(Table_80089904 *pTable, const unsigned char *pValues)
{
    int i;
    int best = -1;
    signed char result = -1;

    for (i = 0; i < pTable->mCount; i++) {
        const unsigned char *pBytes = &pTable->mEntries[i].mpInfo->mValue;
        int score = 0;
        int k;

        for (k = 0; k < 4; k++) {
            if (pValues[k] == *pBytes++) {
                score += 10 - k;
            }
        }
        if (score > best) {
            best = score;
            result = i;
        }
    }
    return result;
}

extern "C" void fn_8009C604(int (**pCallbacks)(Table_80089904 *, unsigned short, void *, void *, void *,
                                               unsigned int),
                            unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        pCallbacks[i] = fn_8009C470;
    }
}

extern "C" int fn_8009C684(Entry_8009C684 *pEntry, int a,
                           void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *), int b, int c)
{
    fn_801C1F94(pEntry->mUnknown10, 0, 8);
    pEntry->mpCallback0 = pCallback;
    if (c == 0) {
        c = 6;
    }
    fn_800AF87C(a, b, &pEntry->mUnknown4, c);
    return 2;
}

extern "C" Entry_8009C684 *fn_8009C6F4(int a, Block_8009C6F4 *pBlock,
                                       void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *),
                                       Vector_80039F5C *pVec, int c, int b, int d)
{
    Entry_8009C684 *pEntry = 0;

    if (pBlock->mUnknown0 != 0 && pBlock->mUnknown0 != 4) {
        fn_800AF82C(a, b, pBlock->mUnknown28, 0, d);
        pBlock->mUnknown6 = b;
        pBlock->mUnknown4 = pBlock->mUnknown4 == 0;
        pEntry = &pBlock->mEntries[pBlock->mUnknown4];
        pEntry->mUnknown4.mX = pVec->mX;
        pEntry->mUnknown4.mY = pVec->mY;
        pEntry->mUnknown4.mZ = pVec->mZ;
        pBlock->mUnknown0 = fn_8009C684(pEntry, a, pCallback, b, c);
    }
    return pEntry;
}

extern "C" int fn_8009C814(Object_80039F5C *p, Block_8009C6F4 *pBlock)
{
    Entry_8009C684 *pEntry = &pBlock->mEntries[pBlock->mUnknown4];

    if (pBlock->mUnknown0 == 2 && fn_8009C7B4(&pEntry->mUnknown4) == 1) {
        fn_8009CE88(p, &pBlock->mUnknown0, 6);
    }
    return pBlock->mUnknown0 > 1;
}

extern "C" void fn_8009C98C(void *p, Vector_80039F5C *pOut, int *pRef)
{
    fn_8009BF5C(fn_8009BCE8(pRef), pRef[1], pOut, 0);
}

extern "C" void fn_8009CC28(void)
{
}

extern "C" void fn_8009D00C(void *p, int *pState)
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

extern "C" {
void fn_8017DC08(void);
void fn_800B63B0(void);
void fn_800A9238(void);
void fn_800A9178(void);
}

extern "C" int fn_800A9680(void)
{
    return lbl_803EAA85;
}

extern "C" void fn_800A9688(void)
{
    fn_8017DC08();
    if (fn_80156704()) {
        fn_801574DC(0);
    }
    fn_800B63B0();
    fn_800A9238();
    fn_800A9178();
    lbl_803EAA85 = 1;
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
void fn_800AFDD4(void (*pCallback)(int, int, float));
void fn_800AFE20(void (*pCallback)(int, int, float));
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
extern Class_80297B50 lbl_803EC908;
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

extern "C" void fn_800B1758(int a, int b, float c)
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

extern "C" int fn_800B2314(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown5C;
}

extern "C" int fn_800B2320(void)
{
    return lbl_803EAB20->mUnknown4.mUnknown5A;
}

extern "C" int fn_800B232C(int index)
{
    return lbl_803EAB20->mUnknown4.mUnknown0[index].mUnknown0;
}

extern "C" Object_80039F5C *fn_800B2340(int index)
{
    return fn_8009BCE8(&lbl_803EAB20->mUnknown4.mUnknown0[index].mUnknown4);
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

extern "C" void fn_800B3644(Class_80297B50 *p)
{
    if (p == 0) {
        lbl_803EAB38 = &lbl_803EC908;
    } else {
        lbl_803EAB38 = p;
    }
}

extern "C" void fn_800B36F4(void)
{
    fn_800B3644(0);
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

extern "C" int fn_800B442C(void)
{
    return 25;
}

extern "C" void fn_800B4434(void)
{
    lbl_803EAB34->mUnknown8 &= ~6;
}

extern "C" void fn_800B49EC(Record_800B49EC *pDst, const Record_800B49EC *pSrc)
{
    *pDst = *pSrc;
}

extern "C" const char *lbl_802D87A4[];

extern "C" void fn_800B4A18(int index, char *pDest, int size)
{
    fn_801C3284(pDest, lbl_802D87A4[index], size);
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
void fn_800CC560(int a);
void fn_8013F3FC(void);
int fn_801F3E28(void);

extern Block_800BC538 *lbl_803EC98C;
extern int lbl_803EC990[2];
extern unsigned char lbl_803EAB94;
extern unsigned char lbl_803EAB95;
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
        lbl_803EC990[i] = (int)fn_800A9F4C(i);
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

extern "C" {
int fn_800C1E40(void);
void fn_8021956C(void *p, int a, int b, int c);
int fn_80169E68(int mode);
}

extern "C" void fn_800BC4E0(void)
{
    if (fn_800C1E40() == 0) {
        fn_8021956C(lbl_803EB688, 3, 8, 1);
    }
}

extern "C" void fn_800BC51C(Class_80297BF8 *pObject)
{
    if (pObject == 0) {
        lbl_803EAB90 = &lbl_803EC910;
    } else {
        lbl_803EAB90 = pObject;
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

extern "C" void fn_800975A4(unsigned char kind, int handle, unsigned char *pHigh, unsigned char *pLow)
{
    unsigned int value;

    if (pHigh == 0 || pLow == 0) {
        return;
    }
    value = (((unsigned int)handle >> 31) << 13) | (((kind & 3) << 14) | (handle & 0x7FF)) | (((handle >> 29) & 3) << 11);
    *pHigh = 0;
    *pLow = 0;
    *pHigh = value >> 8;
    *pLow = value;
}

extern "C" void fn_800996FC(int value);

extern "C" int fn_800994E0(void *p, int value)
{
    if (value & 1) {
        fn_800996FC(((Block_80099630 *)p)->mUnknown0);
    }
    return 0;
}

extern "C" void fn_80099568(int kind)
{
    switch (kind) {
    case 1:
    case 3:
        fn_800975EC(67, 1, 0);
        fn_800975EC(225, 1, 1);
        fn_800975EC(227, 1, 2);
        break;
    case 0:
    case 2:
        fn_800975EC(67, 1, 0);
        break;
    case 4:
        fn_800975EC(67, 0, 0);
        fn_800975EC(225, 0, 1);
        fn_800975EC(227, 0, 2);
        break;
    }
}

extern "C" void fn_80099630(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EC92C, sizeof(Block_80099630), 0, 0x63746368);
    unsigned char i;

    fn_80238234(pHandle, 0, 0, fn_800994E0, 0);
    fn_8023816C(pHandle);
    for (i = 0; i <= 2; i++) {
        lbl_8030C2B8[i].mpUnknownBE8 = 0;
        lbl_8030C2B8[i].mUnknown0 = 0;
    }
    lbl_803EA930 = 1;
    fn_802381E0(pHandle);
}

extern "C" void fn_800996D4(void)
{
    lbl_803EC92C = 0;
    fn_80097564();
}

extern "C" void fn_800996FC(int value)
{
    if (value == 21) {
        fn_80099568(0);
    } else {
        fn_80099568(1);
    }
}

extern "C" int fn_8009A1A8(Object_80039F5C *p, int handle, int b, int c, int kind)
{
    Message_800F01CC message;
    unsigned char high;
    unsigned char low;
    int result;

    if (p->mFlags & 0x800) {
        result = 0;
    } else {
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags &= ~4;
        fn_800C39E0(p, 224, b, c, handle < 0);
        fn_801C1F94(&message, 0, sizeof(Message_800F01CC));
        message.mId = 28;
        fn_800975A4(kind, handle, &high, &low);
        message.mUnknown1[0] = high;
        message.mUnknown1[1] = low;
        message.mUnknown1[2] = 0;
        fn_800F00D4(0, p->mpState, &message, p);
        result = 1;
    }
    return result;
}

extern "C" float fn_8009A270(int handle)
{
    return lbl_8030C2B8[(handle >> 29) & 3].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4->mUnknown20;
}

extern "C" int fn_8009A298(int handle)
{
    Item_80097440 *p = lbl_8030C2B8[(handle >> 29) & 3].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4;
    int result;

    if (handle < 0) {
        result = fn_8009740C(p->mUnknown24);
    } else {
        result = p->mUnknown24;
    }
    return result;
}

extern "C" int fn_8009A2EC(int handle)
{
    Item_80097440 *p = lbl_8030C2B8[(handle >> 29) & 3].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4;

    if (handle < 0) {
        fn_80097430(p->mUnknown38);
    }
    return p->mUnknown38;
}

extern "C" int fn_8009A578(int handle)
{
    return lbl_8030C2B8[(handle >> 29) & 3].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4->mUnknown4;
}

extern "C" int fn_8009A5A0(int handle)
{
    return lbl_8030C2B8[(handle >> 29) & 3].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4->mUnknown5 == 1;
}

extern "C" int fn_8009A5D4(int handle)
{
    return 0;
}

extern "C" void fn_8009A5DC(int high, int low, void *pKind, int *pHandle)
{
    unsigned short value;

    if (pKind == 0 || pHandle == 0) {
        return;
    }
    value = (high << 8) | low;
    *(unsigned char *)pKind = 0;
    *pHandle = 0;
    *(unsigned char *)pKind = value >> 14;
    *pHandle = value & 0x7FF;
    if (value & 0x2000) {
        *pHandle |= 0x80000000;
    }
    *pHandle |= ((value >> 11) & 3) << 29;
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
Message_800F01CC *fn_800AEE20(Object_80039F5C *p);
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
        Message_800F01CC *pRecord = fn_800AEE20(p);

        if (pRecord == 0) {
            if (pObject->mUnknown8.mUnknownF == 0) {
                pRecord = (Message_800F01CC *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mId >> 8 & 0xFF, p->mId >> 16 & 0xFF);
            } else {
                unsigned char index = fn_80163E94(pObject, p->mIdBytes[1], 0)->mUnknownB;

                pRecord = (Message_800F01CC *)fn_80164EC8(fn_8016871C(p->mIdBytes[2]), p->mIdBytes[2], index);
            }
        }
        if ((pRecord->mId & ~0x80) == 22 && (pRecord->mUnknown1[1] & 8)) {
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


typedef Block_800C9D6C Table_800CA8EC;

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
        result = lbl_803EAC3C->mEntries[index][item].mRef;
    }
    return result;
}

extern "C" int fn_800CAAC4(int index, unsigned int item)
{
    if (item >= lbl_803EAC3C->mCounts[index]) {
        return -1;
    }
    return lbl_803EAC3C->mEntries[index][item].mUnknown8;
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

/* One of the 12-byte entries of the array at +0 of Block_800B62D8. */
struct Entry_800B5224 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2[2];
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
};

/* Allocated through fn_80238174 under the id 'pctl' (fn_800B62D8). */
struct Block_800B62D8 {
    Entry_800B5224 *mpEntries;
    unsigned char mCount;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    unsigned char mUnknown8[10];
    unsigned char mUnknown12[10];
};

/* One of the 196-byte records of the array fn_800B8544 allocates. */
struct Record_800B8544 {
    unsigned char mUnknown0[188];
    unsigned int mUnknownBC;
    unsigned char mUnknownC0;
    unsigned char mUnknownC1[3];
};

/* The record array and its count, set by fn_800B8544. */
struct Pool_800B8544 {
    Record_800B8544 *mpRecords;
    unsigned char mCount;
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

/* Allocated through fn_80238174 under the id 'pstp' (fn_800B95B4, 360
   bytes). Only the accessed fields are named. */
struct Block_800B95B4 {
    Sequence_800C4460 mSequence;
    unsigned char mUnknown104[64];
    unsigned int mUnknown144;
    unsigned char mUnknown148;
    unsigned char mUnknown149[3];
    int mUnknown14C;
    unsigned char mUnknown150;
    unsigned char mUnknown151;
    unsigned char mUnknown152[2];
    int mUnknown154;
    unsigned char mUnknown158;
    unsigned char mUnknown159[3];
    int mUnknown15C;
    unsigned char mUnknown160;
    unsigned char mUnknown161[3];
    int mUnknown164;
};

extern "C" {
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_8023790C(void);
void fn_8003AE24(Object_80039F5C *p);
int fn_8009B9A8(int a);
int fn_800A8444(int team);
int fn_800BA6F8(void);
Step_800C4460 *fn_800C4658(Sequence_800C4460 *p);
void fn_800C46A0(Sequence_800C4460 *p);
void fn_800DC578(void);
int fn_800F0770(int a, State_80039F5C *pQueue, int which, int value, Object_80039F5C *p);
void fn_800F1800(int index);
Object_80039F5C *fn_80137B40(void);
int fn_801486A0(void);
int fn_801642DC(Object_800670B4 *p, unsigned char index);
int fn_80164384(Object_800670B4 *p, unsigned char index);
Object_800670B4 *fn_80168708(int team);
int fn_8017F60C(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_801C6458(int a, int b);
unsigned int fn_801E1954(void);
int fn_801E195C(int a);
void fn_800B5150(Object_80039F5C *p);
short fn_800B51D8(Object_800670B4 *p, unsigned short index, int mode);
void fn_800B5C68(Object_80039F5C *p, Vector_80039F5C *pVector, int *pA, int *pB);
int fn_800B5FEC(Object_80039F5C *p);
void fn_800B64C4(void);
Object_80039F5C *fn_800B6544(int index);
int fn_800B6644(int index);
void fn_800B6658(Object_80039F5C *p);
void fn_800B6714(Object_80039F5C *p, int index);
void fn_800B6988(int index);
int fn_800B7F34(Object_80039F5C *p);
int fn_800B9A90(Class_80297C60 *p);

extern unsigned char lbl_803EAB44;
extern Block_800B62D8 *lbl_803EAB60;
extern unsigned char lbl_803EAB74;
extern Block_800B95B4 *lbl_803EAB78;
extern Class_80297C60 lbl_803EC90C;
extern Pool_800B8544 lbl_803EC930;
extern float lbl_803ECB08;
}

extern "C" void fn_800B508C(unsigned char team)
{
    unsigned short i;
    unsigned int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        fn_8003AE24(fn_80039F5C(team, i));
    }
}

extern "C" void fn_800B50E8(int team)
{
    unsigned short i;
    unsigned int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        fn_8003AE24(p);
        fn_800B5150(p);
    }
}

extern "C" int fn_800B51D0(void)
{
    return 1;
}

extern "C" short fn_800B51D8(Object_800670B4 *p, unsigned short index, int mode)
{
    if (mode == 0) {
        return fn_801642DC(p, index);
    }
    return fn_80164384(p, index);
}

extern "C" int fn_800B5224(void *p, int value)
{
    Block_800B62D8 *pBlock = (Block_800B62D8 *)p;
    int i;

    pBlock->mpEntries = (Entry_800B5224 *)fn_801D2B7C(pBlock->mCount * sizeof(Entry_800B5224), 0, 0);
    for (i = 0; i < pBlock->mCount; i++) {
        pBlock->mpEntries[i].mUnknown0 = 0xFF;
        pBlock->mpEntries[i].mUnknown1 = 0xFF;
        pBlock->mpEntries[i].mUnknown4 = 0;
        pBlock->mpEntries[i].mUnknown8 = 0;
    }
    pBlock->mUnknown6[0] = 0xFF;
    pBlock->mUnknown6[1] = 0xFF;
    return 0;
}

extern "C" int fn_800B52D0(void *p, int value)
{
    Block_800B62D8 *pBlock = (Block_800B62D8 *)p;

    fn_801D2BD0(pBlock->mpEntries);
    pBlock->mpEntries = 0;
    return 0;
}

extern "C" int fn_800B530C(void *p, void *q)
{
    Block_800B62D8 *pBlock = (Block_800B62D8 *)p;
    Block_800B62D8 *pOther = (Block_800B62D8 *)q;
    int result = 0;

    if (pOther != 0) {
        result |= pBlock->mCount != pOther->mCount;
        result |= fn_80238258(pBlock->mpEntries, pOther->mpEntries, pBlock->mCount * sizeof(Entry_800B5224));
        result |= pBlock->mUnknown5 != pOther->mUnknown5;
        result |= pBlock->mUnknown6[0] != pOther->mUnknown6[0];
        result |= pBlock->mUnknown6[1] != pOther->mUnknown6[1];
    } else {
        result = fn_80238278(pBlock, sizeof(Block_800B62D8), 0);
        result = fn_80238278(pBlock->mpEntries, pBlock->mCount * sizeof(Entry_800B5224), result);
    }
    return result;
}

extern "C" int fn_800B53F4(void *p, void *pBuffer)
{
    Block_800B62D8 *pBlock = (Block_800B62D8 *)p;

    memcpy(pBuffer, pBlock, sizeof(Block_800B62D8));
    memcpy((char *)pBuffer + sizeof(Block_800B62D8), pBlock->mpEntries, pBlock->mCount * sizeof(Entry_800B5224));
    return 1;
}

extern "C" int fn_800B5448(void *p, void *pBuffer)
{
    Block_800B62D8 *pBlock = (Block_800B62D8 *)p;
    Block_800B62D8 *pSaved = (Block_800B62D8 *)pBuffer;

    *pBlock = *pSaved;
    memcpy(pBlock->mpEntries, pSaved + 1, pBlock->mCount * sizeof(Entry_800B5224));
    return 1;
}

extern "C" int fn_800B54C0(void *p)
{
    return lbl_803EAB60->mCount * sizeof(Entry_800B5224) + sizeof(Block_800B62D8);
}

extern "C" int fn_800B5F94(Object_80039F5C *p, Vector_80039F5C *pVector)
{
    int a;
    int b;

    fn_800B5C68(p, pVector, &a, &b);
    return a;
}

extern "C" int fn_800B5FC0(Object_80039F5C *p, Vector_80039F5C *pVector)
{
    int a;
    int b;

    fn_800B5C68(p, pVector, &a, &b);
    return b;
}

extern "C" void fn_800B62D8(int count)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAB60, sizeof(Block_800B62D8), 0, 0x7063746C);
    Block_800B62D8 *pBlock;
    int i;

    fn_80238234(pHandle, fn_800B5224, fn_800B52D0, 0, fn_800B530C);
    fn_80238248(pHandle, fn_800B53F4, fn_800B54C0, fn_800B5448);
    pBlock = (Block_800B62D8 *)fn_8023816C(pHandle);
    pBlock->mUnknown5 = 1;
    pBlock->mCount = count;
    for (i = 0; i < count; i++) {
        pBlock->mUnknown8[i] = 0xFF;
    }
    fn_800DC578();
    fn_802381E0(pHandle);
}

extern "C" void fn_800B63A4(void)
{
    lbl_803EAB60 = 0;
}

extern "C" void fn_800B63B0(void)
{
    unsigned int count = 7;
    unsigned short i;

    for (i = 0; i < count; i++) {
        fn_800B6658(fn_80039F5C(0, i));
        fn_800B6658(fn_80039F5C(1, i));
    }
}

extern "C" void fn_800B6408(void)
{
    unsigned int count = 7;
    unsigned short i;

    for (i = 0; i < count; i++) {
        fn_80039F5C(0, i)->mFlags &= ~0x4000;
        fn_80039F5C(1, i)->mFlags &= ~0x4000;
    }
}

extern "C" void fn_800B6474(int index, unsigned char value)
{
    Object_80039F5C *p = fn_800B6544(index);

    if (p != 0) {
        fn_800B6658(p);
    }
    lbl_803EAB60->mpEntries[index].mUnknown0 = value;
    fn_800B64C4();
}

extern "C" void fn_800B64C4(void)
{
    unsigned char team;
    unsigned char i;

    lbl_803EAB60->mUnknown6[0] = 0xFF;
    lbl_803EAB60->mUnknown6[1] = 0xFF;
    for (team = 0; team <= 1; team++) {
        for (i = 0; i < lbl_803EAB60->mCount; i++) {
            if (lbl_803EAB60->mpEntries[i].mUnknown0 == team) {
                lbl_803EAB60->mUnknown6[team] = i;
                break;
            }
        }
    }
}

extern "C" Object_80039F5C *fn_800B6544(int index)
{
    Entry_800B5224 *pEntry = &lbl_803EAB60->mpEntries[index];
    Object_80039F5C *p = 0;

    if (pEntry->mUnknown0 != 0xFF && pEntry->mUnknown1 != 0xFF) {
        p = fn_80039F5C(pEntry->mUnknown0, pEntry->mUnknown1);
    }
    return p;
}

extern "C" int fn_800B65A0(int team)
{
    if ((unsigned int)team <= 1) {
        return lbl_803EAB60->mUnknown6[team];
    }
    return 0xFF;
}

extern "C" void fn_800B65C0(int team, unsigned char index)
{
    lbl_803EAB60->mUnknown6[team] = index;
}

extern "C" int fn_800B65D0(int team)
{
    unsigned char result = 0xFF;
    int i;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        if (team == fn_800B6644(i) && i != lbl_803EAB60->mUnknown6[team]) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int fn_800B6644(int index)
{
    return lbl_803EAB60->mpEntries[index].mUnknown0;
}

extern "C" void fn_800B6658(Object_80039F5C *p)
{
    if (p->mUnknown8 != 0xFF) {
        lbl_803EAB60->mpEntries[p->mUnknown8].mUnknown1 = 0xFF;
        lbl_803EAB60->mpEntries[p->mUnknown8].mUnknown4 = 0;
        lbl_803EAB60->mpEntries[p->mUnknown8].mUnknown8 = 0;
        fn_800F0770(0, &p->mUnknown3048, 4, 0, p);
        fn_800F1800(p->mUnknown8);
    }
    p->mUnknown8 = 0xFF;
    p->mUnknown9[1] = 0;
    p->mFlags &= ~0x400;
    p->mFlags &= ~0x4000;
}

extern "C" void fn_800B6714(Object_80039F5C *p, int index)
{
    Object_80039F5C *pOther;

    if (p->mUnknown8 != (unsigned char)index) {
        fn_800B6658(p);
        pOther = fn_800B6544(index);
        if (pOther != 0) {
            fn_800B6658(pOther);
        }
        if (index != 0xFF) {
            fn_800F1800((unsigned char)index);
        }
        p->mUnknown8 = index;
        p->mFlags |= 0x400;
        if (p->mIdBytes[2] == fn_80178320() && fn_801486A0() != 0) {
            p->mUnknown9[1] = lbl_803EAB44;
        } else {
            p->mUnknown9[1] = 0;
        }
        p->mFlags &= ~0x4000;
        p->mFlags |= 0x2000000;
        lbl_803EAB60->mpEntries[index].mUnknown1 = p->mIdBytes[1];
        lbl_803EAB60->mpEntries[index].mUnknown4 = 0;
        lbl_803EAB60->mpEntries[index].mUnknown8 = 0;
    }
}

extern "C" void fn_800B67FC(Object_80039F5C *p, Object_80039F5C *pOther)
{
    unsigned char index;

    if ((p->mFlags & 0x400) && !(pOther->mFlags & 0x400)) {
        index = p->mUnknown8;
        if (index != 0xFF) {
            fn_800F1800(index);
        }
        fn_800B6658(p);
        fn_800B6714(pOther, index);
    }
}

extern "C" void fn_800B6868(int team, int index, int slot, int mode)
{
    Object_800670B4 *pTeam;
    Object_80039F5C *p;
    Object_80039F5C *pOther;
    short tries;

    if (fn_801486A0() != 0 && fn_801486A0() != 1) {
        tries = 7;
        pTeam = fn_80168708(team);
        if (index != 0xFF) {
            if (mode != 2 && mode != 3) {
                index = fn_800B51D8(pTeam, index, mode);
            }
            fn_80067DB8(16, 0, team, 0, 0);
        } else {
            index = 0;
        }
        if (mode == 2 || mode == 3) {
            mode -= 2;
        }
        do {
            p = fn_80039F5C(team, index);
            if (p->mUnknown8 == 0xFF) {
                pOther = fn_800B6544(slot);
                if (pOther != 0) {
                    fn_800B6658(pOther);
                }
                fn_800B6714(p, (unsigned char)slot);
                return;
            }
            index = fn_800B51D8(pTeam, index, mode);
            tries--;
        } while (tries > 0);
    }
}

extern "C" void fn_800B6C98(void)
{
    int team = fn_80178320();
    int other = fn_80178308();
    int i;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        if (lbl_803EAB60->mpEntries[i].mUnknown0 != 0xFF) {
            if (lbl_803EAB60->mpEntries[i].mUnknown0 == team) {
                lbl_803EAB60->mUnknown8[i] = lbl_803EAB60->mpEntries[i].mUnknown1;
            } else if (lbl_803EAB60->mpEntries[i].mUnknown0 == other) {
                lbl_803EAB60->mUnknown12[i] = lbl_803EAB60->mpEntries[i].mUnknown1;
            }
        }
    }
}

extern "C" int fn_800B7368(void)
{
    return 0;
}

extern "C" int fn_800B7370(void)
{
    return 0;
}

extern "C" int fn_800B7F34(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_801374BC();
    fn_800B6D34(p, &input);
    if (input.mUnknown93 & 0x10) {
        fn_800B6988(p->mUnknown8);
        return 0;
    }
    return 0;
}

extern "C" int fn_800B7F88(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_801374BC();
    fn_800B6D34(p, &input);
    if (p->mIdBytes[2] == fn_80178320() && (input.mUnknown93 & 0x10)) {
        fn_800B6988(p->mUnknown8);
    }
    return 0;
}

extern "C" int fn_800B7FE8(Object_80039F5C *p)
{
    if (p == fn_80137B40()) {
        return 0;
    }
    return fn_800B7F34(p);
}

extern "C" int fn_800B81A4(void)
{
    int i;
    int value;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        if (fn_800B6644(i) != 0xFF) {
            value = fn_801C6458(i, 0);
            if ((fn_8017F60C() == 0 || value < fn_801E1954()) && fn_801E195C(value) != 2) {
                return (unsigned char)i;
            }
        }
    }
    return 0xFF;
}

extern "C" int fn_800B823C(int team)
{
    unsigned char count = 0;
    int i;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        if (fn_800B6644(i) == team) {
            count++;
        }
    }
    return count;
}

extern "C" void fn_800B82AC(int team)
{
    Object_80039F5C *p;
    int i;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        if (fn_800B6644(i) == team) {
            p = fn_800B6544(i);
            p->mUnknown512.mUnknown14 = 1;
            p->mFlags |= 0x4000;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        }
    }
}

extern "C" void fn_800B8344(Object_80039F5C *p)
{
    Object_80039F5C *pCurrent = fn_80137B40();

    if (pCurrent == p && pCurrent->mUnknown8 != 0xFF && fn_800B5FEC(pCurrent) != 0) {
        pCurrent->mFlags |= 0x4000;
    }
}

extern "C" int fn_800B83A0(Object_80039F5C *p)
{
    int rating = p->mRatings[0];

    if (rating > 99) {
        return 1;
    }
    return (unsigned short)fn_802372EC(0, 100) <= rating;
}

extern "C" int fn_800B83F4(Object_80039F5C *p)
{
    int rating;
    unsigned char roll;
    int result;

    if (fn_800A8444(p->mIdBytes[2]) != 0) {
        return 0;
    }
    rating = p->mRatings[0];
    roll = fn_802372EC(0, 100);
    result = 0;
    if (rating <= 102) {
        result = roll < 90;
    } else if (rating <= 178 && roll <= 49) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800B847C(int index, unsigned char value)
{
    if (lbl_803EAB60 != 0) {
        lbl_803EAB60->mUnknown8[index] = value;
    }
}

extern "C" void fn_800B852C(void)
{
    lbl_803EAB74 = 1;
}

extern "C" void fn_800B8538(void)
{
    lbl_803EAB74 = 0;
}

extern "C" void fn_800B8544(unsigned char count)
{
    Record_800B8544 *pRecord;
    int i;

    lbl_803EC930.mCount = count;
    lbl_803EC930.mpRecords = (Record_800B8544 *)fn_801D2B7C(count * sizeof(Record_800B8544), 0, 0);
    for (i = 0; i < count; i++) {
        pRecord = &lbl_803EC930.mpRecords[i];
        memset(pRecord, 0, sizeof(pRecord->mUnknown0));
        pRecord->mUnknownC0 = 1;
        pRecord->mUnknownBC = 0;
    }
}

extern "C" void fn_800B85C8(void)
{
    fn_801D2BD0(lbl_803EC930.mpRecords);
    lbl_803EC930.mpRecords = 0;
    lbl_803EC930.mCount = 0;
}

extern "C" void fn_800B8608(void)
{
    Record_800B8544 *pRecord;
    int i;

    for (i = 0; i < lbl_803EC930.mCount; i++) {
        pRecord = &lbl_803EC930.mpRecords[i];
        memset(pRecord, 0, sizeof(pRecord->mUnknown0));
        if (pRecord->mUnknownC0 == 0 && pRecord->mUnknownBC <= fn_8023790C()) {
            pRecord->mUnknownC0 = 1;
        }
    }
}

extern "C" Record_800B8544 *fn_800B8694(int index)
{
    return &lbl_803EC930.mpRecords[index];
}

extern "C" void fn_800B86A4(int index)
{
    Block_800B95B4 *p = lbl_803EAB78;

    if (p->mUnknown160 != 0 && (p->mUnknown164 == 2 || p->mUnknown164 == fn_800B6644(index))
        && (fn_800B6644(index) == 0 || fn_800B6644(index) == 1) && fn_8002D060(lbl_803EA368) == 0) {
        switch (lbl_803EAB78->mUnknown14C) {
        case 0:
            lbl_803EAB78->mUnknown144 = 0;
        case 1:
            lbl_803EAB78->mUnknown14C = 2;
            break;
        }
        if (fn_800BA6F8() != 0) {
            lbl_803EAB78->mUnknown148 = 1;
        }
    }
}

extern "C" void fn_800B8940(void)
{
    if (lbl_803EAB78->mUnknown158 == 1 && (unsigned char)fn_800B9A90(lbl_803EAB84) == 1) {
        lbl_803EAB78->mUnknown158 = 0;
    }
}

extern "C" int fn_800B898C(void *p, void *q)
{
    int result;

    if (q != 0) {
        result = fn_80238258(p, q, sizeof(Block_800B95B4));
    } else {
        result = fn_80238278(p, sizeof(Block_800B95B4), 0);
    }
    return result;
}

extern "C" void fn_800B9598(Class_80297C60 *p)
{
    if (p == 0) {
        lbl_803EAB84 = &lbl_803EC90C;
    } else {
        lbl_803EAB84 = p;
    }
}

extern "C" void *fn_800B9A44(Class_80297C60 *p)
{
    return fn_800C4658(&lbl_803EAB78->mSequence);
}

extern "C" void fn_800B9A6C(Class_80297C60 *p, void *q)
{
    fn_800C46A0(&lbl_803EAB78->mSequence);
}

extern "C" int fn_800B9A90(Class_80297C60 *p)
{
    return lbl_803EAB78->mUnknown151;
}

extern "C" int fn_800B9B18(void *p)
{
    if (fn_8009B9A8(0) != 0 || lbl_803EAB78->mUnknown144 > 120) {
        return lbl_803EAB78->mUnknown14C;
    }
    return 0;
}

extern "C" void fn_800B9B64(Class_80297C60 *p, int enable, int value)
{
    lbl_803EAB78->mUnknown160 = enable;
    lbl_803EAB78->mUnknown164 = enable != 0 ? value : 2;
    if (enable == 0) {
        lbl_803EAB78->mUnknown14C = 0;
    }
}

extern "C" void fn_800B9B9C(Class_80297C60 *p)
{
    lbl_803EAB78->mUnknown150 = 1;
}

extern "C" void fn_800B9BAC(Class_80297C60 *p)
{
    lbl_803EAB78->mUnknown151 = 1;
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


/* 3044-byte records of the array at 0x803103F0. */
struct Record_800C432C {
    Table_80089904 mTable;
    unsigned char mUnknown12[3032];
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
void fn_800C1E5C(int a, int b, float c);
void fn_800AFDD4(void (*pCallback)(int, int, float));
void fn_800AFE20(void (*pCallback)(int, int, float));
void fn_8013FA8C(int a);
void fn_8013F97C(int a);
unsigned char fn_801374D4(void);
void fn_8013FA58(int a, int b);
void fn_800BA804(int a);
int fn_8016E764(void);
int fn_80178308(void);
int fn_80178320(void);
Object_80039F5C *fn_800B6544(int index);
void fn_800B6868(int a, int b, int c, int d);
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
State_8011F4EC *fn_8011F4EC(void);
int fn_801787A0(void);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_801BE648(void *p);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A578(int handle);
void fn_801F51DC(int a, void *pBase, int count, int size,
                 int (*pCompare)(Entry_800C3130 *, Entry_800C3130 *),
                 void (*pSwap)(Entry_800C3130 *, Entry_800C3130 *), int b, int c);

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
    fn_801BBC3C(1, 196, &lbl_803103F0[0].mTable);
    fn_801BBC3C(1, 197, &lbl_803103F0[1].mTable);
    fn_801BBC3C(1, 195, &lbl_803103F0[2].mTable);
    fn_801BBC3C(1, 210, &lbl_803103F0[3].mTable);
    fn_801BBC3C(1, 224, &lbl_803103F0[4].mTable);
    fn_801BBC3C(1, 228, &lbl_803103F0[5].mTable);
    fn_801BBC3C(1, 230, &lbl_803103F0[6].mTable);
    fn_801BBC3C(1, 229, &lbl_803103F0[7].mTable);
    fn_801BBC3C(1, 235, &lbl_803103F0[8].mTable);
    fn_801BBC3C(1, 237, &lbl_803103F0[9].mTable);
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

extern "C" void fn_800BC5B8(void)
{
    fn_800BC51C(0);
}

extern "C" void fn_800BCAF4(float value)
{
    fn_800AD910(5, value);
}

extern "C" void fn_800BD184(void)
{
    lbl_803EAB94 = 1;
}

extern "C" int fn_800BD1BC(void *p)
{
    return lbl_803EAB95 & 1;
}

extern "C" void fn_800BD99C(int team)
{
    if (fn_800BA6F8() == 0 && fn_800B65A0(team) == 255) {
        if (team == fn_80178320()) {
            fn_80169EF4(2);
        } else {
            fn_80169E68(2);
        }
    }
}

