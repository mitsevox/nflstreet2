#include <string.h>
#include "engine/t3db.h"



int fn_801FB9D0(TDbExpr_801FAA00 *pExpr, TDbIOStream_801FA8C8 *pStream, int release)
{
    int err;

    err = fn_801FA964(pStream, pExpr, sizeof(TDbExpr_801FAA00));
    if (err == 0) {
        if (pExpr->mLeft.mType <= TDB_TYPE_BINARY) {
            err = fn_8020D1B0(lbl_803EBE8C, pExpr->mLeft.mSize, &pExpr->mLeft.mValue.p);
            if (err == 0) {
                err = fn_801FA964(pStream, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
            }
            if (release) {
                fn_8020D2AC(lbl_803EBE8C, pExpr->mLeft.mValue.p, pExpr->mRight.mSize);
            }
        }
        if (pExpr->mRight.mType <= TDB_TYPE_BINARY && err == 0) {
            err = fn_8020D1B0(lbl_803EBE8C, pExpr->mRight.mSize, &pExpr->mRight.mValue.p);
            if (err == 0) {
                err = fn_801FA964(pStream, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
            if (release) {
                fn_8020D2AC(lbl_803EBE8C, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
            }
        }
    }
    return err;
}

int fn_801FBAC4(TDbTable_801FAA00 *pTable, TDbExpr_801FAA00 *pExpr, TDbIOStream_801FA8C8 *pStream)
{
    TDbExpr_801FAA00 expr;
    int err;

    expr = *pExpr;
    if (expr.mLeft.mType == TDB_TYPE_COLUMN) {
        expr.mLeft.mValue.l = (unsigned long long)pTable->mUnknown1C << 32 |
                              pTable->mColumns[(unsigned char)expr.mLeft.mValue.l].mUnknown8;
    }
    if (expr.mRight.mType == TDB_TYPE_COLUMN) {
        expr.mRight.mValue.l = (unsigned long long)pTable->mUnknown1C << 32 |
                               pTable->mColumns[(unsigned char)expr.mRight.mValue.l].mUnknown8;
    }
    err = fn_801FA8C8(pStream, &expr, sizeof(expr));
    if (pExpr->mLeft.mType <= TDB_TYPE_BINARY && err == 0) {
        err = fn_801FA8C8(pStream, pExpr->mLeft.mValue.p, pExpr->mLeft.mSize);
    }
    if (pExpr->mRight.mType <= TDB_TYPE_BINARY && err == 0) {
        err = fn_801FA8C8(pStream, pExpr->mRight.mValue.p, pExpr->mRight.mSize);
    }
    return err;
}

int fn_801FBC2C(TDbIndex_801FAA00 *pIndex, TDbIOStream_801FA8C8 *pStream)
{
    TDbIOIndexHdr_801FBC2C hdr;
    TDbIOIndexPart_801FBC2C part;
    unsigned char count;
    unsigned char i;
    int err;

    memset(&hdr, 0, sizeof(hdr));
    hdr.mId = pIndex->mId;
    count = pIndex->mTree.mPartCount;
    hdr.mAllowDuplicates = pIndex->mTree.mAllowDuplicates;
    hdr.mPartCount = count;
    hdr.mHasFilter = pIndex->mFilter != 0;
    err = fn_801FA8C8(pStream, &hdr, sizeof(hdr));
    if (err == 0) {
        for (i = 0; i < count; i++) {
            part.mColumn = pIndex->mTree.mParts[i].mColumn;
            part.mAscending = pIndex->mTree.mParts[i].mAscending;
            err = fn_801FA8C8(pStream, &part, sizeof(part));
            if (err != 0) {
                break;
            }
        }
    }
    if (hdr.mHasFilter && err == 0) {
        err = fn_801FBAC4(pIndex->mTable, pIndex->mFilter, pStream);
    }
    return err;
}

int fn_801FBD2C(TDbTable_801FAA00 *pTable, TDbIOStream_801FA8C8 *pStream)
{
    TDbIOTableHdr_801FAAF8 hdr;
    unsigned int done;
    unsigned char pad[8];
    TDbIndex_801FAA00 *pIndex;
    int rows;
    int err;

    memset(&hdr, 0, sizeof(hdr));
    hdr.mFlags = pTable->mFlags;
    hdr.mRowSize = pTable->mRowSize;
    hdr.mDeletedBit = pTable->mDeletedBit;
    hdr.mDataSize = pTable->mUnknown2C;
    if ((hdr.mFlags & 8) && pTable->mCapacity == 0) {
        hdr.mFlags |= 0x10;
        hdr.mUnknown10 = pTable->mUnknown40;
        rows = 0;
    } else {
        hdr.mFlags &= ~0x10;
        hdr.mUnknown10 = pTable->mCapacity;
        rows = 1;
    }
    hdr.mRowCount = pTable->mRowCount;
    hdr.mUnknown14 = pTable->mUnknown46;
    hdr.mUnknown16 = pTable->mUnknown48;
    hdr.mColumnCount = pTable->mColumnCount;
    hdr.mIndexCount = 0;
    for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
        if (pIndex->mDestroyed == 0) {
            hdr.mIndexCount++;
        }
    }
    pStream->mCrcB = -1;
    err = fn_801FA8C8(pStream, &hdr, sizeof(hdr));
    if (err == 0) {
        err = pStream->mDevice->mWrite(pStream->mHandle, &pStream->mCrcB, 4, &done);
        if (err == 0) {
            if (done != 4) {
                err = 0x24;
            } else {
                pStream->mOffset += 4;
            }
        }
    }
    pStream->mCrcB = -1;
    if (err == 0) {
        err = fn_801FA8C8(pStream, pTable->mColumns, pTable->mColumnCount * sizeof(TDbColumn_801FAA00));
    }
    if (rows == 1 && err == 0 && pTable->mCapacity != 0) {
        err = fn_801FA8C8(pStream, pTable->mRows, pTable->mRowSize * pTable->mCapacity);
    }
    if (err == 0) {
        if ((pTable->mFlags & 0x60) && pTable->mUnknown2C != 0) {
            err = fn_801FA8C8(pStream, pTable->mUnknown18, pTable->mUnknown2C);
            if (err == 0 && (pTable->mUnknown2C & 7)) {
                memset(pad, 0, sizeof(pad));
                err = fn_801FA8C8(pStream, pad, 8 - (pTable->mUnknown2C & 7));
            }
        }
        if (err == 0) {
            for (pIndex = pTable->mIndexes; pIndex != 0; pIndex = pIndex->mNext) {
                if (pIndex->mDestroyed == 0) {
                    err = fn_801FBC2C(pIndex, pStream);
                    if (err != 0) {
                        break;
                    }
                }
            }
            if (err == 0) {
                err = pStream->mDevice->mWrite(pStream->mHandle, &pStream->mCrcB, 4, &done);
                if (err == 0) {
                    if (done != 4) {
                        err = 0x24;
                    } else {
                        pStream->mOffset += 4;
                    }
                }
            }
        }
    }
    return err;
}
