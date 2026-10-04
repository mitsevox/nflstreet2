#include "game/Object_80039F5C.h"

/* Descriptor passed to fn_80238424, which allocates mUnknown0 records of
   mUnknown4 bytes after mUnknown8 callback slots. */
struct Desc_80238424 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

/* Record returned by fn_80067CA8 and handed to the registered callbacks. */
struct Record_80067CA8 {
    int mUnknown0;
    Vector_80039F5C mPos;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    unsigned short mUnknown20;
};

typedef int (*Fn_803EA674)(int);
typedef void (*Callback_80067EC8)(Record_80067CA8 *pRecord);

extern "C" {
int fn_8009D990(int index);
void fn_8006CE84(Record_80067CA8 *pRecord);
void fn_800D70CC(Record_80067CA8 *pRecord);
int fn_801D34D0(void *pDest, int size, int value, int width);
int fn_80238424(Desc_80238424 *pDesc);
void fn_802384C4(int handle);
void *fn_8023850C(int handle);
void fn_80238570(int handle, int unknown);
void fn_8023861C(int handle);
void fn_80238680(int handle, Callback_80067EC8 pCallback);
void fn_802386DC(int handle, Callback_80067EC8 pCallback);
}

static Desc_80238424 lbl_802D5098 = { 50, sizeof(Record_80067CA8), 3 };
static int lbl_803EA670 = 0xFF;
static Fn_803EA674 lbl_803EA674 = 0;

extern "C" void fn_80067C10(void)
{
    lbl_803EA670 = fn_80238424(&lbl_802D5098);
    lbl_803EA674 = 0;
}

extern "C" void fn_80067C44(void)
{
    fn_802384C4(lbl_803EA670);
    lbl_803EA670 = 0xFF;
}

extern "C" void fn_80067C70(void)
{
    lbl_803EA674 = fn_8009D990;
    fn_80238680(lbl_803EA670, fn_8006CE84);
}

extern "C" Record_80067CA8 *fn_80067CA8(void)
{
    return (Record_80067CA8 *)fn_8023850C(lbl_803EA670);
}

extern "C" void fn_80067CCC(void)
{
    fn_8023861C(lbl_803EA670);
}

extern "C" void fn_80067CF0(void)
{
    Record_80067CA8 *p = fn_80067CA8();

    if (lbl_803EA674) {
        p->mUnknown1C = lbl_803EA674(1);
    }
    fn_80238570(lbl_803EA670, 0);
    fn_800D70CC(p);
}

extern "C" void fn_80067D4C(int type, Vector_80039F5C *pPos)
{
    Record_80067CA8 *p = fn_80067CA8();

    fn_801D34D0(p, sizeof(*p), 0, 4);
    p->mUnknown20 = type;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    fn_80067CF0();
}

extern "C" void fn_80067DB8(int type, Vector_80039F5C *pPos, int a, int b, int c)
{
    Record_80067CA8 *p = fn_80067CA8();

    fn_801D34D0(p, sizeof(*p), 0, 4);
    p->mUnknown20 = type;
    p->mUnknown10 = a;
    p->mUnknown14 = b;
    p->mUnknown18 = c;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    fn_80067CF0();
}

extern "C" void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c)
{
    Record_80067CA8 *p = fn_80067CA8();

    fn_801D34D0(p, sizeof(*p), 0, 4);
    p->mUnknown20 = type;
    p->mUnknown0 = id;
    p->mUnknown10 = a;
    p->mUnknown14 = b;
    p->mUnknown18 = c;
    if (pPos) {
        p->mPos.mX = pPos->mX;
        p->mPos.mY = pPos->mY;
        p->mPos.mZ = pPos->mZ;
    }
    fn_80067CF0();
}

extern "C" void fn_80067EC8(Callback_80067EC8 pCallback)
{
    fn_80238680(lbl_803EA670, pCallback);
}

extern "C" void fn_80067EF0(Callback_80067EC8 pCallback)
{
    fn_802386DC(lbl_803EA670, pCallback);
}
