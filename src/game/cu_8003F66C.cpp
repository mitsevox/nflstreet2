/* Partial comparison source for the inferred grouping 0x8003F66C-0x800400CC.
   Not a recovered original file. The original assembly stays linked; only the
   bodies below are compiled and measured. */

/* Record reached through the first argument of fn_8003F66C-fn_8003F754.
   Only the accessed fields are declared; the size is unknown. */
struct Object_8003F66C {
    int mUnknown0;
    int mUnknown4;
    float (*mpUnknown8)[3];
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    float mUnknown28;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    unsigned char mUnknown34;
    char mUnknown35[1];
    float mUnknown36;
    float mUnknown40;
    unsigned char mUnknown44;
};

/* Object passed to fn_8003F91C (also the r3 of fn_8003F768 and fn_8003FBF0,
   which test and set the same word +20). Only the accessed field is
   declared; the size is unknown. */
struct Object_8003F768 {
    char mUnknown0[20];
    int mUnknown20;
};

extern "C" {
void fn_8019CEE8(Object_8003F768 *p);
void fn_8019CFD0(Object_8003F768 *p);
void fn_801DCF8C(int type);
void fn_801DD320(int handle, int item);
}

#include "engine/cu_80227F14.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/bitstream.h"

extern "C" {
unsigned char fn_8003F95C(BitStream_t *pStream, Vector_80039F5C *pPos, Quat_801EB488 *pRot,
                          Vector_80039F5C *pLinkPos, Quat_801EB488 *pLinkRot, Object_80039F5C **ppObject,
                          int *pIndex, unsigned char *pFlag);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
void fn_801EC048(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
int fn_80054138(Vector_80039F5C *pPos);
void fn_80030CA4(Object_80039F5C *pA, Object_80039F5C *pB);
}

extern "C" void fn_8003F6B0(Object_8003F66C *p)
{
}

extern "C" void fn_8003F6B4(Object_8003F66C *p, float (*pData)[3], int a)
{
    p->mpUnknown8 = pData;
    p->mUnknown0 = 0;
    p->mUnknown4 = a;
}

extern "C" void fn_8003F6C8(Object_8003F66C *p, unsigned char a, unsigned char b, unsigned char c)
{
    p->mUnknown32 = a;
    p->mUnknown33 = b;
    p->mUnknown34 = c;
}

extern "C" void fn_8003F6D8(Object_8003F66C *p, float value)
{
    p->mUnknown28 = value;
}

extern "C" void fn_8003F6E0(Object_8003F66C *p, float value)
{
    p->mUnknown36 = value;
}

extern "C" void fn_8003F6E8(Object_8003F66C *p, float value)
{
    p->mUnknown40 = value;
}

extern "C" void fn_8003F6F0(Object_8003F66C *p, float *pValue)
{
    p->mpUnknown8[p->mUnknown0][0] = pValue[0];
    p->mpUnknown8[p->mUnknown0][1] = pValue[1];
    p->mpUnknown8[p->mUnknown0][2] = pValue[2];
    p->mUnknown0++;
}

extern "C" void fn_8003F744(Object_8003F66C *p)
{
    p->mUnknown0 = 0;
    p->mUnknown44 = 0;
}

extern "C" void fn_8003F754(Object_8003F66C *p, int a, int b, float c, float d)
{
    p->mUnknown12 = a;
    p->mUnknown16 = c;
    p->mUnknown20 = d;
    p->mUnknown24 = b;
}

extern "C" void fn_8003F91C(Object_8003F768 *p)
{
    fn_8019CFD0(p);
    if (!(p->mUnknown20 & 4)) {
        fn_8019CEE8(p);
    }
}

extern "C" void fn_8003FB2C(void)
{
    fn_80228E18();
    fn_801DCF8C(3);
}

extern "C" void fn_8003FBB4(int handle, int item)
{
    if (item) {
        fn_801DD320(handle, item);
        fn_80228D58(item);
    }
}

extern "C" int fn_8003FC68(void)
{
    return 212;
}

extern "C" void fn_8003FE90(Block_80170E64 *pBlock, BitStream_t *pStream1, BitStream_t *pStream0,
                            BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    Vector_80039F5C pos0;
    Vector_80039F5C pos1;
    Vector_80039F5C linkPos0;
    Vector_80039F5C linkPos1;
    Quat_801EB488 rot0;
    Quat_801EB488 rot1;
    Quat_801EB488 linkRot0;
    Quat_801EB488 linkRot1;
    unsigned char flag = 0;
    Object_80039F5C *pObject0;
    int index0;
    Object_80039F5C *pObject1;
    int index1;
    unsigned char changed0;
    unsigned char changed1;

    if (pStream2) {
        fn_8003F95C(pStream2, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    }
    if (pStream3) {
        fn_8003F95C(pStream3, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    }
    changed0 = fn_8003F95C(pStream0, &pos0, &rot0, &linkPos0, &linkRot0, &pObject0, &index0, &flag);
    changed1 = fn_8003F95C(pStream1, &pos1, &rot1, &linkPos1, &linkRot1, &pObject1, &index1, &flag);
    if (pObject0 != 0 && pObject1 != 0) {
        Object_8003DEC4 *pPose = (Object_8003DEC4 *)pObject0->mpUnknown4;

        if (index0 == index1) {
            fn_80227930(&pBlock->mUnknown4, &linkPos1, &linkPos0, t);
            fn_801EC048(&pBlock->mUnknown108, &linkRot1, &linkRot0, t);
        } else {
            pBlock->mUnknown4.mX = linkPos1.mX;
            pBlock->mUnknown4.mY = linkPos1.mY;
            pBlock->mUnknown4.mZ = linkPos1.mZ;
            pBlock->mUnknown108.mX = linkRot1.mX;
            pBlock->mUnknown108.mY = linkRot1.mY;
            pBlock->mUnknown108.mZ = linkRot1.mZ;
            pBlock->mUnknown108.mW = linkRot1.mW;
            pPose->mUnknown44.mUnknown6 = index1;
        }
    } else {
        fn_80227930(&pBlock->mUnknown4, &pos1, &pos0, t);
        fn_801EC048(&pBlock->mUnknown108, &rot1, &rot0, t);
    }
    pBlock->mUnknown660 = fn_80054138(&pBlock->mUnknown4);
    if (changed0 | changed1) {
        fn_80030CA4(pObject0, pObject1);
    }
    if (flag) {
        pBlock->mUnknown20 |= 2;
    } else {
        pBlock->mUnknown20 &= ~2;
    }
}

extern "C" void fn_800400BC(Block_80170E64 *pBlock, Object_80041904 *pLinked)
{
    pBlock->mpUnknown676 = pLinked;
}

extern "C" Object_80041904 *fn_800400C4(Block_80170E64 *pBlock)
{
    return pBlock->mpUnknown676;
}
