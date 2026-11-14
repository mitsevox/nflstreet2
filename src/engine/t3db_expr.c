/* T3DB filter expressions: the per-type operator functions (compare, logic, arithmetic) and the
   code that prepares, evaluates, copies and frees the expressions database queries and indexes filter by. */

#include <string.h>
#include "engine/t3db.h"


extern double fn_8025FBD4(double x);
typedef void (*TDbOpFunc_t)(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r);


static void _TDbOpNone(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = a->mType;
    r->mValue.i = a->mValue.i;
}

static void _TDbOpRelatLT_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == -1;
}

static void _TDbOpRelatLE_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != 1;
}

static void _TDbOpRelatEQ_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == 0;
}

static void _TDbOpRelatGT_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) == 1;
}

static void _TDbOpRelatGE_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != -1;
}

static void _TDbOpRelatNE_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = lbl_803EBE74(a->mValue.s, b->mValue.s, a->mSize) != 0;
}

static void _TDbOpLogicAND_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.s && a->mValue.s[0] && b->mValue.s && b->mValue.s[0];
}

static void _TDbOpLogicOR_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = (a->mValue.s && a->mValue.s[0]) || (b->mValue.s && b->mValue.s[0]);
}

static void _TDbOpLogicXOR_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.s && a->mValue.s[0];
    r->mValue.u ^= b->mValue.s && b->mValue.s[0];
}

static void _TDbOpLogicNOT_STRING(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = !a->mValue.s || !a->mValue.s[0];
}

static void _TDbOpRelatLT_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == -1;
}

static void _TDbOpRelatLE_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != 1;
}

static void _TDbOpRelatEQ_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == 0;
}

static void _TDbOpRelatGT_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) == 1;
}

static void _TDbOpRelatGE_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != -1;
}

static void _TDbOpRelatNE_BINARY(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = memcmp(a->mValue.p, b->mValue.p, a->mSize) != 0;
}

static void _TDbOpRelatLT_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i < b->mValue.i;
}

static void _TDbOpRelatLE_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i <= b->mValue.i;
}

static void _TDbOpRelatEQ_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i == b->mValue.i;
}

static void _TDbOpRelatGT_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i > b->mValue.i;
}

static void _TDbOpRelatGE_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i >= b->mValue.i;
}

static void _TDbOpRelatNE_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i != b->mValue.i;
}

static void _TDbOpRelatIR_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i >= (int)(b->mValue.l >> 32) && a->mValue.i <= (int)b->mValue.l;
}

static void _TDbOpRelatNR_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i < (int)(b->mValue.l >> 32) || a->mValue.i > (int)b->mValue.l;
}

static void _TDbOpLogicAND_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i && b->mValue.i;
}

static void _TDbOpLogicOR_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i || b->mValue.i;
}

static void _TDbOpLogicXOR_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.i != 0;
    r->mValue.u ^= b->mValue.i != 0;
}

static void _TDbOpLogicNOT_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = !a->mValue.i;
}

static void _TDbOpSMathADD_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i + b->mValue.i;
}

static void _TDbOpSMathSUB_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i - b->mValue.i;
}

static void _TDbOpSMathMUL_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i * b->mValue.i;
}

static void _TDbOpSMathDIV_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = b->mValue.i ? a->mValue.i / b->mValue.i : 0;
}

static void _TDbOpSMathPCT_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i * b->mValue.i / 100;
}

static void _TDbOpSMathMINOF_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i < b->mValue.i ? a->mValue.i : b->mValue.i;
}

static void _TDbOpSMathMAXOF_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = a->mValue.i > b->mValue.i ? a->mValue.i : b->mValue.i;
}

static void _TDbOpFMathFDIV_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.i ? (float)a->mValue.i / (float)b->mValue.i : 0.0f;
}

static void _TDbOpRelatLT_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < b->mValue.u;
}

static void _TDbOpRelatLE_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u <= b->mValue.u;
}

static void _TDbOpRelatGT_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u > b->mValue.u;
}

static void _TDbOpRelatGE_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u >= b->mValue.u;
}

static void _TDbOpRelatIR_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u >= (unsigned int)(b->mValue.l >> 32) && a->mValue.u <= (unsigned int)b->mValue.l;
}

static void _TDbOpRelatNR_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < (unsigned int)(b->mValue.l >> 32) || a->mValue.u > (unsigned int)b->mValue.l;
}

static void _TDbOpSMathADD_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u + b->mValue.u;
}

static void _TDbOpSMathSUB_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u - b->mValue.u;
}

static void _TDbOpSMathMUL_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u * b->mValue.u;
}

static void _TDbOpSMathDIV_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.u ? a->mValue.u / b->mValue.u : 0;
}

static void _TDbOpSMathPCT_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u * b->mValue.u / 100;
}

static void _TDbOpSMathMINOF_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u < b->mValue.u ? a->mValue.u : b->mValue.u;
}

static void _TDbOpSMathMAXOF_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u > b->mValue.u ? a->mValue.u : b->mValue.u;
}

static void _TDbOpBMathAND_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u & b->mValue.u;
}

static void _TDbOpBMathOR_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u | b->mValue.u;
}

static void _TDbOpBMathXOR_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.u ^ b->mValue.u;
}

static void _TDbOpBMathNOT_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = ~a->mValue.u;
}

static void _TDbOpFMathFDIV_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.u ? (float)a->mValue.u / (float)b->mValue.u : 0.0f;
}

static void _TDbOpRelatLT_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f < b->mValue.f;
}

static void _TDbOpRelatLE_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f <= b->mValue.f;
}

static void _TDbOpRelatGT_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f > b->mValue.f;
}

static void _TDbOpRelatGE_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f >= b->mValue.f;
}

static void _TDbOpRelatIR_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f >= (float)(unsigned int)(b->mValue.l >> 32)
               && a->mValue.f <= (float)(unsigned int)b->mValue.l;
}

static void _TDbOpRelatNR_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = a->mValue.f < (float)(unsigned int)(b->mValue.l >> 32)
               || a->mValue.f > (float)(unsigned int)b->mValue.l;
}

static void _TDbOpSMathADD_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f + b->mValue.f;
}

static void _TDbOpSMathSUB_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f - b->mValue.f;
}

static void _TDbOpSMathMUL_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f * b->mValue.f;
}

static void _TDbOpSMathDIV_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = b->mValue.f != 0.0f ? a->mValue.f / b->mValue.f : 0.0f;
}

static void _TDbOpSMathPCT_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f * b->mValue.f * 0.01f;
}

static void _TDbOpSMathMINOF_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f < b->mValue.f ? a->mValue.f : b->mValue.f;
}

static void _TDbOpSMathMAXOF_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = a->mValue.f > b->mValue.f ? a->mValue.f : b->mValue.f;
}

static void _TDbOpFMathROUND_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_INT;
    r->mValue.i = (int)(a->mValue.f + 0.5f);
}

static void _TDbOpFMathSQRT_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_FLOAT;
    r->mValue.f = fn_8025FBD4(a->mValue.f);
}

static void _TDbOpFMathMKPCT_FLOAT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.f != 0.0f ? (unsigned int)(a->mValue.f * 100.0f / b->mValue.f) : 0;
}

static void _TDbOpFMathMKPCT_INT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.i ? (unsigned int)((float)a->mValue.i * 100.0f / (float)b->mValue.i) : 0;
}

static void _TDbOpFMathMKPCT_UINT(TDbValue_t *a, TDbValue_t *b, TDbValue_t *r)
{
    r->mType = TDB_TYPE_UINT;
    r->mValue.u = b->mValue.u ? (unsigned int)((float)a->mValue.u * 100.0f / (float)b->mValue.u) : 0;
}

static TDbOpFunc_t _tDbExprGrid[28][5] = {
    { _TDbOpNone, _TDbOpNone, _TDbOpNone, _TDbOpNone, _TDbOpNone },
    { _TDbOpRelatLT_STRING, _TDbOpRelatLT_BINARY, _TDbOpRelatLT_INT, _TDbOpRelatLT_UINT, _TDbOpRelatLT_FLOAT },
    { _TDbOpRelatLE_STRING, _TDbOpRelatLE_BINARY, _TDbOpRelatLE_INT, _TDbOpRelatLE_UINT, _TDbOpRelatLE_FLOAT },
    { _TDbOpRelatEQ_STRING, _TDbOpRelatEQ_BINARY, _TDbOpRelatEQ_INT, _TDbOpRelatEQ_INT, _TDbOpRelatEQ_INT },
    { _TDbOpRelatGT_STRING, _TDbOpRelatGT_BINARY, _TDbOpRelatGT_INT, _TDbOpRelatGT_UINT, _TDbOpRelatGT_FLOAT },
    { _TDbOpRelatGE_STRING, _TDbOpRelatGE_BINARY, _TDbOpRelatGE_INT, _TDbOpRelatGE_UINT, _TDbOpRelatGE_FLOAT },
    { _TDbOpRelatNE_STRING, _TDbOpRelatNE_BINARY, _TDbOpRelatNE_INT, _TDbOpRelatNE_INT, _TDbOpRelatNE_INT },
    { 0, 0, _TDbOpRelatIR_INT, _TDbOpRelatIR_UINT, _TDbOpRelatIR_FLOAT },
    { 0, 0, _TDbOpRelatNR_INT, _TDbOpRelatNR_UINT, _TDbOpRelatNR_FLOAT },
    { _TDbOpLogicAND_STRING, 0, _TDbOpLogicAND_INT, _TDbOpLogicAND_INT, _TDbOpLogicAND_INT },
    { _TDbOpLogicOR_STRING, 0, _TDbOpLogicOR_INT, _TDbOpLogicOR_INT, _TDbOpLogicOR_INT },
    { _TDbOpLogicXOR_STRING, 0, _TDbOpLogicXOR_INT, _TDbOpLogicXOR_INT, _TDbOpLogicXOR_INT },
    { _TDbOpLogicNOT_STRING, 0, _TDbOpLogicNOT_INT, _TDbOpLogicNOT_INT, _TDbOpLogicNOT_INT },
    { 0, 0, _TDbOpSMathADD_INT, _TDbOpSMathADD_UINT, _TDbOpSMathADD_FLOAT },
    { 0, 0, _TDbOpSMathSUB_INT, _TDbOpSMathSUB_UINT, _TDbOpSMathSUB_FLOAT },
    { 0, 0, _TDbOpSMathDIV_INT, _TDbOpSMathDIV_UINT, _TDbOpSMathDIV_FLOAT },
    { 0, 0, _TDbOpSMathMUL_INT, _TDbOpSMathMUL_UINT, _TDbOpSMathMUL_FLOAT },
    { 0, 0, _TDbOpSMathPCT_INT, _TDbOpSMathPCT_UINT, _TDbOpSMathPCT_FLOAT },
    { 0, 0, _TDbOpSMathMINOF_INT, _TDbOpSMathMINOF_UINT, _TDbOpSMathMINOF_FLOAT },
    { 0, 0, _TDbOpSMathMAXOF_INT, _TDbOpSMathMAXOF_UINT, _TDbOpSMathMAXOF_FLOAT },
    { 0, 0, _TDbOpBMathAND_UINT, _TDbOpBMathAND_UINT, 0 },
    { 0, 0, _TDbOpBMathOR_UINT, _TDbOpBMathOR_UINT, 0 },
    { 0, 0, _TDbOpBMathXOR_UINT, _TDbOpBMathXOR_UINT, 0 },
    { 0, 0, _TDbOpBMathNOT_UINT, _TDbOpBMathNOT_UINT, 0 },
    { 0, 0, _TDbOpFMathFDIV_INT, _TDbOpFMathFDIV_UINT, _TDbOpSMathDIV_FLOAT },
    { 0, 0, 0, 0, _TDbOpFMathROUND_FLOAT },
    { 0, 0, 0, 0, _TDbOpFMathSQRT_FLOAT },
    { 0, 0, _TDbOpFMathMKPCT_INT, _TDbOpFMathMKPCT_UINT, _TDbOpFMathMKPCT_FLOAT },
};

/* Resolve row columns and nested conversions before dispatching the
   typed operator; a missing expression supplies the true value. */
void _TDbExprTest(TDbExpr_t *pExpr, TDbValue_t *pResult, TDbTable_t **ppTables,
                 unsigned short *pRows)
{
    TDbValue_t left;
    TDbValue_t right;
    TDbTable_t *pTable;
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
                _TDbDataGetBitData((unsigned int *)pRow, pTable->mColumns[columnIndex].mBitOffset,
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
        _TDbExprTest(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
        if (left.mType == TDB_TYPE_FLOAT) {
            left.mValue.i = (int)left.mValue.f;
        }
        left.mType = TDB_TYPE_UINT;
        break;
    case TDB_TYPE_EXPR_UINT:
        _TDbExprTest(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
        if (left.mType == TDB_TYPE_FLOAT) {
            left.mValue.u = (unsigned int)left.mValue.f;
        }
        left.mType = TDB_TYPE_UINT;
        break;
    case TDB_TYPE_EXPR_FLOAT:
        _TDbExprTest(pExpr->mLeft.mValue.p, &left, ppTables, pRows);
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
                    _TDbDataGetBitData((unsigned int *)pRow, pTable->mColumns[columnIndex].mBitOffset,
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
            _TDbExprTest(pExpr->mRight.mValue.p, &right, ppTables, pRows);
            if (right.mType == TDB_TYPE_FLOAT) {
                right.mValue.i = (int)right.mValue.f;
            }
            right.mType = TDB_TYPE_UINT;
            break;
        case TDB_TYPE_EXPR_UINT:
            _TDbExprTest(pExpr->mRight.mValue.p, &right, ppTables, pRows);
            if (right.mType == TDB_TYPE_FLOAT) {
                right.mValue.u = (unsigned int)right.mValue.f;
            }
            right.mType = TDB_TYPE_UINT;
            break;
        case TDB_TYPE_EXPR_FLOAT:
            _TDbExprTest(pExpr->mRight.mValue.p, &right, ppTables, pRows);
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

    _tDbExprGrid[(unsigned short)pExpr->mOp][left.mType](&left, &right, pResult);
}

int _TDbExprCopy(TDbExpr_t *pSrc, TDbExpr_t **ppDst)
{
    int err;

    if (pSrc == 0) {
        *ppDst = 0;
        return 0;
    }
    if (__TDbMemPoolAlloc(&lbl_803E9654, ppDst)) {
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
        err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mLeft.mSize, &(*ppDst)->mLeft.mValue.p);
        if (err == 0) {
            memcpy((*ppDst)->mLeft.mValue.p, pSrc->mLeft.mValue.p, (*ppDst)->mLeft.mSize);
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        err = _TDbExprCopy(pSrc->mLeft.mValue.p, (TDbExpr_t **)&(*ppDst)->mLeft.mValue.p);
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
        err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mRight.mSize, &(*ppDst)->mRight.mValue.p);
        if (err == 0) {
            memcpy((*ppDst)->mRight.mValue.p, pSrc->mRight.mValue.p, (*ppDst)->mRight.mSize);
        }
        break;
    case TDB_TYPE_EXPR_TRUNC:
    case TDB_TYPE_EXPR_UINT:
    case TDB_TYPE_EXPR_FLOAT:
        err = _TDbExprCopy(pSrc->mRight.mValue.p, (TDbExpr_t **)&(*ppDst)->mRight.mValue.p);
        break;
    default:
        (*ppDst)->mRight.mValue = pSrc->mRight.mValue;
        err = 0;
        break;
    }
    (*ppDst)->mRight.mType = pSrc->mRight.mType;

    return err;
}

/* Copy an expression into the supplied table context, resolve column
   identifiers, and simplify true branches while preparing comparisons. */
int _TDbExprPrepare(TDbExpr_t *pSrc, TDbExpr_t **ppDst, TDbTable_t **ppTables, int tableCount,
                int flags)
{
    int err;
    int leftTrue;
    int rightTrue;
    unsigned int i;
    unsigned char column;
    unsigned long long value;
    TDbExpr_t *pKeep;

    if (pSrc == 0) {
        *ppDst = 0;
        return 0;
    }
    if (flags && ((pSrc->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pSrc->mLeft.mType <= TDB_TYPE_EXPR_FLOAT)
                  || (pSrc->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pSrc->mRight.mType <= TDB_TYPE_EXPR_FLOAT))) {
        return 3;
    }
    err = __TDbMemPoolAlloc(&lbl_803E9654, ppDst);
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
            err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mLeft.mSize, &(*ppDst)->mLeft.mValue.p);
            memcpy((*ppDst)->mLeft.mValue.p, pSrc->mLeft.mValue.p, (*ppDst)->mLeft.mSize);
            (*ppDst)->mLeft.mType = pSrc->mLeft.mType;
            break;
        }
    case TDB_TYPE_COLUMN:
        for (i = 0; i < tableCount; i++) {
            if ((int)(pSrc->mLeft.mValue.l >> 32) == ppTables[i]->mId) {
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
        err = _TDbExprPrepare(pSrc->mLeft.mValue.p, (TDbExpr_t **)&(*ppDst)->mLeft.mValue.p, ppTables, tableCount,
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
                err = TDbExtMemAlloc(_tDbGlobalMemoryHeapID, (*ppDst)->mRight.mSize, &(*ppDst)->mRight.mValue.p);
                memcpy((*ppDst)->mRight.mValue.p, pSrc->mRight.mValue.p, (*ppDst)->mRight.mSize);
                (*ppDst)->mRight.mType = pSrc->mRight.mType;
            }
            break;
        case TDB_TYPE_COLUMN:
            for (i = 0; i < tableCount; i++) {
                if ((int)(pSrc->mRight.mValue.l >> 32) == ppTables[i]->mId) {
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
            err = _TDbExprPrepare(pSrc->mRight.mValue.p, (TDbExpr_t **)&(*ppDst)->mRight.mValue.p, ppTables,
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
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = pKeep;
            } else if (!leftTrue) {
                pKeep = (*ppDst)->mLeft.mValue.p;
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = pKeep;
            } else {
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = 0;
            }
        } else if ((*ppDst)->mOp == 0x2000A) {
            if (!leftTrue) {
                _TDbExprFree((*ppDst)->mLeft.mValue.p);
            } else if (!rightTrue) {
                _TDbExprFree((*ppDst)->mRight.mValue.p);
            }
            __TDbMemPoolFree(&lbl_803E9654, *ppDst);
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
                __TDbMemPoolFree(&lbl_803E9654, *ppDst);
                *ppDst = 0;
            }
        }
    }
    return err;
}

void _TDbExprFree(TDbExpr_t *pExpr)
{
    if (pExpr != 0) {
        if (pExpr->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mLeft.mType <= TDB_TYPE_EXPR_FLOAT) {
            _TDbExprFree(pExpr->mLeft.mValue.p);
        } else if (pExpr->mLeft.mType <= TDB_TYPE_BINARY) {
            TDbExtMemFree(_tDbGlobalMemoryHeapID, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
        }
        if (pExpr->mOp) {
            if (pExpr->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mRight.mType <= TDB_TYPE_EXPR_FLOAT) {
                _TDbExprFree(pExpr->mRight.mValue.p);
            } else if (pExpr->mRight.mType <= TDB_TYPE_BINARY) {
                TDbExtMemFree(_tDbGlobalMemoryHeapID, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
        }
        __TDbMemPoolFree(&lbl_803E9654, pExpr);
    }
}

int _TDbExprFindTableCol(TDbExpr_t *pExpr, unsigned long long column)
{
    if (pExpr->mLeft.mType == TDB_TYPE_COLUMN && column == pExpr->mLeft.mValue.l) {
        return 1;
    }
    if (pExpr->mLeft.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mLeft.mType <= TDB_TYPE_EXPR_FLOAT
        && _TDbExprFindTableCol(pExpr->mLeft.mValue.p, column)) {
        return 1;
    }
    if (pExpr->mRight.mType == TDB_TYPE_COLUMN && column == pExpr->mRight.mValue.l) {
        return 1;
    }
    if (pExpr->mRight.mType >= TDB_TYPE_EXPR_TRUNC && pExpr->mRight.mType <= TDB_TYPE_EXPR_FLOAT
        && _TDbExprFindTableCol(pExpr->mRight.mValue.p, column)) {
        return 1;
    }
    return 0;
}
