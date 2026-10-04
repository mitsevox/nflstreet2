#include "game/FMCAPPORT.h"
#include "game/Object_8007A334.h"
#include "game/fn_801C1F94.h"

#include <string.h>

/* Record returned by fn_80221BAC. */
struct Record_80221BAC {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    void *mpUnknown20;
};

/* Local block passed to fn_8004625C by fn_80188A60. */
struct Desc_8004625C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    char *mpUnknown8;
};

/* One pending entry, applied by fn_80188D2C once fn_80221BAC finds it. */
struct Pending_80362F64 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknown12[3];
};

extern "C" {
void fn_80083E1C(Object_8007A334 *pObject, int a);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
void fn_8004625C(Desc_8004625C *pDesc, int id, FMCAPPORTText *pText);
void fn_801CE910(void);
void *fn_8021EA44(int index);
int fn_8021E2B4(void *pObject, int a, int b);
char *fn_80220BFC(int a, int b);
Record_80221BAC *fn_80221BAC(void *pObject, int a, int b);
void fn_80239D1C(char *p, int size);
void fn_8024E034(void);
}

static Pending_80362F64 sPending[2];
static unsigned char sReady = 0;
static unsigned short sIds[2] = {2, 3};

extern "C" {
int fn_80188DD0(int index);

void fn_80188A30(int id, char *p)
{
    fn_80239D1C(p, 0x200);
    fn_8024E034();
}

void fn_80188A5C(void)
{
}

void fn_80188A60(int id, int a, int b, int c, const unsigned char *pColor)
{
    FMCAPPORTText text;
    Desc_8004625C desc;
    char buffer[1024];
    Record_80221BAC *pRecord;
    char *pDst;
    int count;
    int bytes;

    pRecord = fn_80221BAC(fn_8021EA44(1), a, b);
    count = 256;
    bytes = 4;
    desc.mUnknown0 = pRecord->mUnknown8;
    desc.mUnknown2 = pRecord->mUnknown16;
    if (pRecord->mUnknown8 != 1 && pRecord->mUnknown8 != 9) {
        count = 16;
    }
    if (pRecord->mUnknown16 != 6) {
        bytes = 2;
    }
    desc.mUnknown4 = count * bytes;
    memcpy(buffer, pRecord->mpUnknown20, desc.mUnknown4);
    desc.mpUnknown8 = buffer;
    fn_801C1F94(&text, 0, sizeof(text));
    text.mChars[20] = pColor[0];
    text.mChars[21] = pColor[1];
    text.mChars[22] = pColor[2];
    fn_8004625C(&desc, c, &text);
    pDst = fn_80220BFC(5, id);
    fn_801CE910();
    memcpy(pDst, buffer, desc.mUnknown4);
    fn_80188A30(id, pDst);
}

void fn_80188B78(int a, int b)
{
    Object_8007A334 cursor;
    unsigned char color0[3];
    unsigned char color1[3];
    void *pObject;
    int id0;
    int id1;

    pObject = fn_8021EA44(1);
    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, a, 0);
    id0 = fn_80084158(&cursor);
    color0[0] = fn_800841AC(&cursor);
    color0[1] = fn_800841D8(&cursor);
    color0[2] = fn_80084204(&cursor);
    fn_80084034(&cursor, b, 0);
    id1 = fn_80084158(&cursor);
    color1[0] = fn_800841AC(&cursor);
    color1[1] = fn_800841D8(&cursor);
    color1[2] = fn_80084204(&cursor);
    fn_80083F68(&cursor);
    fn_8021E2B4(pObject, 4, id0);
    fn_8021E2B4(pObject, 4, id1);
    fn_80188A60(fn_80188DD0(0), 4, id0, 0xAC, color0);
    fn_80188A60(fn_80188DD0(1), 4, id1, 0xAC, color1);
}

void fn_80188D2C(void);

void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor)
{
    int i;

    for (i = 0; i < 3; i++) {
        sPending[index].mUnknown12[i] = pColor[i];
    }
    sPending[index].mUnknown0 = a;
    sPending[index].mUnknown8 = c;
    sPending[index].mUnknown4 = b;
    fn_80188D2C();
}

void fn_80188D2C(void)
{
    int i;

    if (!sReady) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (sPending[i].mUnknown4 != -1) {
            if (fn_80221BAC(fn_8021EA44(1), sPending[i].mUnknown0, sPending[i].mUnknown4)) {
                fn_80188A60(fn_80188DD0(i), sPending[i].mUnknown0, sPending[i].mUnknown4, sPending[i].mUnknown8,
                            sPending[i].mUnknown12);
                sPending[i].mUnknown4 = -1;
            }
        }
    }
}

int fn_80188DD0(int index)
{
    int result;

    if (index == -1) {
        result = -1;
    } else {
        result = sIds[index];
    }
    return result;
}

int fn_80188DF0(int index)
{
    int result;

    if (index == -1) {
        result = -1;
    } else {
        result = sIds[index] | 0x50000;
    }
    return result;
}

void fn_80188E14(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        fn_801C1F94(&sPending[i], 0, sizeof(Pending_80362F64));
        sPending[i].mUnknown4 = -1;
    }
    if (!sReady) {
        fn_80188A5C();
        sReady = 1;
    }
}

void fn_80188E8C(void)
{
    sReady = 0;
}
}
