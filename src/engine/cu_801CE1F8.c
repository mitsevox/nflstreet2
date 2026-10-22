/* Low-level graphics: video/GX setup, frame-buffer swapping and screen queries. */
#include "engine/cu_801CE1F8.h"
#include "game/fn_801D2B7C.h"

extern GlibConfig_801CE1F8 lbl_803E91F8;
extern GlibState_801CE1F8 lbl_803E9224;
extern unsigned char lbl_803EBC68;
extern int lbl_803EBC6C;
extern void (*lbl_803EBC74)(void);
extern void (*lbl_803EBC78)(void);
extern unsigned char lbl_803EBC87;
extern unsigned char lbl_803EBC88;
extern int lbl_803ECF00;
extern unsigned char lbl_803ECF04;
extern unsigned char lbl_803ECF05;
extern unsigned char lbl_803ECF0C;
extern int lbl_803ED634;
extern int lbl_803ED638;
extern int lbl_803ED63C;
extern unsigned char lbl_802F7A4C[];
extern unsigned char lbl_802F7A88[];
extern unsigned char lbl_802FE350[];
extern unsigned char lbl_802FE38C[];
extern unsigned char lbl_802FE3C8[];
extern unsigned char lbl_802FE404[];
extern unsigned char lbl_802FE440[];
extern unsigned char lbl_802FE47C[];
extern unsigned char lbl_802FE4B8[];

void *fn_801C1F94();
void *fn_801C1FBC();
void fn_801F7B04(void);
void fn_80239CC0(void *addr, int size);
void fn_80243384(void (*callback)(void));
void fn_80243B18(void);
void fn_80243FE0(GlibState_801CE1F8 *pMode);
void fn_80244808(void);
void fn_80244938(void *pXfb);
void fn_802449A4(int black);
void *fn_8024AF70(void *pFifo, int size);
int fn_8024C4F4(int a, int *pB, int *pC);
void fn_8024C5D0(int a);
void fn_8024C65C(void);
int fn_8024C8D8(void);
void fn_8024E034(void);
void fn_8024E36C(void);
void fn_8024E404(void);
void fn_8024E450(void);
void fn_8024E4D0(void);
void fn_8024E750(void (*callback)(void));
void fn_8024EBC4(void *pSrc, GlibState_801CE1F8 *pDst, int hor, int ver);
void fn_8024ECE4(int left, int top, int width, int height);
void fn_8024EDDC(int width, int height);
void fn_8024EFBC(float scale);
void fn_8024F088(GXColor color, int z);
void fn_8024F100(int aa, unsigned char (*pPattern)[2], int filter, unsigned char *pVFilter);
void fn_8024F31C(void *pDst, int clear);
void fn_80252088(int enable);
void fn_802520E0(int enable, int func, int update);
void fn_80252148(int format, int zFormat);
void fn_8025278C(float left, float top, float width, float height, float nearZ, float farZ);
void fn_802527F8(int left, int top, int width, int height);
void fn_802523A4(void *pMatrix, int type);
void fn_801CED3C(GlibState_801CE1F8 *pMode);
void fn_802103DC(void);
void fn_80210634(void);
extern unsigned char lbl_80383DA0[];

int fn_801CE7D0(int a);
void fn_801CE2B8(int enable);
void fn_801CE95C(void);
void fn_801CEA44(int enable);
static void fn_801CEC08(void);
static void fn_801CEC0C(GlibConfig_801CE1F8 *pConfig);

static int fn_801CE1F8(unsigned int value)
{
    int bits = 0;
    unsigned int v;

    for (v = value >> 1; v; v >>= 1) {
        bits++;
    }
    if (value & (value - 1)) {
        bits++;
    }
    return bits;
}

static void fn_801CE228(void)
{
}

void fn_801CE22C(void (*callback)(void))
{
    lbl_803EBC74 = callback;
}

void fn_801CE234(void (*callback)(void))
{
    lbl_803EBC78 = callback;
}

void fn_801CE23C(void)
{
    lbl_803EBC74 = 0;
}

void fn_801CE248(int enable)
{
    lbl_803EBC6C = enable;
}

static void fn_801CE250(void)
{
    lbl_803ED638 = -lbl_803ED634;
}

static void fn_801CE260(void)
{
    fn_801F7B04();
    if (lbl_803EBC74) {
        lbl_803EBC74();
    }
    if (lbl_803EBC87) {
        fn_8024C65C();
    }
    if (lbl_803EBC78) {
        lbl_803EBC78();
    }
}

void fn_801CE2B8(int enable)
{
    if (enable) {
        fn_80243384(fn_801CE260);
    } else {
        fn_80243384(0);
    }
}

int fn_801CE2F4(GlibConfig_801CE1F8 *pConfig)
{
    GlibConfig_801CE1F8 *pCfg;
    GlibState_801CE1F8 *pMode;
    void *pSrcMode = 0;
    void *pFifo;

    lbl_803E91F8 = *pConfig;
    pCfg = &lbl_803E91F8;
    pMode = &lbl_803E9224;
    lbl_803ECF05 = 0;
    switch (pCfg->mTvMode) {
    case 0:
        pSrcMode = lbl_802FE350;
        break;
    case 1:
        pSrcMode = lbl_802FE38C;
        break;
    case 2:
        pSrcMode = lbl_802FE3C8;
        break;
    case 3:
        pSrcMode = lbl_802FE404;
        break;
    case 4:
        pSrcMode = lbl_802FE440;
        break;
    case 5:
        pSrcMode = lbl_802FE47C;
        break;
    case 6:
        pSrcMode = lbl_802FE4B8;
        break;
    case 7:
        pSrcMode = lbl_802F7A4C;
        lbl_803ECF05 = 1;
        break;
    case 8:
        pSrcMode = lbl_802F7A88;
        break;
    }
    fn_801C1F94(pMode, 0, 0x3C);
    if (pCfg->mTvMode == 7) {
        fn_8024EBC4(pSrcMode, pMode, 0, 16);
    } else if (pCfg->mTvMode == 8) {
        fn_8024EBC4(pSrcMode, pMode, 0, 16);
    } else {
        fn_8024EBC4(pSrcMode, pMode, 0, 16);
    }
    lbl_803ECF00 = ((pMode->mFbWidth + 15) & 0xFFF0) * pMode->mXfbHeight * 2;
    pMode->mpXfb[1] = pMode->mpXfb[0] = fn_801D2B7C(lbl_803ECF00, 0, 0);
    pMode->mFrame = 0;
    lbl_803ECF04 = 0;
    fn_80243FE0(pMode);
    fn_80244938(pMode->mpXfb[pMode->mFrame]);
    pMode->mLog2Width = fn_801CE1F8(pCfg->mWidth);
    pMode->mLog2Height = fn_801CE1F8(pCfg->mHeight);
    pFifo = fn_801D2B7C(pCfg->mFifoSize, 0, 0);
    fn_80239CC0(pFifo, pCfg->mFifoSize);
    pMode->mpFifoBuffer = pFifo;
    pMode->mpFifo = fn_8024AF70(pFifo, pCfg->mFifoSize);
    pMode->mFifoSize = pCfg->mFifoSize;
    fn_8024F088(pCfg->mClearColor, 0xFFFFFF);
    fn_8025278C(0.0f, 0.0f, (unsigned int)pMode->mFbWidth, (unsigned int)pMode->mXfbHeight, 0.0f, 1.0f);
    fn_802527F8(0, 0, pMode->mFbWidth, pMode->mEfbHeight);
    fn_8024ECE4(0, 0, pMode->mFbWidth, pMode->mEfbHeight);
    fn_8024EDDC(pMode->mFbWidth, pMode->mXfbHeight);
    fn_8024EFBC((float)(unsigned int)pMode->mXfbHeight / (float)(unsigned int)pMode->mEfbHeight);
    fn_801CEA44(1);
    if (pMode->mAa) {
        fn_80252148(2, 0);
    } else {
        fn_80252148(0, 0);
    }
    fn_802449A4(1);
    fn_80244808();
    fn_8024F31C(lbl_803E9224.mpXfb[pMode->mFrame], 1);
    fn_80244808();
    fn_8024F31C(lbl_803E9224.mpXfb[pMode->mFrame], 1);
    fn_80244808();
    fn_801CE7D0(0);
    if (pMode->mViTvMode & 1) {
        fn_80243B18();
    }
    fn_802449A4(0);
    fn_8024E750(fn_801CE250);
    fn_801CE2B8(1);
    fn_801CEC0C(pCfg);
    lbl_803EBC68 = 1;
    return 0;
}

int fn_801CE718(void)
{
    return 0;
}

void fn_801CE720(void)
{
    int a;
    int b;

    if (lbl_803ECF0C) {
        fn_8024E034();
        fn_8024C4F4(fn_8024C8D8(), &a, &b);
        fn_8024C5D0(b);
    }
    fn_801CED3C(&lbl_803E9224);
    fn_802103DC();
}

static inline void sync_801CE774(int count)
{
    fn_8024E404();
    lbl_803ED63C = count;
}

void fn_801CE774(void)
{
    if (!lbl_803EBC68) {
        fn_801CE95C();
    }
    fn_80210634();
    fn_8024E36C();
    fn_8024E034();
    if (lbl_803ECF0C) {
        fn_8024C65C();
        sync_801CE774(0);
    }
}

int fn_801CE7D0(int a)
{
    fn_80243B18();
    return 0;
}

static void fn_801CE7F4(void)
{
    int a;
    int b;

    fn_8024E034();
    fn_8024C4F4(fn_8024C8D8(), &a, &b);
    fn_8024C5D0(b);
}

void fn_801CE82C(void)
{
    if (lbl_803ECF04) {
        fn_80244938(lbl_803E9224.mpXfb[lbl_803E9224.mFrame]);
        fn_80244808();
        fn_80243B18();
        lbl_803E9224.mFrame ^= 1;
        fn_801CEC08();
    } else {
        fn_8024E450();
        fn_801CE228();
        fn_80244938(lbl_803E9224.mpXfb[0]);
        fn_80244808();
        if (lbl_803EBC88) {
            fn_801CE7F4();
            lbl_803EBC87 = 1;
        } else {
            fn_80243B18();
        }
        lbl_803ED634 = 0;
        fn_80252088(1);
        fn_802520E0(1, 3, 1);
        fn_8024F31C(lbl_803E9224.mpXfb[0], lbl_803EBC68);
        fn_8024E4D0();
        lbl_803E9224.mFrame = 0;
    }
}

void fn_801CE908(unsigned char enable)
{
    lbl_803EBC88 = enable;
}

void fn_801CE910(void)
{
    fn_8024E450();
}

unsigned char fn_801CE930(void)
{
    return lbl_803E9224.mFrame;
}

int fn_801CE93C(void)
{
    return 0;
}

void *fn_801CE944(int frame)
{
    return lbl_803E9224.mpXfb[frame];
}

void fn_801CE95C(void)
{
    GlibState_801CE1F8 *pMode = &lbl_803E9224;

    fn_80252088(0);
    fn_802520E0(0, 0, 1);
    fn_8024EDDC(0, 0);
    fn_8024F31C(lbl_80383DA0, 1);
    fn_80252088(1);
    fn_802520E0(1, 3, 1);
    fn_8024EDDC(pMode->mFbWidth, pMode->mXfbHeight);
}

void fn_801CE9E0(int enable)
{
    fn_802520E0(enable, 3, 1);
}

int fn_801CEA08(void)
{
    return lbl_803E91F8.mWidth;
}

int fn_801CEA14(void)
{
    return lbl_803E91F8.mHeight;
}

void fn_801CEA20(void *pMatrix)
{
    fn_802523A4(pMatrix, 0);
}

void fn_801CEA44(int enable)
{
    fn_8024F100(lbl_803E9224.mAa, lbl_803E9224.mSamplePattern, enable, lbl_803E9224.mVFilter);
}

void fn_801CEA7C(unsigned char clear)
{
    lbl_803EBC68 = clear;
}

void fn_801CEA84(void)
{
    GlibState_801CE1F8 *pMode = &lbl_803E9224;

    fn_80244938(pMode->mpXfb[0]);
    fn_80244808();
    fn_80243B18();
    fn_801D2BD0(pMode->mpXfb[1]);
    lbl_803ECF04 = 0;
    pMode->mFrame = 0;
    pMode->mpXfb[1] = pMode->mpXfb[0];
}

void fn_801CEADC(int skipSwap)
{
    if (!skipSwap) {
        fn_801CE82C();
        fn_801CE82C();
    }
    lbl_803E9224.mpXfb[1] = fn_801D2B7C(lbl_803ECF00, 0, 0);
    fn_801C1FBC(lbl_803E9224.mpXfb[1], lbl_803E9224.mpXfb[0], lbl_803ECF00);
    lbl_803ECF04 = 1;
}

int fn_801CEB40(void)
{
    return 0xFFFF;
}

int fn_801CEB4C(void)
{
    return 0xFFFF;
}

void fn_801CEB58(int progressive)
{
    if (lbl_803ECF05 != progressive) {
        lbl_803ECF05 = progressive;
        fn_802449A4(1);
        if (progressive) {
            fn_8024EBC4(lbl_802F7A4C, &lbl_803E9224, 0, 16);
        } else {
            fn_8024EBC4(lbl_802FE440, &lbl_803E9224, 0, 16);
        }
        fn_80243FE0(&lbl_803E9224);
        fn_80244808();
        fn_80243B18();
        fn_80243B18();
        fn_80243B18();
        fn_802449A4(0);
        fn_80244808();
        fn_80243B18();
    }
}

static void fn_801CEC08(void)
{
}

static void fn_801CEC0C(GlibConfig_801CE1F8 *pConfig)
{
    fn_802527F8(0, 0, pConfig->mWidth - 1, pConfig->mHeight - 1);
}

void fn_801CEC48(int left, int width, int top, int height)
{
    fn_802527F8(left, top, width, height);
}

int fn_801CEC74(void)
{
    return 0x150;
}

int fn_801CEC7C(void)
{
    return 0x280;
}

unsigned short fn_801CEC84(void)
{
    return lbl_803E9224.mXfbHeight;
}
