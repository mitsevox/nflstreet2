#include "engine/t3db.h"



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
