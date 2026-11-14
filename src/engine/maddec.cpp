/* MAD video decoder used by the start-up movies: builds the decoder's lookup tables, reads
   the compressed bit stream and decodes each 16x16 macroblock of a frame into the Y, U and V
   planes, either from coded coefficients or by copying the motion-shifted previous frame. */

#include "engine/maddec.h"

/* One entry of the variable-length code tables read by madinit. */
typedef struct MadCode_t {
    int mLength;
    int mValue;
    int mUnknown8;
    int mCode;
} MadCode_t;

unsigned char *maddataptr;
unsigned int madshiftreg;
int madbitcount;
static int initflag;
static int motionframe;

int madvlctbl1[512];
int madvlctbl2[256];
int madvlctbl3[256];
int madvlctbl4[64];
int madquant[64];
static int luma[256];
static int madchroma[2][64];
static unsigned char clipbiastbl[512];
int idctinput[64];

#if defined(DECOMP_COMPARE)
static const MadCode_t encodetbl1[95] = {
    {2, 65024, 0, 0x8000},
    {3, 1, 0, 0xC000},
    {3, 1023, 0, 0xE000},
    {4, 1025, 0, 0x6000},
    {4, 2047, 0, 0x7000},
    {5, 2, 0, 0x4000},
    {5, 1022, 0, 0x4800},
    {5, 2049, 0, 0x5000},
    {5, 3071, 0, 0x5800},
    {6, 3, 0, 0x2800},
    {6, 1021, 0, 0x2C00},
    {6, 3073, 0, 0x3800},
    {6, 4095, 0, 0x3C00},
    {6, 4097, 0, 0x3000},
    {6, 5119, 0, 0x3400},
    {7, 1026, 0, 0x1800},
    {7, 2046, 0, 0x1A00},
    {7, 5121, 0, 0x1C00},
    {7, 6143, 0, 0x1E00},
    {7, 6145, 0, 0x1400},
    {7, 7167, 0, 0x1600},
    {7, 7169, 0, 0x1000},
    {7, 8191, 0, 0x1200},
    {8, 4, 0, 0xC00},
    {8, 1020, 0, 0xD00},
    {8, 2050, 0, 0x800},
    {8, 3070, 0, 0x900},
    {8, 8193, 0, 0xE00},
    {8, 9215, 0, 0xF00},
    {8, 9217, 0, 0xA00},
    {8, 10239, 0, 0xB00},
    {9, 5, 0, 0x2600},
    {9, 1019, 0, 0x2680},
    {9, 6, 0, 0x2100},
    {9, 1018, 0, 0x2180},
    {9, 1027, 0, 0x2500},
    {9, 2045, 0, 0x2580},
    {9, 3074, 0, 0x2400},
    {9, 4094, 0, 0x2480},
    {9, 10241, 0, 0x2700},
    {9, 11263, 0, 0x2780},
    {9, 11265, 0, 0x2300},
    {9, 12287, 0, 0x2380},
    {9, 12289, 0, 0x2200},
    {9, 13311, 0, 0x2280},
    {9, 13313, 0, 0x2000},
    {9, 14335, 0, 0x2080},
    {11, 7, 0, 0x280},
    {11, 1017, 0, 0x2A0},
    {11, 1028, 0, 0x300},
    {11, 2044, 0, 0x320},
    {11, 2051, 0, 0x2C0},
    {11, 3069, 0, 0x2E0},
    {11, 4098, 0, 0x3C0},
    {11, 5118, 0, 0x3E0},
    {11, 5122, 0, 0x240},
    {11, 6142, 0, 0x260},
    {11, 14337, 0, 0x380},
    {11, 15359, 0, 0x3A0},
    {11, 15361, 0, 0x340},
    {11, 16383, 0, 0x360},
    {11, 16385, 0, 0x200},
    {11, 17407, 0, 0x220},
    {13, 8, 0, 0x1D0},
    {13, 1016, 0, 0x1D8},
    {13, 9, 0, 0x180},
    {13, 1015, 0, 0x188},
    {13, 10, 0, 0x130},
    {13, 1014, 0, 0x138},
    {13, 11, 0, 0x100},
    {13, 1013, 0, 0x108},
    {13, 1029, 0, 0x1B0},
    {13, 2043, 0, 0x1B8},
    {13, 2052, 0, 0x140},
    {13, 3068, 0, 0x148},
    {13, 3075, 0, 0x1C0},
    {13, 4093, 0, 0x1C8},
    {13, 4099, 0, 0x120},
    {13, 5117, 0, 0x128},
    {13, 6146, 0, 0x1E0},
    {13, 7166, 0, 0x1E8},
    {13, 7170, 0, 0x150},
    {13, 8190, 0, 0x158},
    {13, 8194, 0, 0x110},
    {13, 9214, 0, 0x118},
    {13, 17409, 0, 0x1F0},
    {13, 18431, 0, 0x1F8},
    {13, 18433, 0, 0x1A0},
    {13, 19455, 0, 0x1A8},
    {13, 19457, 0, 0x190},
    {13, 20479, 0, 0x198},
    {13, 20481, 0, 0x170},
    {13, 21503, 0, 0x178},
    {13, 21505, 0, 0x160},
    {13, 22527, 0, 0x168},
};

static const MadCode_t encodetbl2[128] = {
    {6, 12, 0, 0xD000},
    {6, 1012, 0, 0xD400},
    {6, 13, 0, 0xC800},
    {6, 1011, 0, 0xCC00},
    {6, 14, 0, 0xC000},
    {6, 1010, 0, 0xC400},
    {6, 15, 0, 0xB800},
    {6, 1009, 0, 0xBC00},
    {6, 1030, 0, 0xB000},
    {6, 2042, 0, 0xB400},
    {6, 1031, 0, 0xA800},
    {6, 2041, 0, 0xAC00},
    {6, 2053, 0, 0xA000},
    {6, 3067, 0, 0xA400},
    {6, 3076, 0, 0x9800},
    {6, 4092, 0, 0x9C00},
    {6, 5123, 0, 0x9000},
    {6, 6141, 0, 0x9400},
    {6, 9218, 0, 0x8800},
    {6, 10238, 0, 0x8C00},
    {6, 10242, 0, 0x8000},
    {6, 11262, 0, 0x8400},
    {6, 22529, 0, 0xF800},
    {6, 23551, 0, 0xFC00},
    {6, 23553, 0, 0xF000},
    {6, 24575, 0, 0xF400},
    {6, 24577, 0, 0xE800},
    {6, 25599, 0, 0xEC00},
    {6, 25601, 0, 0xE000},
    {6, 26623, 0, 0xE400},
    {6, 26625, 0, 0xD800},
    {6, 27647, 0, 0xDC00},
    {7, 16, 0, 0x7C00},
    {7, 1008, 0, 0x7E00},
    {7, 17, 0, 0x7800},
    {7, 1007, 0, 0x7A00},
    {7, 18, 0, 0x7400},
    {7, 1006, 0, 0x7600},
    {7, 19, 0, 0x7000},
    {7, 1005, 0, 0x7200},
    {7, 20, 0, 0x6C00},
    {7, 1004, 0, 0x6E00},
    {7, 21, 0, 0x6800},
    {7, 1003, 0, 0x6A00},
    {7, 22, 0, 0x6400},
    {7, 1002, 0, 0x6600},
    {7, 23, 0, 0x6000},
    {7, 1001, 0, 0x6200},
    {7, 24, 0, 0x5C00},
    {7, 1000, 0, 0x5E00},
    {7, 25, 0, 0x5800},
    {7, 999, 0, 0x5A00},
    {7, 26, 0, 0x5400},
    {7, 998, 0, 0x5600},
    {7, 27, 0, 0x5000},
    {7, 997, 0, 0x5200},
    {7, 28, 0, 0x4C00},
    {7, 996, 0, 0x4E00},
    {7, 29, 0, 0x4800},
    {7, 995, 0, 0x4A00},
    {7, 30, 0, 0x4400},
    {7, 994, 0, 0x4600},
    {7, 31, 0, 0x4000},
    {7, 993, 0, 0x4200},
    {8, 32, 0, 0x3000},
    {8, 992, 0, 0x3100},
    {8, 33, 0, 0x2E00},
    {8, 991, 0, 0x2F00},
    {8, 34, 0, 0x2C00},
    {8, 990, 0, 0x2D00},
    {8, 35, 0, 0x2A00},
    {8, 989, 0, 0x2B00},
    {8, 36, 0, 0x2800},
    {8, 988, 0, 0x2900},
    {8, 37, 0, 0x2600},
    {8, 987, 0, 0x2700},
    {8, 38, 0, 0x2400},
    {8, 986, 0, 0x2500},
    {8, 39, 0, 0x2200},
    {8, 985, 0, 0x2300},
    {8, 40, 0, 0x2000},
    {8, 984, 0, 0x2100},
    {8, 1032, 0, 0x3E00},
    {8, 2040, 0, 0x3F00},
    {8, 1033, 0, 0x3C00},
    {8, 2039, 0, 0x3D00},
    {8, 1034, 0, 0x3A00},
    {8, 2038, 0, 0x3B00},
    {8, 1035, 0, 0x3800},
    {8, 2037, 0, 0x3900},
    {8, 1036, 0, 0x3600},
    {8, 2036, 0, 0x3700},
    {8, 1037, 0, 0x3400},
    {8, 2035, 0, 0x3500},
    {8, 1038, 0, 0x3200},
    {8, 2034, 0, 0x3300},
    {9, 1039, 0, 0x1300},
    {9, 2033, 0, 0x1380},
    {9, 1040, 0, 0x1200},
    {9, 2032, 0, 0x1280},
    {9, 1041, 0, 0x1100},
    {9, 2031, 0, 0x1180},
    {9, 1042, 0, 0x1000},
    {9, 2030, 0, 0x1080},
    {9, 6147, 0, 0x1400},
    {9, 7165, 0, 0x1480},
    {9, 11266, 0, 0x1A00},
    {9, 12286, 0, 0x1A80},
    {9, 12290, 0, 0x1900},
    {9, 13310, 0, 0x1980},
    {9, 13314, 0, 0x1800},
    {9, 14334, 0, 0x1880},
    {9, 14338, 0, 0x1700},
    {9, 15358, 0, 0x1780},
    {9, 15362, 0, 0x1600},
    {9, 16382, 0, 0x1680},
    {9, 16386, 0, 0x1500},
    {9, 17406, 0, 0x1580},
    {9, 27649, 0, 0x1F00},
    {9, 28671, 0, 0x1F80},
    {9, 28673, 0, 0x1E00},
    {9, 29695, 0, 0x1E80},
    {9, 29697, 0, 0x1D00},
    {9, 30719, 0, 0x1D80},
    {9, 30721, 0, 0x1C00},
    {9, 31743, 0, 0x1C80},
    {9, 31745, 0, 0x1B00},
    {9, 32767, 0, 0x1B80},
};
#endif

static const int quanttbl[64] = {
    8, 16, 19, 22, 26, 27, 29, 34,
    16, 16, 22, 24, 27, 29, 34, 37,
    19, 22, 26, 27, 29, 34, 34, 38,
    22, 22, 26, 27, 29, 34, 37, 40,
    22, 26, 27, 29, 32, 35, 40, 48,
    26, 27, 29, 32, 35, 40, 48, 58,
    26, 27, 29, 34, 38, 46, 56, 69,
    27, 29, 35, 38, 46, 56, 69, 83,
};

int idctprescale[64] = {
    8192, 5906, 6270, 6967, 8192, 10426, 15137, 29692,
    5906, 4258, 4520, 5023, 5906, 7517, 10913, 21407,
    6270, 4520, 4799, 5332, 6270, 7980, 11585, 22725,
    6967, 5023, 5332, 5925, 6967, 8867, 12873, 25251,
    8192, 5906, 6270, 6967, 8192, 10426, 15137, 29692,
    10426, 7517, 7980, 8867, 10426, 13270, 19266, 37791,
    15137, 10913, 11585, 12873, 15137, 19266, 27969, 54864,
    29692, 21407, 22725, 25251, 29692, 37791, 54864, 107619,
};

void madinit(void);

#if defined(DECOMP_COMPARE)
void madinit(void)
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
        clipbiastbl[i & 0x1FF] = v - 128;
    }
    madvlctbl1[0] = 0x0F;
    for (i = 1; i < 8; i++) {
        madvlctbl1[i] = 0x1F;
    }
    for (i = 15; i >= 8; i--) {
        madvlctbl1[i] = 0x2F;
    }
    for (i = 383; i >= 256; i--) {
        madvlctbl1[i] = 0x3F;
    }
    for (i = 1; i < 95; i++) {
        const MadCode_t *pCode = &encodetbl1[i];

        length = pCode->mLength;
        flags = pCode->mCode;
        value = pCode->mValue;
        if (flags & 0xFC00) {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | length;
            count = 1 << (9 - length);
            index = flags >> 7;
            for (j = 0; j < count; j++) {
                madvlctbl1[index + j] = code;
            }
        } else {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 6);
            count = 1 << (14 - length);
            index = flags >> 2;
            for (j = 0; j < count; j++) {
                madvlctbl3[index + j] = code;
            }
        }
    }
    for (i = 0; i < 128; i++) {
        const MadCode_t *pCode = &encodetbl2[i];

        length = pCode->mLength + 8;
        flags = pCode->mCode;
        value = pCode->mValue;
        if ((flags & 0x8000) == 0) {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 9);
            count = 1 << (17 - length);
            index = flags >> 7;
            for (j = 0; j < count; j++) {
                madvlctbl2[index + j] = code;
            }
        } else {
            code = (value << 22) | (((value >> 10) & 0x3F) << 16) | (length - 6);
            count = 1 << (14 - length);
            index = flags >> 10;
            for (j = 0; j < count; j++) {
                madvlctbl3[index + j] = code;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        madvlctbl4[i] = 1;
    }
    for (; i < 48; i++) {
        madvlctbl4[i] = ((i - 31) << 22) | 6;
        madvlctbl4[i + 16] = ((i - 48) << 22) | 6;
    }
    initflag = 1;
}
#endif

void maddiscardbits(int count)
{
    madshiftreg <<= count;
    madbitcount -= count;
    if (madbitcount < 16) {
        madshiftreg |= ((maddataptr[1] << 8) | maddataptr[0]) << (16 - madbitcount);
        madbitcount += 16;
        maddataptr += 2;
    }
}

int getdelta(void)
{
    int code = madvlctbl4[madshiftreg >> 26];

    maddiscardbits(code & 0xFF);
    return code >> 22;
}

void dcblock(int *pDst, int stride)
{
    int i;

    for (i = 0; i < 8; i++) {
        pDst[0] = idctinput[0];
        pDst[1] = idctinput[0];
        pDst[2] = idctinput[0];
        pDst[3] = idctinput[0];
        pDst[4] = idctinput[0];
        pDst[5] = idctinput[0];
        pDst[6] = idctinput[0];
        pDst[7] = idctinput[0];
        pDst += stride;
    }
}

void getluma(const unsigned char *pSrc, int stride, int *pDst, int bias)
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

void getchroma(const unsigned char *pSrc, int stride, int *pDst, int bias)
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

void setluma(const int *pSrc, unsigned char *pDst, int stride)
{
    int i;

    for (i = 0; i < 16; i++) {
        pDst[0] = clipbiastbl[(pSrc[0] >> 16) & 0x1FF];
        pDst[1] = clipbiastbl[(pSrc[1] >> 16) & 0x1FF];
        pDst[2] = clipbiastbl[(pSrc[2] >> 16) & 0x1FF];
        pDst[3] = clipbiastbl[(pSrc[3] >> 16) & 0x1FF];
        pDst[4] = clipbiastbl[(pSrc[4] >> 16) & 0x1FF];
        pDst[5] = clipbiastbl[(pSrc[5] >> 16) & 0x1FF];
        pDst[6] = clipbiastbl[(pSrc[6] >> 16) & 0x1FF];
        pDst[7] = clipbiastbl[(pSrc[7] >> 16) & 0x1FF];
        pDst[8] = clipbiastbl[(pSrc[8] >> 16) & 0x1FF];
        pDst[9] = clipbiastbl[(pSrc[9] >> 16) & 0x1FF];
        pDst[10] = clipbiastbl[(pSrc[10] >> 16) & 0x1FF];
        pDst[11] = clipbiastbl[(pSrc[11] >> 16) & 0x1FF];
        pDst[12] = clipbiastbl[(pSrc[12] >> 16) & 0x1FF];
        pDst[13] = clipbiastbl[(pSrc[13] >> 16) & 0x1FF];
        pDst[14] = clipbiastbl[(pSrc[14] >> 16) & 0x1FF];
        pDst[15] = clipbiastbl[(pSrc[15] >> 16) & 0x1FF];
        pSrc += 16;
        pDst += stride;
    }
}

void setchroma(const int *pSrc, unsigned char *pDst, int stride)
{
    int i;

    for (i = 0; i < 8; i++) {
        pDst[0] = clipbiastbl[(pSrc[0] >> 16) & 0x1FF];
        pDst[1] = clipbiastbl[(pSrc[1] >> 16) & 0x1FF];
        pDst[2] = clipbiastbl[(pSrc[2] >> 16) & 0x1FF];
        pDst[3] = clipbiastbl[(pSrc[3] >> 16) & 0x1FF];
        pDst[4] = clipbiastbl[(pSrc[4] >> 16) & 0x1FF];
        pDst[5] = clipbiastbl[(pSrc[5] >> 16) & 0x1FF];
        pDst[6] = clipbiastbl[(pSrc[6] >> 16) & 0x1FF];
        pDst[7] = clipbiastbl[(pSrc[7] >> 16) & 0x1FF];
        pSrc += 8;
        pDst += stride;
    }
}

void MAD_initdecode(const unsigned short *pData, int frame, int quant)
{
    const unsigned char *pBytes = (const unsigned char *)pData;
    int i;

    if (initflag == 0) {
        madinit();
    }
    madshiftreg = (((pBytes[1] << 8) | pBytes[0]) << 16) | ((pBytes[3] << 8) | pBytes[2]);
    madbitcount = 32;
    maddataptr = (unsigned char *)(pData + 2);
    motionframe = frame;
    madquant[0] = (int)(((long long)(quanttbl[0] << 16) * idctprescale[0] + 0x8000) >> 16);
    for (i = 1; i < 64; i++) {
        madquant[i] = (int)(((long long)((quant * quanttbl[i]) << 13) * idctprescale[i] + 0x8000) >> 16);
    }
}

void MAD_decodemacroblock(const unsigned char *pRefY, const unsigned char *pRefU, const unsigned char *pRefV,
                 unsigned char *pDstY, unsigned char *pDstU, unsigned char *pDstV, int stride)
{
    int flags;
    int dx;
    int dy;
    int offset;
    int bias;
    int halfStride = stride >> 1;

    if (motionframe == 0) {
        flags = 0;
    } else if (!(madshiftreg & 0xC0000000)) {
        flags = 0;
        maddiscardbits(2);
    } else {
        if ((int)madshiftreg < 0) {
            flags = 0x3FF;
            maddiscardbits(1);
        } else {
            flags = madshiftreg >> 24;
            maddiscardbits(8);
        }
        dx = getdelta();
        dy = getdelta();
        pRefY += dy * stride + dx;
        dx >>= 1;
        dy >>= 1;
        offset = dy * halfStride + dx;
        pRefU += offset;
        pRefV += offset;
    }
    if ((flags & 1) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(&luma[0], 16);
        } else {
            fn_801DB670(&luma[0], 16);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getluma(pRefY, stride, &luma[0], bias);
    }
    if ((flags & 2) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(&luma[8], 16);
        } else {
            fn_801DB670(&luma[8], 16);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getluma(pRefY + 8, stride, &luma[8], bias);
    }
    if ((flags & 4) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(&luma[128], 16);
        } else {
            fn_801DB670(&luma[128], 16);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getluma(pRefY + stride * 8, stride, &luma[128], bias);
    }
    if ((flags & 8) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(&luma[136], 16);
        } else {
            fn_801DB670(&luma[136], 16);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getluma(pRefY + stride * 8 + 8, stride, &luma[136], bias);
    }
    if ((flags & 0x10) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(madchroma[0], 8);
        } else {
            fn_801DB670(madchroma[0], 8);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getchroma(pRefU, halfStride, madchroma[0], bias);
    }
    if ((flags & 0x20) == 0) {
        if (madvlcdecode() == 1) {
            dcblock(madchroma[1], 8);
        } else {
            fn_801DB670(madchroma[1], 8);
        }
    } else {
        bias = getdelta() * 2 - 128;
        getchroma(pRefV, halfStride, madchroma[1], bias);
    }
    setluma(luma, pDstY, stride);
    setchroma(madchroma[0], pDstU, halfStride);
    setchroma(madchroma[1], pDstV, halfStride);
}
