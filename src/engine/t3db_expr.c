#include <string.h>
#include "engine/t3db.h"


extern double fn_8025FBD4(double x);
typedef void (*TDbOpFunc_802047EC)(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r);


static void fn_80203754(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = a->mType;
    r->mValue.i = a->mValue.i;
}

static void fn_80203768(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == -1;
}

static void fn_802037C0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != 1;
}

static void fn_8020381C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == 0;
}

static void fn_80203870(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == 1;
}

static void fn_802038C8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != -1;
}

static void fn_80203924(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != 0;
}

static void fn_80203980(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.s && a->mValue.s[0] && b->mValue.s && b->mValue.s[0];
}

static void fn_802039C8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = (a->mValue.s && a->mValue.s[0]) || (b->mValue.s && b->mValue.s[0]);
}

static void fn_80203A10(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.s && a->mValue.s[0];
    r->mValue.u ^= b->mValue.s && b->mValue.s[0];
}

static void fn_80203A6C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = !a->mValue.s || !a->mValue.s[0];
}

static void fn_80203A9C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == -1;
}

static void fn_80203AEC(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != 1;
}

static void fn_80203B40(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == 0;
}

static void fn_80203B8C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == 1;
}

static void fn_80203BDC(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != -1;
}

static void fn_80203C30(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != 0;
}

static void fn_80203C84(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i < b->mValue.i;
}

static void fn_80203CA8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i <= b->mValue.i;
}

static void fn_80203CD0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i == b->mValue.i;
}

static void fn_80203CF4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i > b->mValue.i;
}

static void fn_80203D18(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i >= b->mValue.i;
}

static void fn_80203D40(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i != b->mValue.i;
}

static void fn_80203D68(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i >= (int)(b->mValue.l >> 32) && a->mValue.i <= (int)b->mValue.l;
}

static void fn_80203DA8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i < (int)(b->mValue.l >> 32) || a->mValue.i > (int)b->mValue.l;
}

static void fn_80203DE4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i && b->mValue.i;
}

static void fn_80203E14(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i || b->mValue.i;
}

static void fn_80203E44(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i != 0;
    r->mValue.u ^= b->mValue.i != 0;
}

static void fn_80203E84(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = !a->mValue.i;
}

static void fn_80203EA0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i + b->mValue.i;
}

static void fn_80203EBC(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i - b->mValue.i;
}

static void fn_80203ED8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i * b->mValue.i;
}

static void fn_80203EF4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = b->mValue.i ? a->mValue.i / b->mValue.i : 0;
}

static void fn_80203F24(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i * b->mValue.i / 100;
}

static void fn_80203F58(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i < b->mValue.i ? a->mValue.i : b->mValue.i;
}

static void fn_80203F7C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i > b->mValue.i ? a->mValue.i : b->mValue.i;
}

static void fn_80203FA0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.i ? (float)a->mValue.i / (float)b->mValue.i : 0.0f;
}

static void fn_80204018(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < b->mValue.u;
}

static void fn_8020403C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u <= b->mValue.u;
}

static void fn_80204060(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u > b->mValue.u;
}

static void fn_80204084(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u >= b->mValue.u;
}

static void fn_802040A8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u >= (unsigned int)(b->mValue.l >> 32) && a->mValue.u <= (unsigned int)b->mValue.l;
}

static void fn_802040E4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < (unsigned int)(b->mValue.l >> 32) || a->mValue.u > (unsigned int)b->mValue.l;
}

static void fn_80204120(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u + b->mValue.u;
}

static void fn_8020413C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u - b->mValue.u;
}

static void fn_80204158(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u * b->mValue.u;
}

static void fn_80204174(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.u ? a->mValue.u / b->mValue.u : 0;
}

static void fn_802041A4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u * b->mValue.u / 100;
}

static void fn_802041D0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < b->mValue.u ? a->mValue.u : b->mValue.u;
}

static void fn_802041F4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u > b->mValue.u ? a->mValue.u : b->mValue.u;
}

static void fn_80204218(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u & b->mValue.u;
}

static void fn_80204234(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u | b->mValue.u;
}

static void fn_80204250(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u ^ b->mValue.u;
}

static void fn_8020426C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = ~a->mValue.u;
}

static void fn_80204284(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.u ? (float)a->mValue.u / (float)b->mValue.u : 0.0f;
}

static void fn_802042F4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f < b->mValue.f;
}

static void fn_80204318(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f <= b->mValue.f;
}

static void fn_80204340(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f > b->mValue.f;
}

static void fn_80204364(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f >= b->mValue.f;
}

static void fn_8020438C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f >= (float)(unsigned int)(b->mValue.l >> 32)
               && a->mValue.f <= (float)(unsigned int)b->mValue.l;
}

static void fn_8020440C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f < (float)(unsigned int)(b->mValue.l >> 32)
               || a->mValue.f > (float)(unsigned int)b->mValue.l;
}

static void fn_8020448C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f + b->mValue.f;
}

static void fn_802044A8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f - b->mValue.f;
}

static void fn_802044C4(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f * b->mValue.f;
}

static void fn_802044E0(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.f != 0.0f ? a->mValue.f / b->mValue.f : 0.0f;
}

static void fn_8020450C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f * b->mValue.f * 0.01f;
}

static void fn_80204534(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f < b->mValue.f ? a->mValue.f : b->mValue.f;
}

static void fn_8020455C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f > b->mValue.f ? a->mValue.f : b->mValue.f;
}

static void fn_80204584(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = (int)(a->mValue.f + 0.5f);
}

static void fn_802045B8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = fn_8025FBD4(a->mValue.f);
}

static void fn_802045F8(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.f != 0.0f ? (unsigned int)(a->mValue.f * 100.0f / b->mValue.f) : 0;
}

static void fn_8020467C(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.i ? (unsigned int)((float)a->mValue.i * 100.0f / (float)b->mValue.i) : 0;
}

static void fn_80204738(TDbValue_801FDF28 *a, TDbValue_801FDF28 *b, TDbValue_801FDF28 *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.u ? (unsigned int)((float)a->mValue.u * 100.0f / (float)b->mValue.u) : 0;
}

static TDbOpFunc_802047EC lbl_802F9948[28][5] = {
    { fn_80203754, fn_80203754, fn_80203754, fn_80203754, fn_80203754 },
    { fn_80203768, fn_80203A9C, fn_80203C84, fn_80204018, fn_802042F4 },
    { fn_802037C0, fn_80203AEC, fn_80203CA8, fn_8020403C, fn_80204318 },
    { fn_8020381C, fn_80203B40, fn_80203CD0, fn_80203CD0, fn_80203CD0 },
    { fn_80203870, fn_80203B8C, fn_80203CF4, fn_80204060, fn_80204340 },
    { fn_802038C8, fn_80203BDC, fn_80203D18, fn_80204084, fn_80204364 },
    { fn_80203924, fn_80203C30, fn_80203D40, fn_80203D40, fn_80203D40 },
    { 0, 0, fn_80203D68, fn_802040A8, fn_8020438C },
    { 0, 0, fn_80203DA8, fn_802040E4, fn_8020440C },
    { fn_80203980, 0, fn_80203DE4, fn_80203DE4, fn_80203DE4 },
    { fn_802039C8, 0, fn_80203E14, fn_80203E14, fn_80203E14 },
    { fn_80203A10, 0, fn_80203E44, fn_80203E44, fn_80203E44 },
    { fn_80203A6C, 0, fn_80203E84, fn_80203E84, fn_80203E84 },
    { 0, 0, fn_80203EA0, fn_80204120, fn_8020448C },
    { 0, 0, fn_80203EBC, fn_8020413C, fn_802044A8 },
    { 0, 0, fn_80203EF4, fn_80204174, fn_802044E0 },
    { 0, 0, fn_80203ED8, fn_80204158, fn_802044C4 },
    { 0, 0, fn_80203F24, fn_802041A4, fn_8020450C },
    { 0, 0, fn_80203F58, fn_802041D0, fn_80204534 },
    { 0, 0, fn_80203F7C, fn_802041F4, fn_8020455C },
    { 0, 0, fn_80204218, fn_80204218, 0 },
    { 0, 0, fn_80204234, fn_80204234, 0 },
    { 0, 0, fn_80204250, fn_80204250, 0 },
    { 0, 0, fn_8020426C, fn_8020426C, 0 },
    { 0, 0, fn_80203FA0, fn_80204284, fn_802044E0 },
    { 0, 0, 0, 0, fn_80204584 },
    { 0, 0, 0, 0, fn_802045B8 },
    { 0, 0, fn_8020467C, fn_80204738, fn_802045F8 },
};

void fn_802047EC(TDbExpr_801FAA00 *pExpr, TDbValue_801FDF28 *pResult, TDbTable_801FAA00 **ppTables,
                 unsigned short *pRows)
{
    TDbValue_801FDF28 left;
    TDbValue_801FDF28 right;
    TDbTable_801FAA00 *pTable;
    int columnIndex;

    if (pExpr == 0) {
        pResult->mValue.u = 1;
        return;
    }
    left.mSize = right.mSize = -1;

    switch (pExpr->mLeft.mType) {
    case TDB_TYPE_COLUMN: {
        int tableIndex = (int)(pExpr->mLeft.mValue.l >> 32);
        columnIndex = (unsigned char)pExpr->mLeft.mValue.l;
        pTable = ppTables[tableIndex];

        left.mType = pTable->mColumns[columnIndex].mType;
        if (pRows[tableIndex] == 0xFFFF) {
            left.mValue.u = 0;
        } else {
            unsigned char *pRow = pTable->mRows + pTable->mRowSize * pRows[tableIndex];
            if (left.mType > TDB_TYPE_BINARY) {
                fn_80201D94((unsigned int *)pRow, pTable->mColumns[columnIndex].mBitOffset,
                            pTable->mColumns[columnIndex].mBitCount, &left.mValue.u,
                            left.mType == TDB_TYPE_INT);
            } else {
                left.mValue.p = pRow + (pTable->mColumns[columnIndex].mBitOffset >> 3);
                left.mSize = pTable->mColumns[columnIndex].mBitCount >> 3;
            }
        }
        break;
    }
    case TDB_TYPE_EXPR_TRUNC:
        fn_802047EC(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
        if (left.mType == TDB_TYPE_FLOAT) {
            left.mValue.i = (int)left.mValue.f;
        }
        left.mType = TDB_TYPE_UINT;
        break;
    case TDB_TYPE_EXPR_UINT:
        fn_802047EC(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
        if (left.mType == TDB_TYPE_FLOAT) {
            left.mValue.u = (unsigned int)left.mValue.f;
        }
        left.mType = TDB_TYPE_UINT;
        break;
    case TDB_TYPE_EXPR_FLOAT:
        fn_802047EC(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
        if (left.mType == TDB_TYPE_INT) {
            left.mValue.f = (float)left.mValue.i;
        } else if (left.mType == TDB_TYPE_UINT) {
            left.mValue.f = (float)left.mValue.u;
        }
        left.mType = TDB_TYPE_FLOAT;
        break;
    case TDB_TYPE_BINARY:
        left.mSize = pExpr->mLeft.mSize;
    default:
        left.mType = pExpr->mLeft.mType;
        left.mValue.u = pExpr->mLeft.mValue.u;
        break;
    }

    if (pExpr->mOp) {
        switch (pExpr->mRight.mType) {
        case TDB_TYPE_COLUMN: {
            int tableIndex = (int)(pExpr->mRight.mValue.l >> 32);
            columnIndex = (unsigned char)pExpr->mRight.mValue.l;
            pTable = ppTables[tableIndex];

            right.mType = pTable->mColumns[columnIndex].mType;
            if (pRows[tableIndex] == 0xFFFF) {
                right.mValue.u = 0;
            } else {
                unsigned char *pRow = pTable->mRows + pTable->mRowSize * pRows[tableIndex];
                if (right.mType > TDB_TYPE_BINARY) {
                    fn_80201D94((unsigned int *)pRow, pTable->mColumns[columnIndex].mBitOffset,
                                pTable->mColumns[columnIndex].mBitCount, &right.mValue.u,
                                right.mType == TDB_TYPE_INT);
                } else {
                    right.mValue.p = pRow + (pTable->mColumns[columnIndex].mBitOffset >> 3);
                    right.mSize = pTable->mColumns[columnIndex].mBitCount >> 3;
                    if (right.mSize < left.mSize) {
                        left.mSize = right.mSize;
                    }
                }
            }
            break;
        }
        case TDB_TYPE_RANGE_INT:
        case TDB_TYPE_RANGE_UINT:
        case TDB_TYPE_RANGE_FLOAT:
            right.mType = pExpr->mRight.mType;
            right.mValue = pExpr->mRight.mValue;
            break;
        case TDB_TYPE_EXPR_TRUNC:
            fn_802047EC(pExpr->mRight.mValue.p, &right, ppTables, pRows);
            if (right.mType == TDB_TYPE_FLOAT) {
                right.mValue.i = (int)right.mValue.f;
            }
            right.mType = TDB_TYPE_UINT;
            break;
        case TDB_TYPE_EXPR_UINT:
            fn_802047EC(pExpr->mRight.mValue.p, &right, ppTables, pRows);
            if (right.mType == TDB_TYPE_FLOAT) {
                right.mValue.u = (unsigned int)right.mValue.f;
            }
            right.mType = TDB_TYPE_UINT;
            break;
        case TDB_TYPE_EXPR_FLOAT:
            fn_802047EC(pExpr->mRight.mValue.p, &right, ppTables, pRows);
            if (right.mType == TDB_TYPE_INT) {
                right.mValue.f = (float)right.mValue.i;
            } else if (right.mType == TDB_TYPE_UINT) {
                right.mValue.f = (float)right.mValue.u;
            }
            right.mType = TDB_TYPE_FLOAT;
            break;
        case TDB_TYPE_BINARY:
            right.mSize = pExpr->mRight.mSize;
            if (right.mSize < left.mSize) {
                left.mSize = right.mSize;
            }
        default:
            right.mType = pExpr->mRight.mType;
            right.mValue.u = pExpr->mRight.mValue.u;
            break;
        }
    }

    lbl_802F9948[(unsigned short)pExpr->mOp][left.mType](&left, &right, pResult);
}

int fn_80204D14(TDbExpr_801FAA00 *pSrc, TDbExpr_801FAA00 **ppDst)
{
    int err;

    if (pSrc == 0) {
        *ppDst = 0;
        return 0;
    }
    if (fn_8020360C(&lbl_803E9654, ppDst)) {
        return 2;
    }
    (*ppDst)->mOp = pSrc->mOp;

    switch (pSrc->mLeft.mType) {
    case TDB_TYPE_STRING:
    case TDB_TYPE_BINARY:
        if (pSrc->mLeft.mType == TDB_TYPE_STRING) {
            (*ppDst)->mLeft.mSize = strlen(pSrc->mLeft.mValue.s) + 1;
        } else {
            (*ppDst)->mLeft.mSize = pSrc->mLeft.mSize;
        }
        err = fn_8020D1B0(lbl_803EBE8C, (*ppDst)->mLeft.mSize, &(*ppDst)->mLeft.mValue.p);
        if (err == 0) {
            memcpy((*ppDst)->mLeft.mValue.p, pSrc->mLeft.mValue.p, (*ppDst)->mLeft.mSize);
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        err = fn_80204D14(pSrc->mLeft.mValue.p, (TDbExpr_801FAA00 **)&(*ppDst)->mLeft.mValue.p);
        break;
    default:
        (*ppDst)->mLeft.mValue = pSrc->mLeft.mValue;
        err = 0;
        break;
    }
    (*ppDst)->mLeft.mType = pSrc->mLeft.mType;

    switch (pSrc->mRight.mType) {
    case TDB_TYPE_STRING:
    case TDB_TYPE_BINARY:
        if (pSrc->mRight.mType == TDB_TYPE_STRING) {
            (*ppDst)->mRight.mSize = strlen(pSrc->mRight.mValue.s) + 1;
        } else {
            (*ppDst)->mRight.mSize = pSrc->mRight.mSize;
        }
        err = fn_8020D1B0(lbl_803EBE8C, (*ppDst)->mRight.mSize, &(*ppDst)->mRight.mValue.p);
        if (err == 0) {
            memcpy((*ppDst)->mRight.mValue.p, pSrc->mRight.mValue.p, (*ppDst)->mRight.mSize);
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        err = fn_80204D14(pSrc->mRight.mValue.p, (TDbExpr_801FAA00 **)&(*ppDst)->mRight.mValue.p);
        break;
    default:
        (*ppDst)->mRight.mValue = pSrc->mRight.mValue;
        err = 0;
        break;
    }
    (*ppDst)->mRight.mType = pSrc->mRight.mType;

    return err;
}

int fn_80204EF8(TDbExpr_801FAA00 *pSrc, TDbExpr_801FAA00 **ppDst, TDbTable_801FAA00 **ppTables, int tableCount,
                int flags)
{
    int err;
    int leftTrue;
    int rightTrue;
    unsigned int i;
    unsigned char column;
    unsigned long long value;
    TDbExpr_801FAA00 *pKeep;

    if (pSrc == 0) {
        *ppDst = 0;
        return 0;
    }
    if (flags && ((pSrc->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pSrc->mLeft.mType <= TDB_TYPE_EXPR_FLOAT)
                  || (pSrc->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pSrc->mRight.mType <= TDB_TYPE_EXPR_FLOAT))) {
        return 3;
    }
    err = fn_8020360C(&lbl_803E9654, ppDst);
    if (err) {
        return 2;
    }
    (*ppDst)->mLeft.mValue.l = 0;
    (*ppDst)->mRight.mValue.l = 0;
    leftTrue = rightTrue = 0;

    switch (pSrc->mLeft.mType) {
    case TDB_TYPE_STRING:
    case TDB_TYPE_BINARY:
        if (flags == 0) {
            if (pSrc->mLeft.mType == TDB_TYPE_STRING) {
                (*ppDst)->mLeft.mSize = strlen(pSrc->mLeft.mValue.s) + 1;
            } else {
                (*ppDst)->mLeft.mSize = pSrc->mLeft.mSize;
            }
            err = fn_8020D1B0(lbl_803EBE8C, (*ppDst)->mLeft.mSize, &(*ppDst)->mLeft.mValue.p);
            memcpy((*ppDst)->mLeft.mValue.p, pSrc->mLeft.mValue.p, (*ppDst)->mLeft.mSize);
            (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
            break;
        }
    case TDB_TYPE_COLUMN:
        for (i = 0; i < tableCount; i++) {
            if ((int)(pSrc->mLeft.mValue.l >> 32) == ppTables[i]->mUnknown1C) {
                column = fn_8020B97C(ppTables[i], (int)pSrc->mLeft.mValue.l);
                if (column == 0xFF) {
                    return 9;
                }
                (*ppDst)->mLeft.mValue.l = ((unsigned long long)i << 32) | column;
                (*ppDst)->mLeft.mType = TDB_TYPE_COLUMN;
                break;
            }
        }
        if (i >= tableCount) {
            err = 7;
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
        err = fn_80204EF8(pSrc->mLeft.mValue.p, (TDbExpr_801FAA00 **)&(*ppDst)->mLeft.mValue.p, ppTables, tableCount,
                          flags);
        if ((*ppDst)->mLeft.mValue.p == 0) {
            leftTrue = 1;
        }
        break;
    default:
        (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
        if (pSrc->mLeft.mType >= TDB_TYPE_RANGE_INT && pSrc->mLeft.mType <= TDB_TYPE_RANGE_FLOAT) {
            (*ppDst)->mLeft.mValue.l = pSrc->mLeft.mValue.l;
        } else {
            (*ppDst)->mLeft.mValue.u = pSrc->mLeft.mValue.u;
            leftTrue = pSrc->mLeft.mValue.u == 1;
        }
        err = 0;
        break;
    }

    (*ppDst)->mOp = pSrc->mOp;
    if (pSrc->mOp) {
        switch (pSrc->mRight.mType) {
        case TDB_TYPE_STRING:
        case TDB_TYPE_BINARY:
            if (flags == 0) {
                if (pSrc->mRight.mType == TDB_TYPE_STRING) {
                    (*ppDst)->mRight.mSize = strlen(pSrc->mRight.mValue.s) + 1;
                } else {
                    (*ppDst)->mRight.mSize = pSrc->mRight.mSize;
                }
                err = fn_8020D1B0(lbl_803EBE8C, (*ppDst)->mRight.mSize, &(*ppDst)->mRight.mValue.p);
                memcpy((*ppDst)->mRight.mValue.p, pSrc->mRight.mValue.p, (*ppDst)->mRight.mSize);
                (*ppDst)->mRight.mType = pSrc->mRight.mType;
            }
            break;
        case TDB_TYPE_COLUMN:
            for (i = 0; i < tableCount; i++) {
                if ((int)(pSrc->mRight.mValue.l >> 32) == ppTables[i]->mUnknown1C) {
                    column = fn_8020B97C(ppTables[i], (int)pSrc->mRight.mValue.l);
                    if (column == 0xFF) {
                        return 9;
                    }
                    value = ((unsigned long long)i << 32) | column;
                    (*ppDst)->mRight.mValue.l = value;
                    (*ppDst)->mRight.mType = TDB_TYPE_COLUMN;
                    if ((*ppDst)->mLeft.mType <= TDB_TYPE_FLOAT && ((*ppDst)->mOp & 0x30000)) {
                        (*ppDst)->mRight.mValue.l = (*ppDst)->mLeft.mValue.l;
                        (*ppDst)->mRight.mType = (*ppDst)->mLeft.mType;
                        (*ppDst)->mLeft.mValue.l = value;
                        (*ppDst)->mLeft.mType = TDB_TYPE_COLUMN;
                        (*ppDst)->mOp = pSrc->mOp == 0x10005 ? 0x10002
                                      : pSrc->mOp == 0x10004 ? 0x10001
                                      : pSrc->mOp == 0x10002 ? 0x10005
                                      : pSrc->mOp == 0x10001 ? 0x10004
                                      : (*ppDst)->mOp;
                    }
                    break;
                }
            }
            if (i >= tableCount) {
                err = 7;
            }
            break;
        case TDB_TYPE_EXPR_TRUNC:
        case TDB_TYPE_EXPR_UINT:
        case TDB_TYPE_EXPR_FLOAT:
            (*ppDst)->mRight.mType = pSrc->mRight.mType;
            err = fn_80204EF8(pSrc->mRight.mValue.p, (TDbExpr_801FAA00 **)&(*ppDst)->mRight.mValue.p, ppTables,
                              tableCount, flags);
            if ((*ppDst)->mRight.mValue.p == 0) {
                rightTrue = 1;
            }
            break;
        default:
            (*ppDst)->mRight.mType = pSrc->mRight.mType;
            if (pSrc->mRight.mType >= TDB_TYPE_RANGE_INT && pSrc->mRight.mType <= TDB_TYPE_RANGE_FLOAT) {
                (*ppDst)->mRight.mValue.l = pSrc->mRight.mValue.l;
            } else {
                (*ppDst)->mRight.mValue.u = pSrc->mRight.mValue.u;
                rightTrue = pSrc->mRight.mValue.u == 1;
            }
            err = 0;
            break;
        }
    } else {
        (*ppDst)->mRight.mType = 16;
        rightTrue = 1;
    }

    if (leftTrue || rightTrue) {
        if ((*ppDst)->mOp == 0x20009) {
            if (!rightTrue) {
                pKeep = (*ppDst)->mRight.mValue.p;
                fn_80203744(&lbl_803E9654, *ppDst);
                *ppDst = pKeep;
            } else if (!leftTrue) {
                pKeep = (*ppDst)->mLeft.mValue.p;
                fn_80203744(&lbl_803E9654, *ppDst);
                *ppDst = pKeep;
            } else {
                fn_80203744(&lbl_803E9654, *ppDst);
                *ppDst = 0;
            }
        } else if ((*ppDst)->mOp == 0x2000A) {
            if (!leftTrue) {
                fn_802055CC((*ppDst)->mLeft.mValue.p);
            } else if (!rightTrue) {
                fn_802055CC((*ppDst)->mRight.mValue.p);
            }
            fn_80203744(&lbl_803E9654, *ppDst);
            *ppDst = 0;
        } else {
            if (leftTrue) {
                (*ppDst)->mLeft.mType = TDB_TYPE_UINT;
                (*ppDst)->mLeft.mValue.u = 1;
            }
            if (rightTrue) {
                (*ppDst)->mRight.mType = TDB_TYPE_UINT;
                (*ppDst)->mRight.mValue.u = 1;
            }
        }
    }

    if ((*ppDst)->mLeft.mType == TDB_TYPE_COLUMN) {
        i = (*ppDst)->mLeft.mValue.l >> 32;
        column = (*ppDst)->mLeft.mValue.l;
        if (ppTables[i]->mColumns[column].mType == TDB_TYPE_UINT && (*ppDst)->mRight.mType <= TDB_TYPE_FLOAT) {
            if ((*ppDst)->mRight.mType == TDB_TYPE_INT) {
                (*ppDst)->mRight.mType = TDB_TYPE_UINT;
            }
            if ((*ppDst)->mRight.mValue.u == 0 && (*ppDst)->mOp == 0x10005) {
                fn_80203744(&lbl_803E9654, *ppDst);
                *ppDst = 0;
            }
        }
    }
    return err;
}

void fn_802055CC(TDbExpr_801FAA00 *pExpr)
{
    if (pExpr != 0) {
        if (pExpr->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mLeft.mType <= TDB_TYPE_EXPR_FLOAT) {
            fn_802055CC(pExpr->mLeft.mValue.p);
        } else if (pExpr->mLeft.mType <= TDB_TYPE_BINARY) {
            fn_8020D2AC(lbl_803EBE8C, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
        }
        if (pExpr->mOp) {
            if (pExpr->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mRight.mType <= TDB_TYPE_EXPR_FLOAT) {
                fn_802055CC(pExpr->mRight.mValue.p);
            } else if (pExpr->mRight.mType <= TDB_TYPE_BINARY) {
                fn_8020D2AC(lbl_803EBE8C, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
        }
        fn_80203744(&lbl_803E9654, pExpr);
    }
}

int fn_8020567C(TDbExpr_801FAA00 *pExpr, unsigned long long column)
{
    if (pExpr->mLeft.mType == TDB_TYPE_COLUMN && column == pExpr->mLeft.mValue.l) {
        return 1;
    }
    if (pExpr->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mLeft.mType <= TDB_TYPE_EXPR_FLOAT
        && fn_8020567C(pExpr->mLeft.mValue.p, column)) {
        return 1;
    }
    if (pExpr->mRight.mType == TDB_TYPE_COLUMN && column == pExpr->mRight.mValue.l) {
        return 1;
    }
    if (pExpr->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mRight.mType <= TDB_TYPE_EXPR_FLOAT
        && fn_8020567C(pExpr->mRight.mValue.p, column)) {
        return 1;
    }
    return 0;
}
