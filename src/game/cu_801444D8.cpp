#include <dolphin/mtx.h>
#include "game/cu_801444D8.h"
#include "game/bitstream.h"
#include "game/cu_8002B8F8.h"
#include <math.h>
#include <string.h>
#include "game/cu_801962CC.h"
#include "game/fn_801D2B7C.h"

/* Header of the emitter list built by fn_801444D8 and filled by fn_80144EDC. */
struct List_803EB230 {
    unsigned short mCount;
    unsigned short mCapacity;
    Object_80144CE0 **mppList;
};

/* Block passed to fn_801C06E8; the halfword +0 is read as a count there. */
struct Config_803EB22A {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
};

/* Snapshot of lbl_803EB240 taken by fn_801447E8 before it stores the new counts. */
struct Counts_801447E8 {
    signed char mUnknown0;
    signed char mUnknown1;
};

/* One 0x24-byte record of the six-entry table written to the replay stream. */
struct Record_8031B6F8 {
    int mId;
    float mPos[3];
    float mRot[4];
    Source_80144CE0 *mpSource;
};

/* One 12-byte entry of the 20-entry table at lbl_802DD020. */
struct Entry_802DD020 {
    int mIndex;
    int mFile;
    int mUnknown8;
};

/* Descriptor passed to fn_801DE1E0. */
struct Desc_802DCFF8 {
    int mUnknown00;
    unsigned short mUnknown04;
    unsigned short mUnknown06;
    unsigned short mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int (*mpUnknown20)(Object_80144CE0 *pObject, int mode);
    unsigned char mUnknown24;
};

struct Entry_80196B24 {
    void *mpUnknown0;
    int mUnknown4;
};

/* Pool owner returned by fn_801DFD34. */
struct Manager_801DFD34 {
    void *mpPool;
};

/* Pool item of Manager_801DFD34::mpPool. */
struct Item_801DFD34 {
    Object_80144CE0 *mpObject;
};

extern "C" {
extern unsigned char lbl_803EB74C;

int fn_8002D0AC(Type_803EA368 *p);
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030304(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_8003065C(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*pWrite)(BitStream_t *),
                 void (*pRead)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float), int size,
                 const char *pName);
int fn_8004CB98(int index);
void fn_800A3170(void);
void fn_800A3450(void);
int fn_800A34C8(int index);
void *fn_800C47C4(void);
void fn_80196AF0(void);
void fn_80196B20(void);
void fn_80196B24(Entry_80196B24 *pEntries, int *pValues, void *pData);
void fn_80196BD4(int *pValues);
void fn_80145264(void);
void fn_801A762C(void);
void fn_801A7778(void);
void fn_801A7784(float rate);
void fn_801A7880(void);
void fn_801C06E8(Config_803EB22A *pConfig);
void fn_801C07DC(void);
void *fn_801C6B4C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0F80(Mtx44 m);
void *fn_801D2BB0(int a, int size, int c, int d);
int fn_801DCF0C(int type, int size, int count, void *pCreate, void *pDestroy);
void fn_801DCF8C(int type);
void fn_801DD0C8(int handle, int type, int a, int (*pCallback)(void *));
int fn_801DD268(int handle, int type, int a, void *pInit);
void fn_801DD320(int handle, int item);
void fn_801DD3AC(int handle, int item, int a);
void fn_801DE1E0(Desc_802DCFF8 *pDesc);
void fn_801DE410(void);
void fn_801DE4F8(unsigned short a);
void fn_801DEA90(Object_80144CE0 *pObject, int a);
unsigned short fn_801DECFC(unsigned short id, void *pDesc);
Object_80144CE0 *fn_801DEEF8(unsigned short handle);
void fn_801DEF18(Object_80144CE0 *pObject);
void fn_801DF620(void *pDesc, void *pData, int a);
Manager_801DFD34 *fn_801DFD34(void);
void fn_801E0520(Object_80144CE0 *pObject);
void *fn_801EF7BC(void *pArchive, int file, void *pBuffer);
int fn_801F010C(void *pArchive, int file);
int fn_801F0C50(void *pArchive, int file);
void fn_80228D58(int handle);
void fn_80228E18(void);

void fn_801444D8(void);
void fn_80144564(void);
void fn_801445A8(int index, int id);
void fn_80144660(void);
int fn_80144704(void);
void fn_80144718(BitStream_t *pStream);
void fn_801447E8(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t);
void fn_80144B50(int handle);
void fn_80144C6C(int handle);
int fn_80144E64(void *pContext);
void fn_80144EDC(float rate);
int fn_80144FE8(int a);
int fn_80145074(int a);
void fn_80145100(int index, int file);
int fn_80145118(int index);
void fn_8014512C(void);
void fn_8014516C(Record_8031B6F8 record);
}

static unsigned char lbl_803EB228 = 0;
static Config_803EB22A lbl_803EB22A = { 8, 0, 0, 0 };
static List_803EB230 lbl_803EB230 = { 0, 0, 0 };
static int lbl_803EB238 = 0;
static unsigned char lbl_803EB23C = 1;
static signed char lbl_803EB23D = 0;
static signed char lbl_803EB240[2] = { 0, 0 };

static Desc_802DCFF8 lbl_802DCFF8 = { 24, 172, 70, 60, 32.0f, 1, 200000, 20, 1, fn_80196564, 0 };
static Entry_802DD020 lbl_802DD020[20] = {
    { 0, 46, 14 },  { 1, 18, 0 },   { 2, 19, 0 },   { 3, 22, 0 },   { 4, 23, 0 },
    { 5, 24, 0 },   { 6, 29, 0 },   { 7, 30, 0 },   { 8, -1, 0 },   { 9, -1, 0 },
    { 10, -1, 0 },  { 11, -1, 0 },  { 12, -1, 0 },  { 13, -1, 0 },  { 14, -1, 0 },
    { 15, -1, 0 },  { 16, -1, 0 },  { 17, -1, 0 },  { 18, -1, 0 },  { 19, -1, 0 },
};
static Entry_80196B24 lbl_802DD110[8] = {
    { 0, 94 }, { 0, 95 }, { 0, 96 }, { 0, 97 }, { 0, 98 }, { 0, 99 }, { 0, 100 }, { 0, 101 },
};
static int lbl_802DD150[8] = { 0 };

static unsigned short lbl_8031B6D0[20];
static Record_8031B6F8 lbl_8031B6F8[6];

void fn_801444D8(void)
{
    Manager_801DFD34 *pManager = fn_801DFD34();
    List_803EB230 *pList = &lbl_803EB230;
    int count = 0;
    void *pItem;

    for (pItem = fn_801C6B4C(pManager->mpPool, 0); pItem != 0; pItem = fn_801C6C84(pManager->mpPool, pItem)) {
        count++;
    }
    pList->mCapacity = count;
    pList->mCount = 0;
    if (count != 0) {
        pList->mppList = (Object_80144CE0 **)fn_801D2B7C(count * 4, 0, 0);
    } else {
        pList->mppList = 0;
    }
}

void fn_80144564(void)
{
    List_803EB230 *pList = &lbl_803EB230;

    if (pList->mppList != 0) {
        fn_801D2BD0(pList->mppList);
        pList->mppList = 0;
        pList->mCapacity = 0;
    }
}

void fn_801445A8(int index, int id)
{
    char desc[1632];
    void *pArchive = fn_800C47C4();
    void *pBuffer = fn_801D2BB0(1, fn_801F0C50(pArchive, lbl_802DD020[index].mFile), 4, 0);
    void *pData = fn_801EF7BC(pArchive, lbl_802DD020[index].mFile, pBuffer);

    fn_801F010C(pArchive, lbl_802DD020[index].mFile);
    fn_801DF620(desc, pData, 0);
    lbl_8031B6D0[index] = fn_801DECFC(id, desc);
    fn_801D2BD0(pBuffer);
}

void fn_80144660(void)
{
    unsigned int i;
    int id;

    for (i = 0; i < 1; i++) {
        fn_801445A8(i, lbl_802DD020[i].mUnknown8);
    }
    for (i = 1; i <= 11; i++) {
        id = fn_800A34C8(i);
        if (id != 0) {
            fn_801445A8(i, id);
        }
    }
    for (i = 12; i <= 19; i++) {
        id = fn_8004CB98(i);
        if (id != 0) {
            fn_801445A8(i, id);
        }
    }
}

/* Size in bits of one replay frame of this channel. */
int fn_80144704(void)
{
    int size = 8;
    int i;

    for (i = 0; i < 6; i++) {
        size += 16 + 48 + 48 + 32;
    }
    return size;
}

/* Replay channel writer: the record count and the six spawn records, after
   which the pending count is cleared. */
void fn_80144718(BitStream_t *pStream)
{
    unsigned int i;

    fn_80191068(pStream, lbl_803EB23D, 8);
    for (i = 0; i < 6; i++) {
        fn_80191068(pStream, (short)lbl_8031B6F8[i].mId, 16);
        fn_80030554(pStream, lbl_8031B6F8[i].mPos, 16, 256.0f);
        fn_8003065C(pStream, lbl_8031B6F8[i].mRot, 12, 1024.0f);
        fn_80191068(pStream, (unsigned int)lbl_8031B6F8[i].mpSource, 32);
    }
    lbl_803EB23D = 0;
}

/* Replay channel reader: every stream holds the same layout; the records of
   pStream1 are spawned again when the stored counts change. */
void fn_801447E8(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    Record_8031B6F8 record;
    Counts_801447E8 last;
    signed char count;
    signed char value;
    unsigned int i;

    count = ReadBitStream(pStream1, 8);
    value = ReadBitStream(pStream0, 8);
    last.mUnknown0 = lbl_803EB240[0];
    last.mUnknown1 = lbl_803EB240[1];
    lbl_803EB240[1] = value;
    lbl_803EB240[0] = count;
    if (pStream2 != 0) {
        ReadBitStream(pStream2, 8);
    }
    if (pStream3 != 0) {
        ReadBitStream(pStream3, 8);
    }
    for (i = 0; i < count; i++) {
        record.mId = ReadBitStream(pStream1, 16);
        fn_800301C4(pStream1, record.mPos, 16, 256.0f);
        fn_80030304(pStream1, record.mRot, 12, 1024.0f);
        record.mpSource = (Source_80144CE0 *)(unsigned int)ReadBitStream(pStream1, 32);
        if (lbl_803EB240[0] != last.mUnknown0 || lbl_803EB240[1] != last.mUnknown1) {
            fn_80145EFC(record.mId, record.mPos, record.mRot, record.mpSource);
        }
        ReadBitStream(pStream0, 16);
        fn_800301C4(pStream0, record.mPos, 16, 256.0f);
        fn_80030304(pStream0, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream0, 32);
        if (pStream2 != 0) {
            ReadBitStream(pStream2, 16);
            fn_800301C4(pStream2, record.mPos, 16, 256.0f);
            fn_80030304(pStream2, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream2, 32);
        }
        if (pStream3 != 0) {
            ReadBitStream(pStream3, 16);
            fn_800301C4(pStream3, record.mPos, 16, 256.0f);
            fn_80030304(pStream3, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream3, 32);
        }
    }
    for (i = count; i <= 5; i++) {
        ReadBitStream(pStream1, 16);
        fn_800301C4(pStream1, record.mPos, 16, 256.0f);
        fn_80030304(pStream1, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream1, 32);
        ReadBitStream(pStream0, 16);
        fn_800301C4(pStream0, record.mPos, 16, 256.0f);
        fn_80030304(pStream0, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream0, 32);
        if (pStream2 != 0) {
            ReadBitStream(pStream2, 16);
            fn_800301C4(pStream2, record.mPos, 16, 256.0f);
            fn_80030304(pStream2, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream2, 32);
        }
        if (pStream3 != 0) {
            ReadBitStream(pStream3, 16);
            fn_800301C4(pStream3, record.mPos, 16, 256.0f);
            fn_80030304(pStream3, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream3, 32);
        }
    }
}

void fn_80144B50(int handle)
{
    int i;

    for (i = 0; i < 20; i++) {
        lbl_8031B6D0[i] = 20;
    }
    lbl_803EB22A.mUnknown4 = lbl_803EB74C;
    fn_801C06E8(&lbl_803EB22A);
    fn_80196B24(lbl_802DD110, lbl_802DD150, fn_800C47C4());
    fn_801DE1E0(&lbl_802DCFF8);
    fn_80144660();
    fn_801444D8();
    fn_80196480(1200);
    fn_801DCF0C(22, 20, 1, 0, 0);
    fn_801DD0C8(handle, 22, 0, fn_80144E64);
    lbl_803EB238 = fn_801DD268(handle, 22, 0, 0);
    fn_801DD3AC(handle, lbl_803EB238, 12);
    lbl_803EB228 = 1;
    fn_801A762C();
    fn_800A3170();
    lbl_803EB23D = 0;
    memset(lbl_8031B6F8, 0, sizeof(lbl_8031B6F8));
}

void fn_80144C6C(int handle)
{
    fn_800A3450();
    fn_801A7778();
    fn_80196BD4(lbl_802DD150);
    fn_801DE410();
    fn_801C07DC();
    fn_80144564();
    fn_8019651C();
    fn_801DD320(handle, lbl_803EB238);
    fn_80228D58(lbl_803EB238);
    fn_80228E18();
    fn_801DCF8C(22);
    lbl_803EB228 = 0;
}

Object_80144CE0 *fn_80144CE0(Args_80144CE0 *pArgs, int b, Source_80144CE0 *pSource)
{
    Object_80144CE0 *pObject = 0;
    Mtx44 *pTarget;

    if (lbl_803EB228 != 0 && pArgs->mUnknown00 != 21 && lbl_8031B6D0[pArgs->mUnknown00] != 20
        && (pObject = fn_801DEEF8(lbl_8031B6D0[pArgs->mUnknown00])) != 0) {
        if (pSource != 0) {
            pObject->mUnknown35B = (unsigned char)((pSource->mUnknown0C + pSource->mUnknown10 + pSource->mUnknown14) * 33.333336f);
        } else {
            pObject->mUnknown35B = 100;
        }
        pTarget = pArgs->mUnknown04;
        if (pTarget != 0) {
            pObject->mpUnknown3B4 = pTarget;
            pObject->mUnknown3C8 = (*pTarget)[0][3];
            pObject->mUnknown3CC = (*pTarget)[1][3];
            pObject->mUnknown3D0 = (*pTarget)[2][3];
            pObject->mUnknown2B6 = 1;
        } else {
            pObject->mUnknown3C8 = (*pArgs->mUnknown08)[0][3];
            pObject->mUnknown3CC = (*pArgs->mUnknown08)[1][3];
            pObject->mUnknown3D0 = (*pArgs->mUnknown08)[2][3];
            pObject->mUnknown2B6 = 0;
        }
        if (pObject->mUnknown0F0 != 3) {
            pObject->mUnknown35A = 1;
        }
        fn_801D0508();
        if (pObject->mUnknown03C != 0) {
            fn_801D0664(pObject->mUnknown35C);
        }
        fn_801D0F80(pObject->mUnknown35C);
        fn_801D0544();
        pObject->mUnknown03C = 1;
        fn_801E0520(pObject);
    }
    return pObject;
}

void fn_80144E38(Object_80144CE0 *pObject)
{
    if (pObject->mUnknown2B4 != 0) {
        fn_801DEF18(pObject);
    }
}

int fn_80144E64(void *pContext)
{
    if (lbl_803EB23C != 0) {
        List_803EB230 *pList = &lbl_803EB230;
        unsigned short count = pList->mCount;
        Object_80144CE0 **ppList = pList->mppList;
        unsigned int i;

        fn_80196AF0();
        for (i = 0; i < count; i++) {
            fn_80196564(*ppList++, 1);
        }
        fn_80196B20();
        fn_80145264();
        fn_801A7880();
    }
    return 0;
}

void fn_80144EDC(float rate)
{
    int count = 0;
    List_803EB230 *pList;
    Manager_801DFD34 *pManager;
    Item_801DFD34 *pItem;

    fn_801DE4F8((unsigned int)fabsf(1.0f / rate * 60.0f));
    pList = &lbl_803EB230;
    pManager = fn_801DFD34();
    for (pItem = (Item_801DFD34 *)fn_801C6B4C(pManager->mpPool, 0); pItem != 0;
         pItem = (Item_801DFD34 *)fn_801C6C84(pManager->mpPool, pItem)) {
        if (pItem->mpObject->mUnknown2B4 != 0) {
            fn_801DEA90(pItem->mpObject, 1);
            pList->mppList[count++] = pItem->mpObject;
        }
    }
    pList->mCount = count;
    fn_801A7784(rate);
    fn_801DE4F8(60);
}

extern "C" const Vector_80039F5C lbl_802A03D0 = { 0.0f, 0.0f, 1.0f };

int fn_80144FE8(int a)
{
    switch (a) {
    case 0:
        return 21;
    case 1:
        return 21;
    case 2:
        return 6;
    case 3:
        return 1;
    case 4:
        return 3;
    case 5:
        return 21;
    case 6:
        return 21;
    case 7:
        return 21;
    case 8:
        return 21;
    case 9:
        return 21;
    case 10:
        return 21;
    case 11:
        return 21;
    case 12:
        return 21;
    case 13:
        return 21;
    }
    return 21;
}

int fn_80145074(int a)
{
    switch (a) {
    case 0:
        return 21;
    case 1:
        return 21;
    case 2:
        return 7;
    case 3:
        return 2;
    case 4:
        return 4;
    case 5:
        return 21;
    case 6:
        return 21;
    case 7:
        return 21;
    case 8:
        return 21;
    case 9:
        return 21;
    case 10:
        return 21;
    case 11:
        return 21;
    case 12:
        return 21;
    case 13:
        return 21;
    }
    return 21;
}

void fn_80145100(int index, int file)
{
    lbl_802DD020[index].mFile = file;
}

int fn_80145118(int index)
{
    return lbl_802DD150[index];
}

void fn_8014512C(void)
{
    fn_80030ACC(fn_80144718, fn_801447E8, fn_80144704(), "Replay Particles");
}

void fn_8014516C(Record_8031B6F8 record)
{
    if (fn_8002D0AC(lbl_803EA368)) {
        signed char count = lbl_803EB23D;

        if (count <= 5) {
            float *pRot;
            float *pPos;

            lbl_8031B6F8[count].mId = record.mId;
            pRot = lbl_8031B6F8[count].mRot;
            pRot[0] = record.mRot[0];
            pRot[1] = record.mRot[1];
            pRot[2] = record.mRot[2];
            pRot[3] = record.mRot[3];
            pPos = lbl_8031B6F8[count].mPos;
            pPos[0] = record.mPos[0];
            pPos[1] = record.mPos[1];
            pPos[2] = record.mPos[2];
            lbl_8031B6F8[count].mpSource = record.mpSource;
            lbl_803EB23D++;
        }
    }
}
