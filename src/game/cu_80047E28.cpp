#include "engine/cu_80227F14.h"
#include "game/FELoop.h"
#include "game/Object_8007A334.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8008044C.h"
#include "game/fn_800624B0.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C3284.h"
#include "game/fn_802372EC.h"

/* Four bytes copied as one word from lbl_802CFB1C and passed by value. */
struct Colors_802CFB1C {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Three bytes read by fn_800840A4. */
struct Rgb_800840A4 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
};

/* Key/value pair for fn_8015FFC8; a key of 0xFFFF ends a list. */
struct Pair_802CF382 {
    unsigned short mKey;
    unsigned short mValue;
};

/* 40-byte block filled by fn_80082138 and read by fn_80046898. */
struct Block_80307980 {
    int mUnknown0[10];
};

/* Element of lbl_803078E8 (14 records of 0xC0 bytes). */
struct Record_803078E8 {
    char mName[32];
    Info_80307908 mInfo;
    unsigned char mUnknown68;
    char mUnknown69;
    unsigned short mUnknown6A;
    unsigned short mUnknown6C;
    unsigned short mUnknown6E;
    unsigned short mUnknown70;
    unsigned char mUnknown72;
    unsigned char mUnknown73;
    unsigned char mUnknown74;
    unsigned char mUnknown75;
    unsigned char mUnknown76;
    unsigned char mUnknown77;
    unsigned char mUnknown78;
    char mUnknown79;
    unsigned char mUnknown7A[25];
    unsigned char mUnknown93;
    unsigned char mUnknown94;
    unsigned char mUnknown95;
    char mUnknown96[2];
    Block_80307980 mBlock;
};

/* Element of lbl_80308368 (14 records of 0x18 bytes). */
struct Entry_80308368 {
    int mId;
    unsigned short mValues[10];
};

/* 128-byte row read by fn_8007BC34. */
struct Row_8007BC34 {
    char mUnknown00[8];
    int mUnknown08;
    char mUnknown0C[37];
    char mName[33];
    char mUnknown52[18];
    int mUnknown64;
    char mUnknown68[8];
    unsigned char mUnknown70;
    unsigned char mUnknown71;
    unsigned char mUnknown72;
    unsigned char mUnknown73;
    unsigned char mUnknown74;
    unsigned char mUnknown75;
    unsigned char mUnknown76;
    unsigned char mUnknown77;
    int mUnknown78;
    char mUnknown7C[4];
};

struct Item_800476DC {
    char mUnknown00[28];
    unsigned char mUnknown1C;
};

/* Creation argument of fn_8004A040. */
struct Init_8004A040 {
    int mUnknown00;
    int mUnknown04;
    char mUnknown08[8];
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
};

/* Query passed to fn_80083E40; fn_80083E40 builds the same default. */
struct Query_80083E40 {
    Query_80083E40() : mUnknown0(1), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
extern Record_803078E8 lbl_803078E8[14];
extern Entry_80308368 lbl_80308368[14];
extern Pair_802CF382 lbl_802CF382[];
extern Pair_802CF382 lbl_802CF3EE[45][9];
extern int lbl_802CFA44[54];
extern Colors_802CFB1C lbl_802CFB1C[22];
extern int lbl_802CFB74[22];
extern unsigned char lbl_803EA4CA;

int fn_8001E4F4(void);
int fn_8003DEB4(void);
void fn_80042610(Object_8003DEC4 *pPlayer, int a, void *b, int c, int d);
void fn_800428A8(Object_8003DEC4 *pPlayer);
int fn_80046898(Block_80307980 *pBlock);
void fn_800476DC(Item_800476DC *pItem, void *p);
void fn_800478DC(unsigned char *pColors);
void fn_8004795C(unsigned char *pColors, unsigned char flag);
void fn_800479B0(Row_8007BC34 *pRow, Record_803078E8 *pRecord, int *pIds, int *pPalettes, int slot);
int fn_80047C84(Row_8007BC34 *pRow);
void fn_80047CA4(int *pIds, Record_803078E8 *pRecord);
unsigned char fn_80054D24(int index);
int fn_8005FC7C(void);
void fn_8007BA48(Object_8007A334 *pObject);
void fn_8007BA88(Object_8007A334 *pObject, int a);
void fn_8007BB04(Object_8007A334 *pObject);
int fn_8007BB84(Object_8007A334 *pCursor, int a, int b, int *pResult);
void fn_8007BC34(Object_8007A334 *pObject, Row_8007BC34 *pRow);
unsigned int fn_8007BDF8(Object_8007A334 *pObject);
int fn_8007BF14(int index);
int fn_8007CB6C(int index);
int fn_80080970(Object_8008044C *pObject);
void fn_80080A9C(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80080CB0(Object_8008044C *pObject);
int fn_80080E48(Object_8008044C *pObject);
int fn_80080E70(Object_8008044C *pObject);
int fn_80080E98(Object_8008044C *pObject);
int fn_8008125C(Object_8008044C *pObject);
void fn_80081440(Object_8008044C *pObject, unsigned short *pValues);
void fn_80081C10(Object_8008044C *pObject, unsigned char *p);
void fn_80081CDC(void);
void fn_80081D24(void);
int fn_80081D4C(Object_8008044C *pObject, unsigned char *p);
int fn_80081E3C(Object_8008044C *pObject);
int fn_80081FD4(Object_8008044C *pObject, int a);
void fn_80082138(Object_8008044C *pObject, Block_80307980 *pBlock);
int fn_80082280(Object_8008044C *pObject);
int fn_800822D4(Object_8008044C *pObject);
void fn_800840A4(Object_8007A334 *pObject, void *pBuffer);
void fn_80146094(void *p);
void fn_8015F6E8(int a, int b, int c, int d, int e);
void fn_8015FFC8(int player, int key, int value);
void fn_80160E94(int index, int slot, int id, int palette, int d);
int fn_80161048(char *pName);
void fn_801610B0(int index, unsigned char *pColors);
void fn_8016139C(int a, int *pId, int *pPalette);
int fn_801835A0(void);
void fn_801A34B0(int a, int b, int c, int d);
void fn_801A3520(void);
void fn_801A3588(Object_8003DEC4 *pPlayer, Init_8004A040 *pInit);
void fn_801A3C40(Object_8003DEC4 *pPlayer);
void fn_801A3F48(Object_8003DEC4 *pPlayer);
void fn_801A4AD4(Object_8003DEC4 *pPlayer);
int fn_801486A0(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C302C(const char *s1, const char *s2, int n);
int fn_801DCF0C(int a, int b, int c, void (*pA)(Object_8003DEC4 *, Init_8004A040 *), void (*pB)(Object_8003DEC4 *));
void fn_801DCF8C(int a);
void fn_801DD0C8(int handle, int a, int b, int (*pCallback)(Object_8003DEC4 *, int));
}

extern "C" void fn_80049F10(int index, Block_80307980 *pBlock);

static Object_8008044C lbl_80307720;
static Object_8007A334 lbl_8030774C;

extern "C" void fn_80047E28(int index)
{
    int a = 0;
    int b;
    int c;
    Object_8007A334 cursor;

    fn_8007BA88(&cursor, 11);
    a = fn_8007A410(&cursor);
    fn_8007BB04(&cursor);
    fn_8007BA88(&cursor, 12);
    b = fn_8007A410(&cursor);
    fn_8007BB04(&cursor);
    fn_8007BA88(&cursor, 1);
    c = fn_8007A410(&cursor);
    fn_8007BB04(&cursor);
    int x = fn_802372EC(0, a - 1) + 1;
    int y = fn_802372EC(0, b);
    int z = fn_802372EC(0, c - 1) + 1;
    lbl_803078E8[index].mInfo.mValues[12] = x;
    lbl_803078E8[index].mInfo.mValues[13] = y;
    lbl_803078E8[index].mInfo.mValues[1] = z;
}

extern "C" void fn_80047F24(int player, int index)
{
    Pair_802CF382 pair;
    int i;

    for (i = 0, pair = lbl_802CF3EE[index][0]; pair.mKey != 0xFFFF; pair = lbl_802CF3EE[index][++i]) {
        fn_8015FFC8(player, pair.mKey, pair.mValue);
    }
}

extern "C" void fn_80047FA4(Row_8007BC34 *pRow, Info_80307908 *pInfo, int player, int slot)
{
    int type = pRow->mUnknown64;

    if (type == 63) {
        return;
    }
    if ((unsigned int)type > 53) {
        return;
    }
    switch (type) {
    case 22:
        if (pInfo->mUnknown00 & 1) {
            fn_80047F24(player, 22);
        }
        if (pInfo->mUnknown00 & 2) {
            fn_80047F24(player, 23);
        }
        break;
    case 25:
        if (pInfo->mUnknown01 & 1) {
            fn_80047F24(player, 26);
        }
        if (pInfo->mUnknown01 & 2) {
            fn_80047F24(player, 27);
        }
        break;
    case 26:
        if (pInfo->mUnknown01 & 1) {
            fn_80047F24(player, 28);
        }
        if (pInfo->mUnknown01 & 2) {
            fn_80047F24(player, 29);
        }
        break;
    default:
        if (lbl_802CFA44[pRow->mUnknown64] != 255) {
            fn_80047F24(player, lbl_802CFA44[pRow->mUnknown64]);
        }
        break;
    }
}

extern "C" void fn_800480C8(int base, unsigned int number, unsigned char home, int player, int *pIds, int *pPalettes, int kind)
{
    int id;
    int numberId;

    number--;
    if (kind == 3) {
        int partial;
        unsigned int offset;

        numberId = number + 0x3BDD;
        offset = number * 200;
        partial = !home ? offset + 0x1969 : offset + 0x1905;
        id = partial + base;
        pIds[23] = numberId;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        switch (number + 1) {
        case 26:
            fn_8015FFC8(player, 22, 255);
            fn_8015FFC8(player, 21, 2);
            break;
        case 15:
        case 25:
        case 27:
            fn_8015FFC8(player, 22, 0);
            fn_8015FFC8(player, 21, 0);
            break;
        case 7:
            if (home == 0) {
                fn_8015FFC8(player, 22, 0);
                fn_8015FFC8(player, 21, 1);
                break;
            }
        case 1:
        case 3:
        case 8:
        case 9:
        case 10:
        case 23:
        case 30:
            fn_8015FFC8(player, 22, 255);
            fn_8015FFC8(player, 21, 2);
            break;
        case 6:
        case 12:
        case 14:
        case 17:
        case 21:
        case 22:
        case 24:
        case 28:
        case 31:
        case 32:
            fn_8015FFC8(player, 22, 0);
            fn_8015FFC8(player, 21, 1);
            break;
        case 2:
        case 4:
        case 5:
        case 11:
        case 13:
        case 16:
        case 18:
        case 19:
        case 20:
        case 29:
            fn_8015FFC8(player, 22, 0);
            fn_8015FFC8(player, 21, 255);
            break;
        }
    } else {
        int partial;
        unsigned int offset;

        numberId = number + 0x3BDD;
        offset = number * 200;
        partial = !home ? offset + 0x69 : offset + 5;
        id = partial + base;
        pIds[23] = numberId;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        switch (number + 1) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            fn_8015FFC8(player, 22, 0);
            fn_8015FFC8(player, 21, 255);
            break;
        case 8:
        case 10:
        case 21:
        case 24:
            fn_8015FFC8(player, 22, 255);
            fn_8015FFC8(player, 21, 255);
            break;
        }
    }
    fn_8015FFC8(player, 23, 0);
}

extern "C" void fn_80048388(Row_8007BC34 *pRow, int offset, unsigned char flag, int player, int *pIds, int *pPalettes)
{
    char name[82];
    int id;

    fn_801C2D88(name, sizeof(name), "PLATEX_DECAL_%s_CHICAGO", pRow->mName);
    id = fn_80161048(name);
    if (id >= 0) {
        id += offset;
        pIds[23] = id;
        pIds[24] = id;
        pPalettes[23] = -1;
        pPalettes[24] = -1;
        Colors_802CFB1C colors = lbl_802CFB1C[pRow->mUnknown64];
        if (pRow->mUnknown71) {
            if (pRow->mUnknown72) {
                fn_8015FFC8(player, 19, colors.mUnknown3);
            } else {
                fn_8015FFC8(player, 19, colors.mUnknown1);
            }
        }
        if (pRow->mUnknown70) {
            fn_8015FFC8(player, 20, colors.mUnknown1);
        }
    }
}

extern "C" void fn_80048470(Row_8007BC34 *pRow, int offset, int player, int *pIds, int *pPalettes)
{
    char name[82];
    int id;

    fn_801C2D88(name, sizeof(name), "PLATEX_DECAL_%s_CHICAGO", pRow->mName);
    id = fn_80161048(name);
    if (id >= 0) {
        if (fn_801C302C(pRow->mName, "REEBOK_T045Z", 33) == 0 || fn_801C302C(pRow->mName, "REEBOK_BO04A381", 33) == 0) {
            pIds[3] = 3;
            pPalettes[2] = -1;
        } else {
            pIds[3] = 4;
            pPalettes[2] = -1;
        }
        id += offset;
        pIds[2] = id;
        pPalettes[2] = -1;
        fn_8015FFC8(player, 25, 0);
        fn_8015FFC8(player, 26, 0);
    }
}

extern "C" void fn_80048554(int number, int player, int *pId, int *pPalette)
{
    *pId = number + 0x3FEE;
    *pPalette = -1;
    fn_8015FFC8(player, 20, 1);
}

extern "C" void fn_80048590(int kind, int key, Colors_802CFB1C colors, unsigned char number, unsigned int index,
                            unsigned char flag, unsigned char home, unsigned char single, int player, int *pId,
                            int *pPalette)
{
    unsigned char c1 = colors.mUnknown1;
    unsigned char c0 = colors.mUnknown0;
    unsigned char c2 = colors.mUnknown2;
    unsigned int id;

    if (single) {
        c1 = colors.mUnknown3;
        c0 = c1;
        c2 = c1;
    }
    switch (kind) {
    case 0:
        break;
    case 1:
        if (number > 99) {
            number = 0;
        }
        *pId = number + 0x3B10;
        *pPalette = 0xAB;
        fn_8015FFC8(player, key, c2);
        break;
    case 2:
        if (home) {
            *pId = index + 0x3B97;
        } else {
            *pId = index + 0x3B74;
        }
        *pPalette = -1;
        fn_8015FFC8(player, key, c0);
        break;
    case 3:
        *pId = index + 0x3BBA;
        *pPalette = 0xA9;
        fn_8015FFC8(player, key, c1);
        break;
    case 4:
        *pId = index + 0x3BBA;
        *pPalette = 0xA9;
        fn_8015FFC8(player, key, c0);
        break;
    case 5:
        id = index + 0x3BDD;
        *pId = id;
        if (id > 0x3C60) {
            *pId = 0x3C0A;
        }
        *pPalette = flag ? -1 : 0xAD;
        fn_8015FFC8(player, key, c1);
        break;
    default:
        *pId = kind + 0x31FF;
        *pPalette = -1;
        fn_8015FFC8(player, key, c1);
        break;
    }
}

extern "C" void fn_80048704(Row_8007BC34 *pRow, Info_80307908 *pInfo, unsigned char number, int index,
                            unsigned char flag, unsigned char home, int player, int *pIds, int *pPalettes)
{
    if (fn_80047C84(pRow)) {
        fn_800480C8(number, pRow->mUnknown78, home, player, pIds, pPalettes, pRow->mUnknown08);
    } else if (pRow->mUnknown76) {
        fn_80048388(pRow, pInfo->mUnknown0C, home, player, pIds, pPalettes);
    } else {
        Colors_802CFB1C colors = lbl_802CFB1C[pRow->mUnknown64];
        int kind;

        kind = pRow->mUnknown71 ? pInfo->mUnknown09 : 0;
        fn_80048590(kind, 19, colors, number, index, flag, home, pRow->mUnknown72, player, &pIds[23], &pPalettes[23]);
        if (pInfo->mValues[10] == 0 && pInfo->mUnknown08 != 0 && home != 0) {
            fn_80048554(pInfo->mUnknown08, player, &pIds[24], &pPalettes[24]);
        } else {
            kind = pRow->mUnknown70 && pInfo->mValues[10] ? pInfo->mUnknown0A : 0;
            fn_80048590(kind, 20, colors, number, index, flag, home, 0, player, &pIds[24], &pPalettes[24]);
        }
    }
}

extern "C" void fn_80048894(int index, unsigned char *pColors, unsigned char flag)
{
    Object_8007A334 cursor;
    Query_80083E40 query;
    Rgb_800840A4 rgb;

    query.mUnknown8 = index + 1;
    query.mUnknown4 = 5;
    fn_80083E40(&cursor, &query, 0x54415453);
    fn_800840A4(&cursor, &rgb);
    fn_80083F68(&cursor);
    pColors[4] = rgb.mUnknown0;
    pColors[5] = rgb.mUnknown1;
    pColors[6] = rgb.mUnknown2;
    fn_8004795C(pColors, flag);
}

extern "C" void fn_80048950(int index, unsigned char *pColors, unsigned char flag)
{
    Object_8007A334 cursor;
    Query_80083E40 query;
    Rgb_800840A4 rgb;

    query.mUnknown8 = index + 1;
    query.mUnknown4 = 5;
    fn_80083E40(&cursor, &query, 0x54415453);
    fn_800840A4(&cursor, &rgb);
    fn_80083F68(&cursor);
    pColors[0] = rgb.mUnknown0;
    pColors[1] = rgb.mUnknown1;
}

extern "C" int fn_800489F4(unsigned int type)
{
    switch (type) {
    case 37:
        return 1;
    case 38:
        return 4;
    case 39:
        return 5;
    case 40:
        return 6;
    case 41:
        return 7;
    case 42:
        return 12;
    case 43:
        return 13;
    case 44:
        return 14;
    case 50:
        return 15;
    case 51:
        return 16;
    case 63:
        return 0;
    default:
        return 0;
    }
}

extern "C" int fn_80048ACC(int type)
{
    return lbl_802CFB74[lbl_802CFA44[type]] == 1;
}

extern "C" int fn_80048AFC(int index)
{
    int result;

    fn_8007BB84(&lbl_8030774C, 9, lbl_803078E8[index].mInfo.mValues[10], 0);
    if (fn_8007BDF8(&lbl_8030774C) == 13) {
        result = 0;
    } else {
        fn_8007BB84(&lbl_8030774C, 0, lbl_803078E8[index].mInfo.mValues[0], 0);
        result = fn_800489F4(fn_8007BDF8(&lbl_8030774C));
    }
    return result;
}

extern "C" int fn_80048B84(int index)
{
    fn_8007BB84(&lbl_8030774C, 1, lbl_803078E8[index].mInfo.mValues[1], 0);
    switch (fn_8007BDF8(&lbl_8030774C)) {
    case 45:
        return 1;
    case 46:
        return 2;
    case 47:
        return 3;
    case 48:
        return 4;
    case 49:
        return 5;
    case 63:
        return 0;
    default:
        return 0;
    }
}

extern "C" void fn_80048C40(int *pId, int *pPalette, int a, int b)
{
    int even = 0;

    *pId = b + 0x3AEF;
    if (b == 2 || b == 4 || b == 6 || b == 8) {
        even = 1;
    }
    if (a == 0) {
        *pPalette = 0x3563;
        return;
    }
    *pPalette = (a - 1) * 2 + 0x3AF8 + even;
}

extern "C" void fn_80048C9C(int index, int unused, int id, unsigned char flag)
{
    Object_8007A334 cursor;
    Block_80307980 block;
    int value;
    unsigned char *pColors = lbl_803078E8[index].mUnknown7A;
    Record_803078E8 *pRecord;

    fn_800809C4(&lbl_80307720, id, 0);
    value = fn_80080970(&lbl_80307720);
    fn_80083E40(&cursor, 0, 0x54415453);
    fn_80084034(&cursor, value, 0);
    fn_800840A4(&cursor, &pColors[20]);
    lbl_803078E8[index].mUnknown6A = fn_80084158(&cursor);
    lbl_803078E8[index].mUnknown68 = fn_80084438(&cursor);
    fn_80083F68(&cursor);
    fn_800817CC(&lbl_80307720, &lbl_803078E8[index].mInfo);
    if (fn_80054D24(47) && !fn_8017F584()) {
        fn_80047E28(index);
    }
    pRecord = &lbl_803078E8[index];
    fn_80080A9C(&lbl_80307720, pRecord->mName, 31);
    pRecord->mUnknown72 = fn_80081E3C(&lbl_80307720) + 1;
    pRecord->mUnknown73 = fn_80082280(&lbl_80307720);
    pRecord->mUnknown74 = fn_800822D4(&lbl_80307720);
    pRecord->mUnknown6C = fn_80080E70(&lbl_80307720);
    pRecord->mUnknown6E = fn_80080E98(&lbl_80307720);
    pRecord->mUnknown77 = fn_8008125C(&lbl_80307720);
    pRecord->mUnknown93 = flag;
    pRecord->mUnknown78 = fn_80080E20(&lbl_80307720);
    pRecord->mUnknown76 = fn_80080E48(&lbl_80307720);
    if (fn_80080CB0(&lbl_80307720)) {
        fn_80082138(&lbl_80307720, &block);
        fn_80049F10(index, &block);
        pRecord->mInfo.mUnknown03 = fn_80046898(&block);
    } else {
        fn_80049F10(index, 0);
    }
    lbl_803078E8[index].mUnknown70 = fn_80048AFC(index);
    lbl_803078E8[index].mUnknown75 = fn_80048B84(index);
    fn_80081C10(&lbl_80307720, &pColors[18]);
    if (!fn_80081D4C(&lbl_80307720, pColors)) {
        fn_800478DC(pColors);
        fn_8004795C(pColors, lbl_803078E8[index].mUnknown93);
    }
}

extern "C" void fn_80048EDC(void)
{
    fn_8008044C(&lbl_80307720, 0, fn_80027DF0() ? 0x54415453 : 0x454D4147);
    fn_80081CDC();
    fn_8007BA48(&lbl_8030774C);
}

extern "C" void fn_80048F34(void)
{
    fn_8007BB04(&lbl_8030774C);
    fn_80081D24();
    fn_8008056C(&lbl_80307720);
}

extern "C" void fn_80048F6C(int index, const char *pName)
{
    fn_801C3284(lbl_803078E8[index].mName, pName, 31);
}

extern "C" void fn_80048FA0(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown0D = value;
}

extern "C" void fn_80048FB8(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown0C = value;
}

extern "C" void fn_80048FD0(int index, unsigned short value)
{
    lbl_803078E8[index].mUnknown6A = value;
}

extern "C" void fn_80048FE8(int index, int unused, int id)
{
    Object_8008044C cursor;
    int i;

    fn_8008040C(&cursor, 0);
    lbl_80308368[index].mId = id;
    if (fn_800809C4(&cursor, id, 0)) {
        fn_80081440(&cursor, lbl_80308368[index].mValues);
    } else {
        for (i = 9; i >= 0; i--) {
            lbl_80308368[index].mValues[i] = 0;
        }
    }
    fn_8008056C(&cursor);
}

extern "C" void fn_800490A0(int player, int slot, int value)
{
    Object_8003DEC4 *pPlayer = fn_8003DEC4(player);

    lbl_803078E8[pPlayer->mUnknown4971].mInfo.mValues[slot] = value;
    lbl_803078E8[pPlayer->mUnknown4971].mUnknown70 = fn_80048AFC(pPlayer->mUnknown4971);
    lbl_803078E8[pPlayer->mUnknown4971].mUnknown75 = fn_80048B84(pPlayer->mUnknown4971);
}

extern "C" void fn_80049124(int player)
{
    int ids[32];
    int palettes[32];
    Row_8007BC34 row;
    Colors_802CFB1C colors;
    int id;
    int palette;
    int id2;
    int palette2;
    int clearLogo;
    Object_8003DEC4 *pPlayer;
    unsigned char key;
    unsigned char index;
    int i;
    int slot;
    Record_803078E8 *pRecord;
    unsigned char *pColors;

    pPlayer = fn_8003DEC4(player);
    clearLogo = 0;
    key = pPlayer->mUnknown4970;
    index = pPlayer->mUnknown4971;
    for (i = 0; i < 32; i++) {
        if (i != 31) {
            ids[i] = -1;
            palettes[i] = -1;
        }
    }
    ids[25] = 0x3EEC;
    ids[26] = 0x3DE1;
    ids[27] = 0x3EED;
    ids[28] = 0x3DE2;
    ids[29] = 0x3EEE;
    ids[30] = 0x3DE3;
    for (i = 0; lbl_802CF382[i].mKey != 0xFFFF; i++) {
        fn_8015FFC8(key, lbl_802CF382[i].mKey, lbl_802CF382[i].mValue);
    }
    pColors = lbl_803078E8[index].mUnknown7A;
    fn_800478DC(pColors);
    fn_8004795C(pColors, lbl_803078E8[index].mUnknown93);
    for (slot = 0; slot <= 13; slot++) {
        fn_8007BB84(&lbl_8030774C, fn_8007BF14(slot), lbl_803078E8[index].mInfo.mValues[slot], 0);
        fn_8007BC34(&lbl_8030774C, &row);
        fn_800479B0(&row, &lbl_803078E8[index], ids, palettes, slot);
        fn_80047FA4(&row, &lbl_803078E8[index].mInfo, key, slot);
        if (slot == 10) {
            if (row.mUnknown64 == 13) {
                lbl_803078E8[index].mUnknown95 = 1;
            } else {
                lbl_803078E8[index].mUnknown95 = 0;
            }
            fn_80048704(&row, &lbl_803078E8[index].mInfo, lbl_803078E8[index].mUnknown77,
                        lbl_803078E8[index].mUnknown6A - 1, lbl_803078E8[index].mUnknown68,
                        lbl_803078E8[index].mUnknown93, key, ids, palettes);
            if (row.mUnknown76) {
                fn_80048894(lbl_803078E8[index].mInfo.mUnknown0C, lbl_803078E8[index].mUnknown7A,
                            lbl_803078E8[index].mUnknown93);
            }
            clearLogo = fn_80048ACC(row.mUnknown64) == 0;
        } else if (slot == 0) {
            unsigned char type;

            colors.mUnknown1 = 0;
            colors.mUnknown0 = 0;
            colors.mUnknown3 = 255;
            colors.mUnknown2 = 0;
            type = lbl_803078E8[index].mInfo.mUnknown0B;
            if (row.mUnknown76) {
                fn_80048470(&row, lbl_803078E8[index].mInfo.mUnknown0D, key, ids, palettes);
                fn_80048950(lbl_803078E8[index].mInfo.mUnknown0D, lbl_803078E8[index].mUnknown7A, lbl_803078E8[index].mUnknown93);
            } else {
                if (fn_801C302C(row.mName, "SKULLCAP_BLACK_L", 16) == 0) {
                    ids[2] = 0x3216;
                    palettes[2] = -1;
                    fn_8015FFC8(key, 25, colors.mUnknown1);
                } else if (fn_801C302C(row.mName, "SKULLCAP_WHITE_L", 16) == 0) {
                    ids[2] = 0x3215;
                    palettes[2] = -1;
                    fn_8015FFC8(key, 25, colors.mUnknown1);
                } else {
                    fn_80048590(type, 25, colors, lbl_803078E8[index].mUnknown77, lbl_803078E8[index].mUnknown6A - 1,
                                lbl_803078E8[index].mUnknown68, lbl_803078E8[index].mUnknown93, 0, key, &ids[2], &palettes[2]);
                }
                fn_8015FFC8(key, 26, 255);
            }
        }
    }
    if (clearLogo) {
        ids[10] = -1;
        palettes[10] = -1;
    }
    fn_80047CA4(ids, &lbl_803078E8[index]);
    for (i = 0; i <= 31; i++) {
        if (i != 31) {
            fn_80160E94(index, i, ids[i], palettes[i], 0);
        }
    }
    fn_801610B0(index, lbl_803078E8[index].mUnknown7A);
    if (ids[4] == -1) {
        fn_8016139C(lbl_803078E8[index].mUnknown6E, &id, &palette);
        fn_80160E94(index, 4, id, palette, 0);
    }
    pRecord = &lbl_803078E8[index];
    if (pRecord->mUnknown95) {
        fn_8015FFC8(key, 0, 255);
        fn_8015FFC8(key, 27, 255);
        fn_8015FFC8(key, 25, 255);
        fn_8015FFC8(key, 26, 255);
    }
    if (pRecord->mUnknown70 != 15 && pRecord->mUnknown70 != 16 && !pRecord->mUnknown95) {
        pRecord->mUnknown94 = 1;
    } else {
        lbl_803078E8[index].mUnknown94 = 0;
    }
    fn_8015FFC8(key, 29, 255);
    fn_8015FFC8(key, 30, 255);
    if (lbl_803078E8[index].mInfo.mValues[12]) {
        fn_8015FFC8(key, 29, 0);
        if (lbl_803078E8[index].mInfo.mValues[13]) {
            fn_8015FFC8(key, 30, 0);
        }
        fn_80048C40(&id2, &palette2, lbl_803078E8[index].mInfo.mValues[13], lbl_803078E8[index].mInfo.mValues[12]);
        fn_80160E94(index, 7, id2, -1, 0);
        fn_80160E94(index, 8, palette2, -1, 0);
    }
    fn_801C3284(pPlayer->mUnknown4184, lbl_803078E8[index].mName, 31);
    fn_801A4AD4(pPlayer);
}

extern "C" void fn_800496A0(unsigned int mode, int index, int unused, int id)
{
    int flag = 1;

    if (fn_80027DF0() && fn_8001E4F4() && fn_8005FC7C()) {
        Object_8007A334 cursor;

        fn_8007A334(&cursor, 0x59414C50, 0x44494750, 0, 0, 0x54415453);
        if (fn_800809C4((Object_8008044C *)&cursor, id, 0)) {
            flag = fn_80081FD4((Object_8008044C *)&cursor, 1) == 0;
        }
        fn_8007A3C4(&cursor);
    } else if ((fn_80027DF0() && (fn_801835A0() || fn_800624B0())) || !fn_801486A0()) {
        flag = 1;
    } else if (fn_8007CB6C(2) == 0) {
        flag = mode <= 6;
    } else {
        flag = mode > 6;
    }
    fn_80048C9C(index, unused, id, flag);
}

extern "C" void fn_800497F4(int unused, int id, unsigned short *pValues)
{
    unsigned int i;
    int j;

    for (i = 0; i <= 13; i++) {
        if (lbl_80308368[i].mId == id) {
            break;
        }
    }
    if (i <= 13) {
        for (j = 0; j < 10; j++) {
            pValues[j] = lbl_80308368[i].mValues[j];
        }
    } else {
        for (j = 0; j < 10; j++) {
            *pValues++ = 0;
        }
    }
}

extern "C" int fn_80049888(int index)
{
    int kind;
    unsigned char style = lbl_803078E8[index].mInfo.mUnknown02;
    unsigned short type = lbl_803078E8[index].mUnknown70;

    if (type != 0 && type != 16 && type != 15) {
        switch (type) {
        case 1:
            switch (style) {
            case 0:
                kind = 1;
                break;
            case 1:
                kind = 2;
                break;
            case 2:
                kind = 3;
                break;
            default:
                kind = lbl_803078E8[index].mUnknown70;
                break;
            }
            break;
        case 7:
            switch (style) {
            case 0:
                kind = 7;
                break;
            case 2:
                kind = 8;
                break;
            case 3:
                kind = 9;
                break;
            case 5:
                kind = 10;
                break;
            case 1:
                kind = 11;
                break;
            default:
                kind = lbl_803078E8[index].mUnknown70;
                break;
            }
            break;
        default:
            kind = lbl_803078E8[index].mUnknown70;
            break;
        }
        return (kind - 1) * 14 + lbl_803078E8[index].mUnknown6C * 2 + 1;
    }
    return 3;
}

extern "C" int fn_800499A8(int index)
{
    Record_803078E8 *pRecord = &lbl_803078E8[index];

    if (pRecord->mUnknown75 != 0) {
        return (pRecord->mUnknown75 - 1) * 8 + pRecord->mInfo.mUnknown03 * 2 + 1;
    }
    return 1;
}

extern "C" int fn_800499E8(int index)
{
    Row_8007BC34 row;
    unsigned int a = lbl_803078E8[index].mInfo.mValues[12];
    unsigned int b = lbl_803078E8[index].mInfo.mValues[13];
    int result;

    if (a == 0) {
        result = 0x151;
    } else {
        fn_8007BB84(&lbl_8030774C, 9, lbl_803078E8[index].mInfo.mValues[10], 0);
        fn_8007BC34(&lbl_8030774C, &row);
        result = (a - 1) / 2;
        result = result * 13;
        result = result + b;
        result = result * 3 + lbl_802CFB74[lbl_802CFA44[row.mUnknown64]];
        result = result * 4 + lbl_803078E8[index].mUnknown78;
        result = result * 2;
        result = result + 1;
    }
    return result;
}

extern "C" unsigned short fn_80049AB8(int index)
{
    return lbl_803078E8[index].mUnknown6E;
}

extern "C" void fn_80049AD0(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown02 = value;
}

extern "C" void fn_80049AE8(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown0B = value;
}

extern "C" void fn_80049B00(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown09 = value;
}

extern "C" void fn_80049B18(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown0A = value;
}

extern "C" void fn_80049B30(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown72 = value;
}

extern "C" void fn_80049B48(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown73 = value;
}

extern "C" void fn_80049B60(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown74 = value;
}

extern "C" void fn_80049B78(int index, unsigned short value)
{
    lbl_803078E8[index].mUnknown6C = value;
}

extern "C" void fn_80049B90(int index, unsigned short value)
{
    lbl_803078E8[index].mUnknown6E = value;
}

extern "C" void fn_80049BA8(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown78 = value;
}

extern "C" unsigned char fn_80049BC0(int index)
{
    return lbl_803078E8[index].mUnknown78;
}

extern "C" void fn_80049BD8(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown03 = value;
}

extern "C" void fn_80049BF0(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown77 = value;
}

extern "C" unsigned short fn_80049C08(int index)
{
    return lbl_803078E8[index].mUnknown6C;
}

extern "C" void fn_80049C20(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown76 = value;
}

extern "C" unsigned char fn_80049C38(int index)
{
    return lbl_803078E8[index].mUnknown76;
}

extern "C" void fn_80049C50(int index, int player)
{
    Colors_802CFB1C colors;
    int dummy;

    colors.mUnknown1 = 0;
    colors.mUnknown0 = 0;
    colors.mUnknown2 = 0;
    colors.mUnknown3 = 255;
    fn_80048590(lbl_803078E8[index].mInfo.mUnknown0B, 25, colors, lbl_803078E8[index].mUnknown77,
                lbl_803078E8[index].mUnknown6A - 1, lbl_803078E8[index].mUnknown68,
                lbl_803078E8[index].mUnknown93, 0, player, &dummy, &dummy);
}

extern "C" int fn_80049CD8(int index)
{
    int result = 1;

    if (lbl_803078E8[index].mUnknown70 == 0) {
        result = 0;
    }
    return result;
}

extern "C" unsigned char fn_80049D04(int index)
{
    return lbl_803078E8[index].mUnknown94;
}

extern "C" unsigned char fn_80049D1C(int index)
{
    return lbl_803078E8[index].mUnknown95;
}

extern "C" void fn_80049D34(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown7A[18] = value + 0x80;
}

extern "C" void fn_80049D50(int index, unsigned char value)
{
    lbl_803078E8[index].mUnknown7A[19] = value + 0x80;
}

extern "C" void fn_80049D6C(int index, unsigned int which, unsigned char value)
{
    switch (which) {
    case 1:
        lbl_803078E8[index].mInfo.mUnknown05 = value;
        break;
    case 0:
        lbl_803078E8[index].mInfo.mUnknown04 = value;
        break;
    case 2:
        lbl_803078E8[index].mInfo.mUnknown08 = value;
        break;
    }
}

extern "C" void fn_80049DD0(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown00 = value;
}

extern "C" void fn_80049DE8(int index, unsigned char value)
{
    lbl_803078E8[index].mInfo.mUnknown01 = value;
}

extern "C" void fn_80049E00(int index, int a, int b)
{
    fn_80049C08(index);
    fn_8015F6E8(a, fn_80049AB8(index), fn_80049C08(index), fn_80049CD8(index), b);
}

extern "C" void fn_80049E6C(void)
{
    unsigned int count = fn_8003DEB4();
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_8015FFC8(fn_8003DEC4(i)->mUnknown4970, 28, 255);
    }
}

extern "C" unsigned char fn_80049EC8(int index)
{
    return lbl_803078E8[index].mUnknown72;
}

extern "C" unsigned char fn_80049EE0(int index)
{
    return lbl_803078E8[index].mUnknown73;
}

extern "C" unsigned char fn_80049EF8(int index)
{
    return lbl_803078E8[index].mUnknown74;
}

extern "C" void fn_80049F10(int index, Block_80307980 *pBlock)
{
    if (pBlock) {
        lbl_803078E8[index].mBlock = *pBlock;
    } else {
        fn_801C1F94(&lbl_803078E8[index].mBlock, 0, sizeof(Block_80307980));
    }
}

extern "C" void fn_80049FC8(int index, Block_80307980 *pBlock)
{
    *pBlock = lbl_803078E8[index].mBlock;
}

extern "C" void fn_8004A040(Object_8003DEC4 *pPlayer, Init_8004A040 *pInit)
{
    fn_801C1F94(pPlayer, 0x19F0, 0);
    fn_80042610(pPlayer, pInit->mUnknown04, pInit->mUnknown08, pInit->mUnknown10, pInit->mUnknown14);
    pPlayer->mUnknown4956 = pInit->mUnknown18;
    fn_80146094(pPlayer->mUnknown5188);
    fn_801A3588(pPlayer, pInit);
}

extern "C" void fn_8004A0AC(Object_8003DEC4 *pPlayer)
{
    fn_801A3F48(pPlayer);
    fn_800428A8(pPlayer);
}

extern "C" void fn_8004A0E0(int a, int b)
{
    lbl_803EA4CA = 1;
    fn_801A34B0(0, 0, a, b);
}

extern "C" void fn_8004A118(void)
{
    lbl_803EA4CA = 0;
    fn_801A3520();
}

extern "C" void fn_8004A140(int owner, int type, int count)
{
    fn_801DCF0C(type, 0x19F0, count, fn_8004A040, fn_8004A0AC);
    if (owner) {
        fn_801DD0C8(owner, type, 0, fn_8004A1A8);
    }
}

extern "C" int fn_8004A1A8(Object_8003DEC4 *pPlayer, int unused)
{
    Item_800476DC *pItem = pPlayer->mUnknown988;

    if (pItem && pItem->mUnknown1C) {
        fn_800476DC(pItem, pPlayer->mUnknown4);
    }
    fn_801A3C40(pPlayer);
    return 0;
}

extern "C" void fn_8004A1FC(int type)
{
    fn_80228E18();
    fn_801DCF8C(type);
}

extern "C" void fn_8004A230(unsigned char value)
{
    lbl_803EA4CA = value;
}

extern "C" unsigned char fn_8004A238(void)
{
    return lbl_803EA4CA;
}
