#include "game/Record_80082B18.h"
#include "game/Block_80307980.h"
#include "game/Class_8018FD64.h"
#include "game/Class_802938C0.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Row_8007BC34.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"


extern "C" {
int fn_8007A43C(Object_8007A334 *pObject);
void fn_8007BA88(Object_8007A334 *pCursor, int value);
void fn_8007BB04(Object_8007A334 *pCursor);
int fn_8007BBFC(Object_8007A334 *pCursor, int key, int *pResult);
int fn_8007FC70(int a, int b, int mode, int c);
void fn_80080138(int a, int b, int mode);
int fn_8008058C(int *pId, int *pPos, int *pValue, int a, int b, int c, int mode);
void fn_80080874(int which);
int fn_800808F8(Object_8008044C *pObject);
void fn_800731D0(int a);
int fn_80186F7C(unsigned char index);
int fn_801C1F54(int c);
unsigned int fn_80229CFC(int category, int *pValues, int a);
int fn_8022C8F0(unsigned int low, unsigned int high);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_8022F358(int index);
int fn_8022F3D4(int handle);

int fn_80082280(Object_8008044C *pObject);
int fn_8008257C(int count, unsigned int *pOut);
int fn_80082864(void);

extern int lbl_802D6850[18];
extern int lbl_802D69F0[];
extern int lbl_802D6AD8[];
extern const int lbl_80293968[];
extern QueryCursor lbl_8030BC88;
extern QueryCursor lbl_8030BC98;

static Object_8007A334 lbl_8030BC2C;

static unsigned char lbl_803EA7D8 = 0;
static int lbl_803EA7DC = 0;
static int lbl_803EA7E0 = 0;

void fn_80081CDC(void)
{
    fn_8007A334(&lbl_8030BC2C, 0x4C434750, 0x44494750, 0, 0, 0x54415453);
}

void fn_80081D24(void)
{
    fn_8007A3C4(&lbl_8030BC2C);
}

int fn_80081D4C(Object_8008044C *pObject, unsigned char *p)
{
    int found = 0;

    if (fn_8007A7F4(&lbl_8030BC2C, 0x44494750, fn_800808F8(pObject), 0, 0)) {
        ColumnValue_802D6424 columns[19];
        int i;

        found = 1;
        for (i = 0; i < 18; i++) {
            columns[i].Set(0x4C434750, lbl_802D6850[i], 0);
        }
        columns[18].SetEnd();
        pObject->Read(columns);
        for (i = 0; i < 18; i++) {
            p[i] = columns[i].mValue;
        }
    }
    return found;
}

int fn_80081E3C(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x494B5350);
}

void fn_80081E64(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007ADD4(pObject, 0x414E4650, pBuffer, size);
}

void fn_80081E98(Object_8008044C *pObject, char *pBuffer, int size)
{
    fn_8007ADD4(pObject, 0x414E4C50, pBuffer, size);
}

unsigned int fn_80081ECC(int category, int *pValues)
{
    int values[10];

    values[0] = pValues[0];
    values[1] = pValues[4];
    values[2] = pValues[1];
    values[3] = pValues[3];
    values[4] = pValues[2];
    values[5] = pValues[5];
    values[6] = pValues[6];
    values[7] = pValues[7];
    values[8] = pValues[8];
    values[9] = pValues[9];
    return fn_80229CFC(category, values, 0);
}

void fn_80081F50(Object_8008044C *pObject, unsigned char side, int a)
{
    unsigned int flags = fn_8007A98C(pObject, 0x47494C50);

    if (a) {
        if (side == 0) {
            flags |= 1;
        } else {
            flags |= 2;
        }
    } else {
        if (side == 0) {
            flags &= ~1;
        } else {
            flags &= ~2;
        }
    }
    fn_8007ABA4(pObject, 0x47494C50, flags);
}

int fn_80081FD4(Object_8008044C *pObject, int a)
{
    if (a != 0) {
        return (fn_8007A98C(pObject, 0x47494C50) >> 1) & 1;
    }
    return fn_8007A98C(pObject, 0x47494C50) & 1;
}

int fn_8008201C(Object_8008044C *pObject, int a, int b, int *pResult, int *pPosition)
{
    Object_8007A334 *pCursor = (Object_8007A334 *)pObject;
    int first;
    int second;
    int row = fn_8007A43C(pCursor);
    int position = -1;
    int found1 = fn_8007A7F4(pCursor, 0x47494C50, 3, a, &first);
    int found2;
    int found;

    fn_8007A600(pCursor, row);
    found2 = fn_8007A7F4(pCursor, 0x47494C50, b == 0 ? 1 : 2, a, &second);
    if (found1) {
        if (found2) {
            position = second;
            if (position > first) {
                position = first;
            }
        } else {
            position = first;
        }
    } else if (found2) {
        position = second;
    }
    found = 0;
    if (found1 || found2) {
        found = 1;
    }
    if (found) {
        fn_8007A600(pCursor, position);
        if (pResult) {
            *pResult = fn_800808F8(pObject);
        }
        if (pPosition) {
            *pPosition = position;
        }
    }
    return found;
}

void fn_80082138(Object_8008044C *pObject, Block_80307980 *pBlock)
{
    Class_802938C0 cursor;

    cursor.fn_80190098();
    cursor.fn_801900D4(fn_80082280(pObject), 0);
    pBlock->mUnknown0[0] = cursor.fn_801901A4();
    pBlock->mUnknown0[1] = fn_8007A98C(pObject, 0x57424650);
    pBlock->mUnknown0[2] = fn_8007A98C(pObject, 0x41454650) + 8;
    pBlock->mUnknown0[3] = fn_8007A98C(pObject, 0x54484C50);
    pBlock->mUnknown0[4] = fn_8007A98C(pObject, 0x4F4D4650) + 0x15;
    pBlock->mUnknown0[5] = fn_8007A98C(pObject, 0x504C4650) + 0x1E;
    pBlock->mUnknown0[6] = fn_8007A98C(pObject, 0x434A4650) + 0x22;
    pBlock->mUnknown0[7] = fn_8007A98C(pObject, 0x59454650) + 0x30;
    pBlock->mUnknown0[8] = fn_8007A98C(pObject, 0x4F4E4650) + 0x48;
    pBlock->mUnknown0[9] = fn_8007A98C(pObject, 0x54425950);
}

int fn_80082280(Object_8008044C *pObject)
{
    return fn_8007A98C(pObject, 0x48464650);
}

void fn_800822A8(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x48464650, value);
}

int fn_800822D4(Object_8008044C *pObject)
{
    int value = fn_8007A98C(pObject, 0x42454650);

    if (value > 2) {
        value = 0;
    }
    return value;
}

void fn_80082308(Object_8008044C *pObject, int value)
{
    fn_8007ABA4(pObject, 0x42454650, value);
}

void fn_80082334(Object_8008044C *pObject, Block_80307980 *pBlock)
{
    fn_8007ABA4(pObject, 0x57424650, pBlock->mUnknown0[1]);
    fn_8007ABA4(pObject, 0x41454650, pBlock->mUnknown0[2] - 8);
    fn_8007ABA4(pObject, 0x54484C50, pBlock->mUnknown0[3]);
    fn_8007ABA4(pObject, 0x4F4D4650, pBlock->mUnknown0[4] - 0x15);
    fn_8007ABA4(pObject, 0x504C4650, pBlock->mUnknown0[5] - 0x1E);
    fn_8007ABA4(pObject, 0x434A4650, pBlock->mUnknown0[6] - 0x22);
    fn_8007ABA4(pObject, 0x59454650, pBlock->mUnknown0[7] - 0x30);
    fn_8007ABA4(pObject, 0x4F4E4650, pBlock->mUnknown0[8] - 0x48);
}

int fn_80082414(int index)
{
    int result;

    switch (index) {
    case 0:
        result = fn_8008058C(0, 0, 0, -1, -1, -1, 0);
        fn_80080874(0);
        return result;
    case 1: {
        int count = fn_80082864();
        unsigned int teams = 0;

        return fn_8008257C(count, &teams);
    }
    case 2:
        return 42;
    case 3: {
        Object_8008044C cursor;
        Desc_8008044C desc;

        desc.mUnknown4 = 3;
        desc.mUnknown8 = 1;
        desc.mUnknown0 = 0;
        fn_8008044C(&cursor, &desc, 0x54415453);
        result = fn_8007A410((Object_8007A334 *)&cursor);
        fn_8008056C(&cursor);
        return result;
    }
    }
    return -1;
}

void fn_80082534(int a, int b)
{
    fn_80080138(a, b, 0);
}

void fn_80082558(int a, int b)
{
    fn_80080138(a, b, 1);
}

}

#include "game/Class_8018FD64Inline.h"

extern "C" {

int fn_8008257C(int count, unsigned int *pOut)
{
    int result;
    unsigned int pad;
    int i;

    *pOut = 0;
    result = count - 10;
    for (pad = 0; pad <= 1; pad++) {
        int db = fn_80186F7C(pad);

        if (db != -1) {
            int handle = fn_8022F3D4(fn_8022F358((signed char)db));
            Class_8018FD64 cursor;

            cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
            *pOut |= cursor.fn_8018FF9C(0x504C5555);
        }
    }
    for (i = 0; i < 10; i++) {
        if (*pOut & (1 << i)) {
            result++;
        }
    }
    return result;
}

void fn_80082688(int db)
{
    int mask = 0;
    int i;

    for (i = 0; i < 10; i++) {
        mask |= 1 << i;
    }
    {
        int handle = fn_8022F3D4(fn_8022F358(db));
        Class_8018FD64 cursor;

        cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
        cursor.fn_8019002C(0x504C5555, mask);
    }
}

void fn_8008274C(int db)
{
    int mask = 0;
    int handle = fn_8022F3D4(fn_8022F358(db));
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
    cursor.fn_8019002C(0x504C5555, mask);
}

int fn_800827EC(int id, unsigned int value)
{
    int i;
    int result = 1;

    for (i = 0; lbl_802D6AD8[i] != id && lbl_802D6AD8[i] != 0x7FFF; i++) {
    }
    if (lbl_802D6AD8[i] != 0x7FFF) {
        if (i > 9 || (value & (1 << i))) {
            result = 0;
        }
    }
    return result;
}

int fn_80082864(void)
{
    Object_8008044C cursor;
    Desc_8008044C desc;
    int count;

    desc.mUnknown4 = 1;
    desc.mUnknown8 = 0x22;
    desc.mUnknown0 = 0;
    fn_8008044C(&cursor, &desc, 0x54415453);
    count = fn_8007A410((Object_8007A334 *)&cursor);
    fn_8008056C(&cursor);
    return count;
}

void fn_800828FC(void)
{
    QueryResult result;

    fn_800731D0(0);
    fn_8022EF8C(0, 0x4D4E4653);
    fn_800731D0(0);
    fn_8022EF8C(0, 0x4D4E4C53);
    fn_800731D0(0);
    lbl_8030BC88.mUnknown0 = 0;
    lbl_8030BC88.mUnknown4 = 0;
    lbl_8030BC88.mUnknown8 = -1;
    lbl_8030BC88.mUnknown12 = 0;
    fn_801FCE10(&result, "declare \x8a cursor for select 'ANFP' from 'MNFS'\n", &lbl_8030BC88);
    lbl_803EA7DC = result.mUnknown0;
    lbl_8030BC98.mUnknown0 = 0;
    lbl_8030BC98.mUnknown4 = 0;
    lbl_8030BC98.mUnknown8 = -1;
    lbl_8030BC98.mUnknown12 = 0;
    fn_801FCE10(&result, "declare \x8a cursor for select 'ANLP' from 'MNLS'\n", &lbl_8030BC98);
    lbl_803EA7E0 = result.mUnknown0;
    lbl_803EA7D8 = 1;
}

void fn_800829D8(void)
{
    if (lbl_8030BC98.mUnknown0) {
        fn_801FCFA0(&lbl_8030BC98);
    }
    if (lbl_8030BC88.mUnknown0) {
        fn_801FCFA0(&lbl_8030BC88);
    }
    fn_800731D0(0);
    fn_8022EFBC(0, 0x4D4E4653);
    fn_800731D0(0);
    fn_8022EFBC(0, 0x4D4E4C53);
    fn_800731D0(0);
    lbl_803EA7D8 = 0;
}

int fn_80082A64(int a, int b)
{
    return fn_8007FC70(a, fn_8022C8F0(0, 14), 0, b);
}

int fn_80082AB0(int a, int b, int c)
{
    return fn_8007FC70(b, a, 0, c);
}

int fn_80082AE4(int a, int b)
{
    return fn_8007FC70(b, a, 1, -1);
}

void fn_80082B18(Record_80082B18 *pRecord)
{
    pRecord->mUnknown00 = 0x7FFF;
    pRecord->mUnknown04 = 0;
    pRecord->mUnknown08 = 0;
    pRecord->mUnknown0C = 0;
    pRecord->mUnknown10 = 0x1F;
    pRecord->mUnknown14 = 0x1F;
    pRecord->mUnknown18 = 0x7F;
    pRecord->mUnknown1C = 0x7F;
    pRecord->mUnknown20 = 0x3F;
    pRecord->mUnknown24 = 0;
    pRecord->mUnknown2C = 0;
    pRecord->mUnknown68 = 0;
    pRecord->mUnknown30 = 0;
    pRecord->mUnknown34 = 0;
    pRecord->mUnknown38 = 0xF;
    pRecord->mUnknown3C = 0;
    pRecord->mUnknown40 = 0;
    pRecord->mUnknown44 = 0;
    pRecord->mUnknown48 = 0;
    pRecord->mUnknown4C = 0;
    pRecord->mUnknown50 = 0;
    pRecord->mUnknown54 = 0;
    pRecord->mUnknown58 = 0;
    pRecord->mUnknown5C = 7;
    pRecord->mUnknown60 = 0;
    pRecord->mUnknown64 = 0;
    pRecord->mUnknownC4 = 0x7F;
    pRecord->mUnknownC8 = 0x7F;
    pRecord->mUnknownCC = 0x7F;
    pRecord->mUnknownD0 = 0x7F;
    pRecord->mUnknownD4 = 0x7F;
    pRecord->mUnknownD8 = 0x7F;
    pRecord->mUnknownDC = 0x7F;
    pRecord->mUnknownE0 = 0x7F;
    pRecord->mUnknown10C = 0x55;
    pRecord->mUnknown110 = 0x1A0;
    pRecord->mUnknown114 = 3;
    pRecord->mUnknown9C = 0x7F;
    pRecord->mUnknownA4 = 7;
    pRecord->mUnknownE4 = 0x7F;
    pRecord->mUnknownE8 = 0x7F;
    pRecord->mUnknownEC = 0x7F;
    pRecord->mUnknownF0 = 0x7F;
    pRecord->mUnknownF4 = 0x7F;
    pRecord->mUnknownF8 = 0x7F;
    pRecord->mUnknownFC = 0x7F;
    pRecord->mUnknown100 = 0x7F;
    pRecord->mUnknown104 = 0x7F;
    pRecord->mUnknown108 = 0x7F;
    pRecord->mUnknown118 = 0;
    pRecord->mUnknown11C = 0;
    pRecord->mUnknown6C = 0x7F;
    pRecord->mUnknown70 = 0x7F;
    pRecord->mUnknown74 = 0x7F;
    pRecord->mUnknown78 = 0x7F;
    pRecord->mUnknown7C = 0x7F;
    pRecord->mUnknown80 = 0x7F;
    pRecord->mUnknown84 = 0x7F;
    pRecord->mUnknown88 = 0x7F;
    pRecord->mUnknown8C = 0x7F;
    pRecord->mUnknown90 = 0x7F;
    pRecord->mUnknown94 = 0x7F;
    pRecord->mUnknown98 = 0x7F;
    pRecord->mUnknownA0 = 0;
    pRecord->mUnknownA8 = 0;
    pRecord->mUnknownAC = 0;
    pRecord->mUnknownB0 = 0;
    pRecord->mUnknownB4 = 0;
    pRecord->mUnknown28 = 0xF;
    pRecord->mUnknownC0 = 0;
    pRecord->mUnknownB8 = 0;
    pRecord->mUnknownBC = 0;
}

/* Fetches a randomly chosen first and last name through the two name cursors
   opened by fn_800828FC, and stores the upper-case form of the last name. */
void fn_80082C64(Record_80082B18 *pRecord)
{
    char *pLast = pRecord->mUnknown08;
    char *pFirst = pRecord->mUnknown04;
    char *pUpper = pRecord->mUnknown0C;
    unsigned int i;

    lbl_8030BC88.mUnknown4 = fn_802372EC(0, lbl_803EA7DC);
    fn_801FCE10(0, "fetch from \x8a 'ANFP' into \x88\n", &lbl_8030BC88, pFirst);
    lbl_8030BC98.mUnknown4 = fn_802372EC(0, lbl_803EA7E0);
    fn_801FCE10(0, "fetch from \x8a 'ANLP' into \x88\n", &lbl_8030BC98, pLast);
    for (i = 0; i < 15; i++) {
        if (pLast) {
            pUpper[i] = fn_801C1F54(pLast[i]);
        }
    }
}

void fn_80082D30(Record_80082B18 *pRecord)
{
    QueryCursor cursor;
    QueryResult result;
    unsigned int skin = fn_802372EC(0, 12);

    pRecord->mUnknown28 = skin;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use 'TATS' declare \x8a cursor for select * from 'ECAF' where 'IKSP' = \x85\n", &cursor, skin);
    cursor.mUnknown4 = fn_802372EC(0, result.mUnknown0);
    fn_801FCE10(0,
                "fetch from \x8a 'CFRP' into \x82 and 'THLP' into \x82 and 'PTEP' into \x82 and 'XELP' into \x82 "
                "and 'HFFP' into \x82 and 'BEFP' into \x82 and 'AEFP' into \x82 and 'OMFP' into \x82 and 'PLFP' "
                "into \x82 and 'CJFP' into \x82 and 'YEFP' into \x82 and 'ONFP' into \x82 and 'RAHP' into \x82 "
                "and '1AHP' into \x82 and 'CHFP' into \x82 and 'PXSP' into \x82\n",
                &cursor, &pRecord->mUnknown2C, &pRecord->mUnknown38, &pRecord->mUnknown34, &pRecord->mUnknown30,
                &pRecord->mUnknown3C, &pRecord->mUnknown40, &pRecord->mUnknown44, &pRecord->mUnknown48,
                &pRecord->mUnknown4C, &pRecord->mUnknown50, &pRecord->mUnknown54, &pRecord->mUnknown58,
                &pRecord->mUnknown5C, &pRecord->mUnknown60, &pRecord->mUnknown64, &pRecord->mUnknown68);
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
}

void fn_80082E48(Record_80082B18 *pRecord)
{
    QueryCursor cursor;
    QueryResult result;
    unsigned short count;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result,
                "use 'TATS' declare \x8a cursor for select * from 'YALP' inner join 'MAET' on 'YALP'.'DIGT' = "
                "'MAET'.'DIGT' where 'YALP'.'OPBP' = \x85 and 'MAET'.'PYTT' = \x82\n",
                &cursor, pRecord->mUnknown14, 0);
    count = result.mUnknown0;
    cursor.mUnknown4 = fn_802372EC(0, count);
    fn_801FCE10(0,
                "fetch from \x8a 'TAHP' into \x82 and 'ROHP' into \x82 and 'RWEP' into \x82 and 'APSP' into \x82 "
                "and 'TRSP' into \x82 and 'TNPP' into \x82 and 'RAUP' into \x82 and 'LULP' into \x82 and 'WBEP' "
                "into \x82 and 'DNHP' into \x82 and 'DHRP' into \x82 and 'TRWP' into \x82 and 'LWLP' into \x82 "
                "and 'COSP' into \x82 and 'OHSP' into \x82 and 'TARP' into \x82 and 'OTAP' into \x82 and 'TLRP' "
                "into \x82 and 'OTLP' into \x82 and 'DBTP' into \x82 and 'DFTP' into \x82 and 'CDHP' into \x82 "
                "and 'RVOP' into \x82 and 'EGAP' into \x82\n",
                &cursor, &pRecord->mUnknown6C, &pRecord->mUnknown70, &pRecord->mUnknown74, &pRecord->mUnknown78,
                &pRecord->mUnknown7C, &pRecord->mUnknown80, &pRecord->mUnknown84, &pRecord->mUnknown88,
                &pRecord->mUnknown8C, &pRecord->mUnknown90, &pRecord->mUnknown94, &pRecord->mUnknown98,
                &pRecord->mUnknown9C, &pRecord->mUnknownA0, &pRecord->mUnknownA4, &pRecord->mUnknownA8,
                &pRecord->mUnknownAC, &pRecord->mUnknownB0, &pRecord->mUnknownB4, &pRecord->mUnknownB8,
                &pRecord->mUnknownBC, &pRecord->mUnknownC0, &pRecord->mUnknown1C, &pRecord->mUnknown20);
    cursor.mUnknown4 = fn_802372EC(0, count);
    fn_801FCE10(0,
                "fetch from \x8a 'DPSP' into \x82 and 'IGAP' into \x82 and 'MUJP' into \x82 and 'HTCP' into \x82 "
                "and 'KTBP' into \x82 and 'KATP' into \x82 and 'SSPP' into \x82 and 'KLBP' into \x82 and 'VOCP' "
                "into \x82 and 'TFDP' into \x82 and 'PMIP' into \x82 and 'NSPP' into \x82 and 'LECP' into \x82 "
                "and 'LCUP' into \x82 and '1TGS' into \x82 and '2TGS' into \x82 and '3TGS' into \x82 and '4TGS' "
                "into \x82 and 'TGHP' into \x82 and 'TGWP' into \x82 and 'NAHP' into \x82 and 'TBYP' into \x82 "
                "and 'TLFP' into \x82\n",
                &cursor, &pRecord->mUnknownC4, &pRecord->mUnknownC8, &pRecord->mUnknownCC, &pRecord->mUnknownD0,
                &pRecord->mUnknownD4, &pRecord->mUnknownD8, &pRecord->mUnknownDC, &pRecord->mUnknownE0,
                &pRecord->mUnknownE4, &pRecord->mUnknownE8, &pRecord->mUnknownEC, &pRecord->mUnknownF0,
                &pRecord->mUnknownF4, &pRecord->mUnknownF8, &pRecord->mUnknownFC, &pRecord->mUnknown100,
                &pRecord->mUnknown104, &pRecord->mUnknown108, &pRecord->mUnknown10C, &pRecord->mUnknown110,
                &pRecord->mUnknown114, &pRecord->mUnknown118, &pRecord->mUnknown11C);
    pRecord->mUnknown18 = fn_802372EC(0, 100);
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
}

void fn_80083070(Record_80082B18 *pRecord)
{
    int dftp;
    int dbtp;
    int cdhp;

    pRecord->mUnknown10 = lbl_802D69F0[pRecord->mUnknown14];
    pRecord->mUnknownA8 = 0;
    pRecord->mUnknownAC = 0;
    pRecord->mUnknownB0 = 0;
    pRecord->mUnknownB4 = 0;
    Object_8007A334 rows;
    fn_8007BA88(&rows, 9);
    fn_8007BBFC(&rows, pRecord->mUnknown7C, 0);
    if (fn_8007BDF8(&rows) == 5) {
        pRecord->mUnknown7C = 0x53;
        pRecord->mUnknown78 = 1;
        pRecord->mUnknownB8 = 0;
        pRecord->mUnknownBC = 0;
    }
    fn_8007BB04(&rows);
    dftp = pRecord->mUnknownBC;
    dbtp = pRecord->mUnknownB8;
    cdhp = pRecord->mUnknownC0;
    if (dftp >= 2 && dftp <= 4) {
        pRecord->mUnknownBC = 5;
    }
    if (dbtp >= 2 && dbtp <= 4) {
        pRecord->mUnknownB8 = 5;
    }
    if (cdhp >= 2 && cdhp <= 4) {
        pRecord->mUnknownC0 = 5;
    }
    pRecord->mUnknown11C = lbl_80293968[pRecord->mUnknown118];
}

void fn_8008318C(int handle, Record_80082B18 *pRecord, int team, int offset)
{
    fn_801FCE10(0,
                "use 'TATS' insert into \x8c set 'DIGP' = \x82 and 'DIOP' = \x82 and 'ANFP' = \x88 and 'ANLP' = "
                "\x88 and 'DIGT' = \x82 and 'ITGT' = \x82 and 'YTRP' = \x82 and 'SOPP' = \x82 and 'OPBP' = \x82 "
                "and 'NEJP' = \x82 and 'RVOP' = \x82 and 'EGAP' = \x82 and 'CFRP' = \x82 and 'XELP' = \x82 and "
                "'PXSP' = \x82 and 'PTEP' = \x82 and 'LILP' = \x82 and 'DPSP' = \x82 and 'IGAP' = \x82 and 'MUJP' "
                "= \x82 and 'HTCP' = \x82 and 'KTBP' = \x82 and 'KATP' = \x82 and 'SSPP' = \x82 and 'KLBP' = \x82 "
                "and 'VOCP' = \x82 and 'TFDP' = \x82 and 'PMIP' = \x82 and 'NSPP' = \x82 and 'LECP' = \x82 and "
                "'LCUP' = \x82 and '1TGS' = \x82 and '2TGS' = \x82 and '3TGS' = \x82 and '4TGS' = \x82 and 'TGHP' "
                "= \x82 and 'TGWP' = \x82 and 'NAHP' = \x82 and 'TBYP' = \x82 and 'TLFP' = \x82 and 'THLP' = \x82 "
                "and 'RAHP' = \x82 and '1AHP' = \x82 and 'TAHP' = \x82 and 'ROHP' = \x82 and 'RWEP' = \x82 and "
                "'APSP' = \x82 and 'TRSP' = \x82 and 'TNPP' = \x82 and 'RAUP' = \x82 and 'LULP' = \x82 and 'WBEP' "
                "= \x82 and 'DNHP' = \x82 and 'DHRP' = \x82 and 'TRWP' = \x82 and 'LWLP' = \x82 and 'COSP' = \x82 "
                "and 'OHSP' = \x82 and 'TARP' = \x82 and 'OTAP' = \x82 and 'TLRP' = \x82 and 'OTLP' = \x82 and "
                "'DBTP' = \x82 and 'DFTP' = \x82 and 'CDHP' = \x82 and 'IKSP' = \x82 and 'HFFP' = \x82 and 'BEFP' "
                "= \x82 and 'AEFP' = \x82 and 'OMFP' = \x82 and 'PLFP' = \x82 and 'CJFP' = \x82 and 'YEFP' = \x82 "
                "and 'ONFP' = \x82 and 'CHFP' = \x82\n",
                handle, pRecord->mUnknown00, pRecord->mUnknown00, pRecord->mUnknown04, pRecord->mUnknown08, team,
                team, 2, pRecord->mUnknown10, pRecord->mUnknown14, pRecord->mUnknown18, pRecord->mUnknown1C,
                pRecord->mUnknown20, pRecord->mUnknown2C, pRecord->mUnknown30, pRecord->mUnknown68 + offset,
                pRecord->mUnknown34, pRecord->mUnknown24, pRecord->mUnknownC4, pRecord->mUnknownC8,
                pRecord->mUnknownCC, pRecord->mUnknownD0, pRecord->mUnknownD4, pRecord->mUnknownD8,
                pRecord->mUnknownDC, pRecord->mUnknownE0, pRecord->mUnknownE4, pRecord->mUnknownE8,
                pRecord->mUnknownEC, pRecord->mUnknownF0, pRecord->mUnknownF4, pRecord->mUnknownF8,
                pRecord->mUnknownFC, pRecord->mUnknown100, pRecord->mUnknown104, pRecord->mUnknown108,
                pRecord->mUnknown10C, pRecord->mUnknown110, pRecord->mUnknown114, pRecord->mUnknown118,
                pRecord->mUnknown11C, pRecord->mUnknown38, pRecord->mUnknown5C, pRecord->mUnknown60,
                pRecord->mUnknown6C, pRecord->mUnknown70, pRecord->mUnknown74, pRecord->mUnknown78,
                pRecord->mUnknown7C, pRecord->mUnknown80, pRecord->mUnknown84, pRecord->mUnknown88,
                pRecord->mUnknown8C, pRecord->mUnknown90, pRecord->mUnknown94, pRecord->mUnknown98,
                pRecord->mUnknown9C, pRecord->mUnknownA0, pRecord->mUnknownA4, pRecord->mUnknownA8,
                pRecord->mUnknownAC, pRecord->mUnknownB0, pRecord->mUnknownB4, pRecord->mUnknownB8,
                pRecord->mUnknownBC, pRecord->mUnknownC0, pRecord->mUnknown28, pRecord->mUnknown3C,
                pRecord->mUnknown40, pRecord->mUnknown44, pRecord->mUnknown48, pRecord->mUnknown4C,
                pRecord->mUnknown50, pRecord->mUnknown54, pRecord->mUnknown58, pRecord->mUnknown64);
}

}
