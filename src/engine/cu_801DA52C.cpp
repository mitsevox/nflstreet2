#include "engine/cu_801DA52C.h"

extern unsigned char *lbl_803ECF1C;
extern unsigned int lbl_803ECF20;
extern int lbl_803ECF24;
extern int lbl_8039A110[256];
extern unsigned char lbl_8039A910[512];
extern int lbl_8039AB10[64];
extern int lbl_803ECF28;
extern int lbl_803ECF2C;
extern int lbl_8039A210[64];
extern const int lbl_802B0E50[64];
extern int lbl_802F7BA0[64];

typedef struct Code_801DA52C {
    int mLength;
    int mValue;
    int mUnknown8;
    int mCode;
} Code_801DA52C;

extern int lbl_80399110[512];
extern int lbl_80399910[256];
extern int lbl_80399D10[256];
extern const Code_801DA52C lbl_802B0060[95];
extern const Code_801DA52C lbl_802B0650[128];


void fn_801DA52C(void)
{
    int i;
    int j;
    int v;
    int code;
    int length;
    int count;
    int index;
    int flags;
    int value;

    for (i = -256; i < 255; i++) {
        v = i;
        if (i < -128) {
            v = -128;
        } else if (i > 127) {
            v = 127;
        }
        lbl_8039A910[i & 0x1FF] = v - 128;
    }
    lbl_80399110[0] = 0x0F;
    for (i = 1; i < 8; i++) {
        lbl_80399110[i] = 0x1F;
    }
    for (i = 15; i >= 8; i--) {
        lbl_80399110[i] = 0x2F;
    }
    for (i = 383; i >= 256; i--) {
        lbl_80399110[i] = 0x3F;
    }
    for (i = 1; i < 95; i++) {
        const Code_801DA52C *pCode = &lbl_802B0060[i];

        length = pCode->mLength;
        flags = pCode->mCode;
        value = pCode->mValue;
        if (flags & 0xFC00) {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | length;
            count = 1 << (9 - length);
            index = flags >> 7;
            for (j = 0; j < count; j++) {
                lbl_80399110[index + j] = code;
            }
        } else {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 6);
            count = 1 << (14 - length);
            index = flags >> 2;
            for (j = 0; j < count; j++) {
                lbl_80399D10[index + j] = code;
            }
        }
    }
    for (i = 0; i < 128; i++) {
        const Code_801DA52C *pCode = &lbl_802B0650[i];

        length = pCode->mLength + 8;
        flags = pCode->mCode;
        value = pCode->mValue;
        if ((flags & 0x8000) == 0) {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 9);
            count = 1 << (17 - length);
            index = flags >> 7;
            for (j = 0; j < count; j++) {
                lbl_80399910[index + j] = code;
            }
        } else {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 6);
            count = 1 << (14 - length);
            index = flags >> 10;
            for (j = 0; j < count; j++) {
                lbl_80399D10[index + j] = code;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        lbl_8039A110[i] = 1;
    }
    for (; i < 48; i++) {
        lbl_8039A110[i] = ((i - 31) << 22) | 6;
        lbl_8039A110[i + 16] = ((i - 48) << 22) | 6;
    }
    lbl_803ECF28 = 1;
}

extern int lbl_8039A310[256];
extern int lbl_8039A710[64];
extern int lbl_8039A810[64];

void fn_801DA7E8(int count)
{
    lbl_803ECF20 <<= count;
    lbl_803ECF24 -= count;
    if (lbl_803ECF24 < 16) {
        lbl_803ECF20 |= ((lbl_803ECF1C[1] << 8) | lbl_803ECF1C[0]) << (16 - lbl_803ECF24);
        lbl_803ECF24 += 16;
        lbl_803ECF1C += 2;
    }
}

int fn_801DA840(void)
{
    int code = lbl_8039A110[lbl_803ECF20 >> 24];

    fn_801DA7E8(code & 0xFF);
    return code >> 22;
}

void fn_801DA884(int *pDst, int stride)
{
    int i;

    for (i = 0; i < 8; i++) {
        pDst[0] = lbl_8039AB10[0];
        pDst[1] = lbl_8039AB10[0];
        pDst[2] = lbl_8039AB10[0];
        pDst[3] = lbl_8039AB10[0];
        pDst[4] = lbl_8039AB10[0];
        pDst[5] = lbl_8039AB10[0];
        pDst[6] = lbl_8039AB10[0];
        pDst[7] = lbl_8039AB10[0];
        pDst += stride;
    }
}

void fn_801DA8E0(const unsigned char *pSrc, int stride, int *pDst, int bias)
{
    int i;

    if ((int)pSrc < 0) {
        for (i = 0; i < 8; i++) {
            pDst[0] = (pSrc[0] + bias) << 16;
            pDst[1] = (pSrc[1] + bias) << 16;
            pDst[2] = (pSrc[2] + bias) << 16;
            pDst[3] = (pSrc[3] + bias) << 16;
            pDst[4] = (pSrc[4] + bias) << 16;
            pDst[5] = (pSrc[5] + bias) << 16;
            pDst[6] = (pSrc[6] + bias) << 16;
            pDst[7] = (pSrc[7] + bias) << 16;
            pSrc += stride;
            pDst += 16;
        }
    }
}

void fn_801DA980(const unsigned char *pSrc, int stride, int *pDst, int bias)
{
    int i;

    if ((int)pSrc < 0) {
        for (i = 0; i < 8; i++) {
            pDst[0] = (pSrc[0] + bias) << 16;
            pDst[1] = (pSrc[1] + bias) << 16;
            pDst[2] = (pSrc[2] + bias) << 16;
            pDst[3] = (pSrc[3] + bias) << 16;
            pDst[4] = (pSrc[4] + bias) << 16;
            pDst[5] = (pSrc[5] + bias) << 16;
            pDst[6] = (pSrc[6] + bias) << 16;
            pDst[7] = (pSrc[7] + bias) << 16;
            pSrc += stride;
            pDst += 8;
        }
    }
}

void fn_801DAA20(const int *pSrc, unsigned char *pDst, int stride)
{
    int i;

    for (i = 0; i < 16; i++) {
        pDst[0] = lbl_8039A910[(pSrc[0] >> 16) & 0x1FF];
        pDst[1] = lbl_8039A910[(pSrc[1] >> 16) & 0x1FF];
        pDst[2] = lbl_8039A910[(pSrc[2] >> 16) & 0x1FF];
        pDst[3] = lbl_8039A910[(pSrc[3] >> 16) & 0x1FF];
        pDst[4] = lbl_8039A910[(pSrc[4] >> 16) & 0x1FF];
        pDst[5] = lbl_8039A910[(pSrc[5] >> 16) & 0x1FF];
        pDst[6] = lbl_8039A910[(pSrc[6] >> 16) & 0x1FF];
        pDst[7] = lbl_8039A910[(pSrc[7] >> 16) & 0x1FF];
        pDst[8] = lbl_8039A910[(pSrc[8] >> 16) & 0x1FF];
        pDst[9] = lbl_8039A910[(pSrc[9] >> 16) & 0x1FF];
        pDst[10] = lbl_8039A910[(pSrc[10] >> 16) & 0x1FF];
        pDst[11] = lbl_8039A910[(pSrc[11] >> 16) & 0x1FF];
        pDst[12] = lbl_8039A910[(pSrc[12] >> 16) & 0x1FF];
        pDst[13] = lbl_8039A910[(pSrc[13] >> 16) & 0x1FF];
        pDst[14] = lbl_8039A910[(pSrc[14] >> 16) & 0x1FF];
        pDst[15] = lbl_8039A910[(pSrc[15] >> 16) & 0x1FF];
        pSrc += 16;
        pDst += stride;
    }
}

void fn_801DAB40(const int *pSrc, unsigned char *pDst, int stride)
{
    int i;

    for (i = 0; i < 8; i++) {
        pDst[0] = lbl_8039A910[(pSrc[0] >> 16) & 0x1FF];
        pDst[1] = lbl_8039A910[(pSrc[1] >> 16) & 0x1FF];
        pDst[2] = lbl_8039A910[(pSrc[2] >> 16) & 0x1FF];
        pDst[3] = lbl_8039A910[(pSrc[3] >> 16) & 0x1FF];
        pDst[4] = lbl_8039A910[(pSrc[4] >> 16) & 0x1FF];
        pDst[5] = lbl_8039A910[(pSrc[5] >> 16) & 0x1FF];
        pDst[6] = lbl_8039A910[(pSrc[6] >> 16) & 0x1FF];
        pDst[7] = lbl_8039A910[(pSrc[7] >> 16) & 0x1FF];
        pSrc += 8;
        pDst += stride;
    }
}

void fn_801DABE0(const unsigned short *pData, int frame, int quant)
{
    const unsigned char *pBytes = (const unsigned char *)pData;
    int i;

    if (lbl_803ECF28 == 0) {
        fn_801DA52C();
    }
    lbl_803ECF20 = (((pBytes[1] << 8) | pBytes[0]) << 16) | ((pBytes[3] << 8) | pBytes[2]);
    lbl_803ECF24 = 32;
    lbl_803ECF1C = (unsigned char *)(pData + 2);
    lbl_803ECF2C = frame;
    lbl_8039A210[0] = (int)(((long long)(lbl_802B0E50[0] << 16) * lbl_802F7BA0[0] + 0x8000) >> 16);
    for (i = 1; i < 64; i++) {
        lbl_8039A210[i] = (int)(((long long)((quant * lbl_802B0E50[i]) << 13) * lbl_802F7BA0[i] + 0x8000) >> 16);
    }
}

void fn_801DAD20(const unsigned char *pRefY, const unsigned char *pRefU, const unsigned char *pRefV,
                 unsigned char *pDstY, unsigned char *pDstU, unsigned char *pDstV, int stride)
{
    int flags;
    int dx;
    int dy;
    int offset;
    int bias;
    int halfStride = stride >> 1;

    if (lbl_803ECF2C == 0) {
        flags = 0;
    } else if (!(lbl_803ECF20 & 0xC0000000)) {
        flags = 0;
        fn_801DA7E8(2);
    } else {
        if ((int)lbl_803ECF20 < 0) {
            flags = 0x3FF;
            fn_801DA7E8(1);
        } else {
            flags = lbl_803ECF20 >> 24;
            fn_801DA7E8(8);
        }
        dx = fn_801DA840();
        dy = fn_801DA840();
        pRefY += dy * stride + dx;
        dx >>= 1;
        dy >>= 1;
        offset = dy * halfStride + dx;
        pRefU += offset;
        pRefV += offset;
    }
    if ((flags & 1) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(&lbl_8039A310[0], 16);
        } else {
            fn_801DB670(&lbl_8039A310[0], 16);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA8E0(pRefY, stride, &lbl_8039A310[0], bias);
    }
    if ((flags & 2) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(&lbl_8039A310[8], 16);
        } else {
            fn_801DB670(&lbl_8039A310[8], 16);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA8E0(pRefY + 8, stride, &lbl_8039A310[8], bias);
    }
    if ((flags & 4) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(&lbl_8039A310[128], 16);
        } else {
            fn_801DB670(&lbl_8039A310[128], 16);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA8E0(pRefY + stride * 8, stride, &lbl_8039A310[128], bias);
    }
    if ((flags & 8) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(&lbl_8039A310[136], 16);
        } else {
            fn_801DB670(&lbl_8039A310[136], 16);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA8E0(pRefY + stride * 8 + 8, stride, &lbl_8039A310[136], bias);
    }
    if ((flags & 0x10) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(lbl_8039A710, 8);
        } else {
            fn_801DB670(lbl_8039A710, 8);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA980(pRefU, halfStride, lbl_8039A710, bias);
    }
    if ((flags & 0x20) == 0) {
        if (fn_801DB0B0() == 1) {
            fn_801DA884(lbl_8039A810, 8);
        } else {
            fn_801DB670(lbl_8039A810, 8);
        }
    } else {
        bias = fn_801DA840() * 2 - 128;
        fn_801DA980(pRefV, halfStride, lbl_8039A810, bias);
    }
    fn_801DAA20(lbl_8039A310, pDstY, stride);
    fn_801DAB40(lbl_8039A710, pDstU, halfStride);
    fn_801DAB40(lbl_8039A810, pDstV, halfStride);
}
