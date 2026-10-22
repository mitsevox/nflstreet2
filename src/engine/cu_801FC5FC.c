#include <string.h>
#include "engine/t3db.h"

typedef struct TDbIOFileHdr_801FC5FC {
    unsigned char mMagic[2];
    unsigned char mUnknown2;
    unsigned char mVersion;
    unsigned char mUnknown4;
    unsigned int mEnd;
    unsigned int mBase;
} TDbIOFileHdr_801FC5FC;

int fn_801FC5FC(TDbDatabase_801FAA00 *pDb, void *pName, TDbIODevice_801FC5FC *pDevice)
{
    TDbIOFileHdr_801FC5FC hdr;
    TDbIOStream_801FA8C8 stream;
    TDbTable_801FAA00 *pTable;
    unsigned int *pOffsets;
    unsigned int count;
    unsigned int n;
    unsigned int done;
    unsigned int base;
    int err;

    TDbMemNotify_801FC9D4(1, (int)pDb->mUnknown8, -1);
    memset(&hdr, 0, sizeof(hdr));
    count = 0;
    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
        if (pTable->mFlags & 2) {
            count++;
        }
    }
    pOffsets = 0;
    err = fn_8020D1B0(lbl_803EBE8C, count * 8, &pOffsets);
    if (err != 0) {
        pOffsets = 0;
    }
    stream.mSize = fn_801FAA00(pDb, pOffsets) + (0x1C + count * 8);
    base = pDevice->mReserve(stream.mSize);
    hdr.mBase = base;
    stream.mEnd = hdr.mEnd = stream.mSize + base;
    stream.mUnknownC = 0;
    stream.mCrcB = -1;
    stream.mDevice = pDevice;
    stream.mCrcA = -1;
    stream.mOffset = 0;
    if (err == 0) {
        err = pDevice->mOpen(stream.mHandle, stream.mSize, pName, 0);
    }
    if (err == 0) {
        hdr.mMagic[0] = 'D';
        hdr.mMagic[1] = 'B';
        hdr.mUnknown2 = 0;
        hdr.mVersion = 8;
        hdr.mUnknown4 = 1;
        n = count;
        err = fn_801FA8C8(&stream, &hdr, sizeof(hdr));
        if (err == 0) {
            err = fn_801FA8C8(&stream, &n, 4);
            if (err == 0) {
                err = pDevice->mWrite(stream.mHandle, &stream.mCrcA, 4, &done);
                if (err == 0) {
                    if (done == 4) {
                        stream.mOffset += 4;
                    } else {
                        err = 0x24;
                    }
                }
            }
        }
        stream.mCrcA = -1;
        if (err == 0) {
            err = fn_801FA8C8(&stream, pOffsets, count * 8);
            fn_8020D2AC(lbl_803EBE8C, pOffsets, count * 8);
            pOffsets = 0;
            if (err == 0) {
                err = pDevice->mWrite(stream.mHandle, &stream.mCrcA, 4, &done);
                if (err == 0) {
                    if (done == 4) {
                        stream.mOffset += 4;
                    } else {
                        err = 0x24;
                    }
                }
                if (err == 0) {
                    for (pTable = pDb->mTables; pTable != 0; pTable = pTable->mNext) {
                        if ((pTable->mFlags & 2) && (err = fn_801FBD2C(pTable, &stream)) != 0) {
                            break;
                        }
                    }
                }
            }
        }
        if (pOffsets) {
            fn_8020D2AC(lbl_803EBE8C, pOffsets, count * 8);
            pOffsets = 0;
        }
        if (err == 0) {
            err = pDevice->mClose(stream.mHandle);
        } else {
            pDevice->mClose(stream.mHandle);
        }
    } else if (pOffsets) {
        fn_8020D2AC(lbl_803EBE8C, pOffsets, count * 8);
    }
    TDbMemNotify_801FC9D4(4, -1, -1);
    return err;
}

unsigned int fn_801FC950(void *pData, unsigned int size, unsigned int crc)
{
    unsigned char *p;

    if (lbl_802F9548[1] == 0) {
        fn_801FA870();
        crc = -1;
    }
    for (p = pData; size != 0; size--) {
        crc = (crc << 8) ^ lbl_802F9548[(crc >> 24) ^ *p++];
    }
    return crc;
}
