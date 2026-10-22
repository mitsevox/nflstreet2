/* Math library init/shutdown and the random-number streams (linear congruential,
 * shuffled minimal-standard and subtractive generators). */

typedef struct RandStream_801CEF48 {
    int mType;
} RandStream_801CEF48;

typedef struct RandFast_801CEF48 {
    int mType;
    unsigned int mSeed;
} RandFast_801CEF48;

typedef struct RandSlow_801CEF48 {
    int mType;
    int mY;
    int mTable[32];
    int mSeed;
} RandSlow_801CEF48;

typedef struct RandSub_801CEF48 {
    int mType;
    int mNext;
    int mNextP;
    int mInit;
    int mTable[56];
} RandSub_801CEF48;

extern unsigned char lbl_803EBCB0;
extern RandStream_801CEF48 *(*lbl_802F7AD0[])(int seed);
extern int (*lbl_802F7AE8[])(RandStream_801CEF48 *pDst, RandStream_801CEF48 *pSrc);
extern float (*lbl_802F7AF4[])(RandStream_801CEF48 *pStream);
extern int lbl_802F7B00[];

void fn_801CFF34(void);
void fn_801F7BD4(int error);
void *fn_801D2B7C(int size, int a, int b);
void fn_801D2BD0(void *p);
int fn_8023E7AC(void);

void fn_801CF040(RandFast_801CEF48 *pStream, unsigned int seed);
void fn_801CF12C(RandSlow_801CEF48 *pStream, int seed);
void fn_801CF358(RandSub_801CEF48 *pStream, int seed);
float fn_801CF69C(RandStream_801CEF48 *pStream);

int fn_801CEF48(void)
{
    int result = 0;

    if (!lbl_803EBCB0) {
        fn_801CFF34();
        lbl_803EBCB0 = 1;
    } else {
        result = 0x40001;
    }
    fn_801F7BD4(result);
    return result;
}

int fn_801CEFA0(void)
{
    int result = 0;

    if (lbl_803EBCB0) {
        lbl_803EBCB0 = result;
    } else {
        result = 0x40002;
    }
    fn_801F7BD4(result);
    return result;
}

RandFast_801CEF48 *fn_801CEFF0(unsigned int seed)
{
    RandFast_801CEF48 *pStream = fn_801D2B7C(sizeof(RandFast_801CEF48), 0, 0);

    if (pStream) {
        fn_801CF040(pStream, seed);
    }
    return pStream;
}

void fn_801CF040(RandFast_801CEF48 *pStream, unsigned int seed)
{
    pStream->mSeed = seed;
}

int fn_801CF048(RandFast_801CEF48 *pDst, RandFast_801CEF48 *pSrc)
{
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        pDst->mSeed = pSrc->mSeed;
        result = 0;
    }
    return result;
}

float fn_801CF074(RandFast_801CEF48 *pStream)
{
    float value;

    pStream->mSeed = pStream->mSeed * 1664525 + 1013904223;
    value = (float)pStream->mSeed * 2.3283064e-10f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

RandSlow_801CEF48 *fn_801CF0DC(int seed)
{
    RandSlow_801CEF48 *pStream = fn_801D2B7C(sizeof(RandSlow_801CEF48), 0, 0);

    if (pStream) {
        fn_801CF12C(pStream, seed);
    }
    return pStream;
}

void fn_801CF12C(RandSlow_801CEF48 *pStream, int seed)
{
    int i;
    int k;

    if (seed == 0) {
        seed = 1;
    }
    for (i = 39; i >= 0; i--) {
        k = seed / 127773;
        seed = 16807 * (seed - k * 127773) - 2836 * k;
        if (seed < 0) {
            seed += 2147483647;
        }
        if (i < 32) {
            pStream->mTable[i] = seed;
        }
    }
    pStream->mY = pStream->mTable[0];
}

int fn_801CF1B0(RandSlow_801CEF48 *pDst, RandSlow_801CEF48 *pSrc)
{
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

float fn_801CF240(RandSlow_801CEF48 *pStream)
{
    int seed = pStream->mSeed;
    int k;
    int j;
    float value;

    k = seed / 127773;
    seed = 16807 * (seed - k * 127773) - 2836 * k;
    if (seed < 0) {
        seed += 2147483647;
    }
    j = pStream->mY / 67108864;
    pStream->mY = pStream->mTable[j];
    pStream->mTable[j] = seed;
    pStream->mSeed = seed;
    value = (float)seed * 4.65639582e-10f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

RandSub_801CEF48 *fn_801CF308(int seed)
{
    RandSub_801CEF48 *pStream = fn_801D2B7C(sizeof(RandSub_801CEF48), 0, 0);

    if (pStream) {
        fn_801CF358(pStream, seed);
    }
    return pStream;
}

void fn_801CF358(RandSub_801CEF48 *pStream, int seed)
{
    int mj;
    int mk;
    int i;
    int ii;
    int k;

    if (seed == 0) {
        seed = 1;
    }
    mj = 161803398 - seed;
    mj %= 1000000000;
    pStream->mTable[55] = mj;
    mk = 1;
    for (i = 1; i <= 54; i++) {
        ii = (21 * i) % 55;
        pStream->mTable[ii] = mk;
        mk = mj - mk;
        if (mk < 0) {
            mk += 1000000000;
        }
        mj = pStream->mTable[ii];
    }
    for (k = 1; k <= 4; k++) {
        for (i = 1; i <= 55; i++) {
            pStream->mTable[i] -= pStream->mTable[1 + (i + 30) % 55];
            if (pStream->mTable[i] < 0) {
                pStream->mTable[i] += 1000000000;
            }
        }
    }
    pStream->mNext = 0;
    pStream->mNextP = 31;
    pStream->mInit = 1;
}

int fn_801CF498(RandSub_801CEF48 *pDst, RandSub_801CEF48 *pSrc)
{
    int result = 0x40003;

    if (pDst->mType == pSrc->mType) {
        *pDst = *pSrc;
        result = 0;
    }
    return result;
}

float fn_801CF504(RandSub_801CEF48 *pStream)
{
    int mj;
    float value;

    if (++pStream->mNext > 55) {
        pStream->mNext = 1;
    }
    if (++pStream->mNextP > 55) {
        pStream->mNextP = 1;
    }
    mj = pStream->mTable[pStream->mNext] - pStream->mTable[pStream->mNextP];
    if (mj < 0) {
        mj += 1000000000;
    }
    pStream->mTable[pStream->mNext] = mj;
    value = (float)mj * 1e-9f;
    if (!(value < 0.99999988f)) {
        value = 0.99999988f;
    }
    return value;
}

RandStream_801CEF48 *fn_801CF5BC(int type, int seed)
{
    RandStream_801CEF48 *pStream = lbl_802F7AD0[type](seed);

    if (pStream) {
        pStream->mType = type;
    }
    return pStream;
}

int fn_801CF60C(RandStream_801CEF48 *pDst, RandStream_801CEF48 *pSrc)
{
    int type = pDst->mType;
    int result = 0x40003;

    if (pDst && pSrc) {
        result = lbl_802F7AE8[type](pDst, pSrc);
    }
    return result;
}

int fn_801CF664(RandStream_801CEF48 *pStream)
{
    return lbl_802F7B00[pStream->mType];
}

void fn_801CF67C(RandStream_801CEF48 *pStream)
{
    fn_801D2BD0(pStream);
}

float fn_801CF69C(RandStream_801CEF48 *pStream)
{
    return lbl_802F7AF4[pStream->mType](pStream);
}

unsigned int fn_801CF6D4(RandStream_801CEF48 *pStream, unsigned int range)
{
    float value = fn_801CF69C(pStream) * (float)range;

    if ((unsigned int)value >= range) {
        value = 0.0f;
    }
    return (unsigned int)value;
}

int fn_801CF7AC(void)
{
    return fn_8023E7AC();
}
