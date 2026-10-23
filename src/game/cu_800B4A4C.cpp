#include "game/bitstream.h"
#include "game/fn_801FCE10.h"
#include "game/fn_8017F584.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Item_800476DC.h"
#include "game/cu_80136B1C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/fn_800AD9B4.h"
#include <string.h>

extern "C" {
void fn_800B44D4(BitStream_t *pStream);
void fn_800B4628(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t);
void fn_80030ACC(void (*pSave)(BitStream_t *pStream),
                 void (*pLoad)(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                               BitStream_t *pStream3, float t),
                 int size, const char *pName);
}

extern "C" void fn_800B4A4C(void)
{
    fn_80030ACC(fn_800B44D4, fn_800B4628, 0x8C0, "Player Abilities");
}

struct Record_800B4DE4 {
    float mUnknown0;
    float mUnknown4;
    unsigned short mUnknown8;
    char mUnknown10[2];
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    char mUnknown14[2];
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    char mUnknown27[21];
    char mUnknown48[21];
    char mUnknown69[1];
};

extern "C" {
unsigned char fn_80054D24(int index);
char *fn_801C2EB4(char *pDest, const char *pSource);
char *fn_801C32CC(char *pString);
float fn_80237260(int stream);
void fn_800476CC(Item_800476DC *p, const char *name);
void fn_8009BD88(Object_80039F5C *p, float scale);
void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_801CFB18(int angle);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_800EF8E8(Object_80039F5C *p, int a);
void fn_800D4948(void);
float fn_80178A2C(void);
unsigned int fn_80178D18(int team);
int fn_80178308(void);
int fn_80178320(void);
int fn_801486A0(void);
void fn_80156C78(int index, int value);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_801783AC(int bit);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_80227350(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
Object_80039F5C *fn_800B6544(int index);
void fn_800B6658(Object_80039F5C *p);
void fn_800B6714(Object_80039F5C *p, int index);
Object_80039F5C *fn_800B57F4(unsigned char team, Vector_80039F5C *pPos, Vector_80039F5C *pVel, int carried);
}

extern "C" void fn_800B4DE4(QueryCursor cursor, int index, void *pData)
{
    Record_800B4DE4 *pOut = (Record_800B4DE4 *)pData;
    int values[18];

    cursor.mUnknown4 = index;
    fn_801FCE10(0,
        "fetch from \x8a 'ANFP' into \x88 and 'ANLP' into \x88 and 'NKNP' into \x88 and "
        "'TGWP' into \x82 and 'TGHP' into \x82 and 'IKSP' into \x82 and 'NAHP' into \x82 and "
        "'SOPP' into \x82 and 'DIGP' into \x82 and 'LCUP' into \x82 and 'LECP' into \x82 and "
        "'1TGS' into \x82 and '2TGS' into \x82 and '3TGS' into \x82 and '4TGS' into \x82 and "
        "'NSPP' into \x82 and 'TBYP' into \x82 and 'XELP' into \x82 and 'TLFP' into \x82\n",
        &cursor, pOut->mUnknown27, pOut->mUnknown48, pOut->mUnknown69,
        &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], &values[9], &values[10],
        &values[12], &values[13], &values[14], &values[15], &values[11], &values[16], &values[8], &values[17]);
    fn_801C2EB4(pOut->mUnknown69, pOut->mUnknown48);
    pOut->mUnknown20 = values[16];
    if (fn_8017F584() == 0) {
        if (fn_80054D24(30) || fn_80054D24(34)) {
            pOut->mUnknown0 = (float)values[3] * 0.33;
        } else if (fn_80054D24(31)) {
            pOut->mUnknown0 = (float)values[3] * 1.5;
        } else if (fn_80054D24(44)) {
            pOut->mUnknown0 = (float)values[3] * (fn_80237260(0) + 0.5f);
        } else {
            pOut->mUnknown0 = (float)values[3];
        }
    } else {
        pOut->mUnknown0 = (float)values[3];
    }
    pOut->mUnknown4 = (float)values[2] + 160.0f;
    pOut->mUnknown12 = values[4];
    pOut->mUnknown13 = values[5];
    pOut->mUnknown16 = values[6];
    pOut->mUnknown8 = values[7];
    pOut->mUnknown22 = values[8];
    pOut->mUnknown17 = values[9];
    pOut->mUnknown18 = values[10];
    pOut->mUnknown19 = values[11];
    pOut->mUnknown23 = values[12];
    pOut->mUnknown24 = values[13];
    pOut->mUnknown25 = values[14];
    pOut->mUnknown26 = values[15];
    pOut->mUnknown21 = values[17];
}

extern "C" void fn_800B5150(Object_80039F5C *p)
{
    if (p) {
        Object_8003DEC4 *model = (Object_8003DEC4 *)p->mpUnknown4;
        char name[48];
        fn_801C2EB4(name, p->mUnknown2927 + 21);
        fn_801C32CC(name);
        fn_800476CC(model->mUnknown988, p->mUnknown2927 + 42);
        float scale = p->mUnknown2900;
        scale *= 0.013888889f;
        if (scale == 0.0f) {
            scale = 1.0f;
        }
        fn_8009BD88(p, scale);
    }
}

extern "C" int fn_800B54D4(Object_80039F5C *p, int mode)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pNearest;
    Object_80039F5C *pOther;
    float distance;
    float otherDistance;
    float limit;

    pNearest = fn_801245DC(p, fn_80178320(), 0, fn_80178D18(fn_80178320()), 0x200000, &distance, 0);
    pOther = fn_801245DC(p, fn_80178308(), 0, fn_80178D18(fn_80178308()), 0x200000, &otherDistance, 0);
    if (pNearest == 0 || (pOther != 0 && otherDistance < distance)) {
        pNearest = pOther;
        distance = otherDistance;
    }
    if (pNearest != 0) {
        Point_8017886C delta;
        int angle;
        int turn;

        fn_80227690(&delta, &pNearest->mMotion, pMotion);
        angle = fn_801CFE40(delta.mY, delta.mX);
        turn = fn_801CFFD0(angle, pMotion->mFacing);
        fn_801CFFD0((angle + 0x800000) & 0xFFFFFF, pNearest->mMotion.mFacing);
        if (!(distance > 3.0f) && turn <= 0x1FFFFF && !(pNearest->mFlags & 0x800) && fn_800EF8E8(p, mode) != 0) {
            return 1;
        }
    }
    if (pMotion->mUnknown44 > 0.0f) {
        otherDistance = fn_80178A2C() - pMotion->mPos.mY;
        limit = 7.0f;
        limit *= fn_801CFB18(p->mMotion.mFacing);
        if (otherDistance > 0.0f && otherDistance < limit && fn_800E815C(p, 2, mode) != 0) {
            fn_800D4948();
            return 1;
        }
    }
    return fn_800EF8E8(p, mode);
}

extern "C" void fn_800B5764(Vector_80039F5C *pOut)
{
    pOut->mX = pOut->mY = 0.0f;
    Object_80039F5C *pOwner = fn_80137BEC();
    float height;
    if (pOwner) {
        height = (pOwner->mUnknown2900 * 0.027777778f + 1.159353f) * 0.5f;
    } else {
        height = 1.65f;
    }
    fn_8013AA00(fn_801374BC(), height, 0, pOut);
}

extern "C" void fn_800B6988(int index)
{
    Object_80039F5C *pNew = 0;

    if (fn_801486A0() != 0 && fn_801486A0() != 1 && fn_800AD9B4() == 3) {
        Vector_80039F5C vel;
        Vector_80039F5C target;
        Vector_80039F5C pos;
        Object_80039F5C *p;
        Object_80137ABC *pBall;
        Object_80039F5C *pCarrier;
        int ballState;

        fn_80156C78(0x24, 1);
        p = fn_800B6544(index);
        pBall = fn_801374BC();
        fn_8013BA58(pBall, &ballState);
        pCarrier = fn_80137AD0(pBall);
        if (pCarrier != 0) {
            pos.mX = pCarrier->mMotion.mPos.mX;
            pos.mY = pCarrier->mMotion.mPos.mY;
            vel.mX = pCarrier->mMotion.mUnknown40;
            vel.mY = pCarrier->mMotion.mUnknown44;
            vel.mZ = pCarrier->mMotion.mUnknown48;
        } else {
            fn_80137D58(pBall, &pos);
            fn_80137EC4(pBall, &vel);
            if (fn_80138064(pBall, &target) != 0) {
                Object_80039F5C *pReceiver;

                fn_80227264(&pos, &pos, 1.0f - 0.8f);
                fn_80227350(&pos, &target, 0.8f);
                pReceiver = fn_80137B88(pBall);
                if (p->mIdBytes[2] == fn_80178308() && pReceiver != 0 && pReceiver->mUnknown8 == 0xFF
                    && !fn_801783AC(11) && !fn_801783AC(12) && !fn_801783AC(24)) {
                    pNew = pReceiver;
                }
            }
        }
        if (pNew == 0) {
            pNew = fn_800B57F4(p->mIdBytes[2], &pos, &vel, pCarrier != 0);
        }
        if (pNew != 0) {
            int state;

            fn_800B6658(p);
            fn_800B6714(pNew, index);
            if (fn_8013BA58(fn_801374BC(), &state) == 5 && state == 1) {
                Message_800F01CC message;

                memset(&message, 0, sizeof(message));
                message.mId = 0x39;
                message.mUnknown1[0] = fn_801374E0(fn_801374BC());
                fn_8003AB28(pNew, &message, 0);
            }
        }
    }
}
