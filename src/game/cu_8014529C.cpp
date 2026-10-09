#include "game/Event_801459F0.h"
#include "game/Object_8003DEC4.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801EBC18.h"
#include "game/fn_802270D4.h"

extern "C" {
void fn_80044858(Object_80039F5C *pPlayer, Vector_80039F5C *pPos, int foot0);
int fn_800A33DC(void);
int fn_800A8444(int team);
int fn_80144FE8(int a);
int fn_80145074(int a);
void fn_801D03D0(float m[4][4]);
void fn_801D04C4(void);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0664(float (*m)[4]);
void fn_801D06D4(void *p);
void fn_801D0BCC(int a, int b, int c);
void fn_801D0C58(void *a);
void fn_801D0CFC(float a);
void fn_801D0F80(float m[4][4]);
void fn_801D0FB8(Vector_80039F5C *pOut);
void fn_801D11F4(Angles_801EBC18 *pOut, int a);
int fn_80227594(float *pA, float *pB, float tolerance);
}

extern "C" void fn_8014529C(Object_8003DEC4 *pBody, int index, Vector_80039F5C *pPos, Angles_801EBC18 *pAngles)
{
    fn_801D04C4();
    fn_801D06D4(pBody->mUnknown908);
    fn_801D0CFC(pBody->mUnknown24);
    fn_801D0664(pBody->mUnknown44.mUnknown52[index]);
    fn_801D0FB8(pPos);
    if (pAngles) {
        fn_801D11F4(pAngles, 0);
    }
    fn_801D0544();
}

extern "C" void fn_80145314(Event_801459F0 *pEvent)
{
    Object_80039F5C *pPlayer = (Object_80039F5C *)pEvent->mUnknown0C;
    Object_8003DEC4 *pBody = (Object_8003DEC4 *)pPlayer->mpUnknown4;
    Vector_80039F5C pos;
    float m[4][4];
    Args_80144CE0 args;
    float speed;

    fn_8014529C(pBody, pEvent->mUnknown14, &pos, 0);
    speed = pPlayer->mMotion.mUnknown28;
    fn_80044858(pPlayer, &pos, pEvent->mUnknown14 == 8);
    if (fn_800A8444(0) || fn_800A8444(1) || pos.mZ >= 0.09f || speed <= 0.05f) {
        return;
    }
    if ((pEvent->mUnknown14 == 8 && !fn_80227594(pPlayer->mUnknown1016, &pos.mX, 0.5f))
        || (pEvent->mUnknown14 == 4 && !fn_80227594(pPlayer->mUnknown1024, &pos.mX, 0.5f))) {
        if (pEvent->mUnknown14 == 8) {
            pPlayer->mUnknown1016[0] = pos.mX;
            pPlayer->mUnknown1016[1] = pos.mY;
        } else {
            pPlayer->mUnknown1024[0] = pos.mX;
            pPlayer->mUnknown1024[1] = pos.mY;
        }
        if (pEvent->mUnknown18 == 0 && pBody->mUnknown972 != 0) {
            fn_801D03D0(m);
            m[2][3] = m[1][3] = m[0][3] = 0.0f;
            fn_801D03D0(pEvent->mUnknown20);
            pEvent->mUnknown20[0][3] = pos.mX;
            pEvent->mUnknown20[1][3] = pos.mY;
            pEvent->mUnknown20[2][3] = pos.mZ;
            args.mUnknown0C = 0;
            args.mUnknown10 = 0;
            args.mUnknown08 = &m;
            args.mUnknown04 = &pEvent->mUnknown20;
            args.mUnknown00 = fn_80144FE8(((Source_80144CE0 *)pBody->mUnknown972)->mUnknown08);
            pEvent->mUnknown18 = fn_80144CE0(&args, 0, (Source_80144CE0 *)pBody->mUnknown972);
        }
    }
}

extern "C" void fn_801454DC(Event_801459F0 *pEvent)
{
    Object_80039F5C *pPlayer = (Object_80039F5C *)pEvent->mUnknown0C;
    Vector_80039F5C pos;
    Angles_801EBC18 angles;
    float m[4][4];
    Args_80144CE0 args;

    fn_8014529C((Object_8003DEC4 *)pPlayer->mpUnknown4, pEvent->mUnknown14, &pos, &angles);
    if (pEvent->mUnknown18 == 0) {
        fn_801D03D0(m);
        m[2][3] = m[1][3] = m[0][3] = 0.0f;
        fn_801D0508();
        fn_801D0C58(&pos);
        fn_801D0BCC(angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        fn_801D0F80(pEvent->mUnknown20);
        fn_801D0544();
        args.mUnknown0C = 0;
        args.mUnknown10 = 0;
        args.mUnknown08 = &m;
        args.mUnknown04 = &pEvent->mUnknown20;
        args.mUnknown00 = pEvent->mUnknown1C;
        pEvent->mUnknown18 = fn_80144CE0(&args, 0, 0);
    } else {
        fn_801D0508();
        fn_801D0C58(&pos);
        fn_801D0BCC(angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        fn_801D0F80(pEvent->mUnknown20);
        fn_801D0544();
    }
    if (pEvent->mUnknown18) {
        pEvent->mUnknown18->mUnknown39C = pPlayer->mMotion.mUnknown40;
        pEvent->mUnknown18->mUnknown3A0 = pPlayer->mMotion.mUnknown44;
        pEvent->mUnknown18->mUnknown3A4 = pPlayer->mMotion.mUnknown48;
    }
}

extern "C" void fn_801455F8(Event_801459F0 *pEvent)
{
    Object_8003DEC4 *pBody = (Object_8003DEC4 *)((Object_80039F5C *)pEvent->mUnknown0C)->mpUnknown4;
    Object_80146094 *pTrail = &pBody->mUnknown5188;
    Vector_80039F5C pos;
    Angles_801EBC18 angles;
    float m[4][4];
    Args_80144CE0 args;

    if (fn_800A33DC() != 0 && fn_800A33DC() != 1 && pTrail->mUnknown57C != 1) {
        return;
    }
    fn_8014529C(pBody, pEvent->mUnknown14, &pos, &angles);
    if (pEvent->mUnknown18 == 0) {
        fn_801D03D0(m);
        m[2][3] = m[1][3] = m[0][3] = 0.0f;
        fn_801D0508();
        fn_801D0C58(&pos);
        fn_801D0BCC(angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        fn_801D0CFC(pBody->mUnknown24);
        fn_801D0F80(pEvent->mUnknown20);
        fn_801D0544();
        args.mUnknown0C = 0;
        args.mUnknown10 = 0;
        args.mUnknown08 = &m;
        args.mUnknown04 = &pEvent->mUnknown20;
        args.mUnknown00 = 0;
        pEvent->mUnknown18 = fn_80144CE0(&args, 0, (Source_80144CE0 *)pBody->mUnknown972);
        if (pEvent->mUnknown18 && pTrail->mUnknown57C == 1) {
            pEvent->mUnknown18->mUnknown7C *= 1.35f;
            pEvent->mUnknown18->mUnknown80 *= 1.35f;
            pEvent->mUnknown18->mUnknown84 *= 1.35f;
            pEvent->mUnknown18->mUnknown88 *= 1.35f;
            pEvent->mUnknown18->mUnknownA8 *= 1.35f;
            pEvent->mUnknown18->mUnknownAC *= 1.35f;
        }
    } else {
        fn_801D0508();
        fn_801D0C58(&pos);
        fn_801D0BCC(angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        fn_801D0CFC(pBody->mUnknown24);
        fn_801D0F80(pEvent->mUnknown20);
        fn_801D0544();
    }
}

extern "C" void fn_80145798(Event_801459F0 *pEvent)
{
    Object_8003DEC4 *pBody = (Object_8003DEC4 *)((Object_80039F5C *)pEvent->mUnknown0C)->mpUnknown4;
    Vector_80039F5C pos;
    float m[4][4];
    Args_80144CE0 args;

    fn_8014529C(pBody, pEvent->mUnknown14, &pos, 0);
    if (fn_800A8444(0) || fn_800A8444(1) || pos.mZ >= 0.25f || pEvent->mUnknown18 != 0 || pEvent->mUnknown04 != 0) {
        return;
    }
    fn_80137AD0(fn_801374BC());
    args.mUnknown00 = 21;
    if (pBody->mUnknown972 != 0) {
        fn_801D03D0(m);
        m[2][3] = m[1][3] = m[0][3] = 0.0f;
        fn_801D03D0(pEvent->mUnknown20);
        pEvent->mUnknown20[0][3] = pos.mX;
        pEvent->mUnknown20[1][3] = pos.mY;
        pEvent->mUnknown20[2][3] = pos.mZ;
        args.mUnknown0C = 0;
        args.mUnknown10 = 0;
        args.mUnknown08 = &m;
        args.mUnknown04 = &pEvent->mUnknown20;
        args.mUnknown00 = fn_80145074(((Source_80144CE0 *)pBody->mUnknown972)->mUnknown08);
        pEvent->mUnknown18 = fn_80144CE0(&args, 0, (Source_80144CE0 *)pBody->mUnknown972);
        pEvent->mUnknown04 = 1;
    }
}

extern "C" void fn_801458C8(Event_801459F0 *pEvent)
{
    float m[4][4];
    Args_80144CE0 args;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    float (*pMatrix)[4][4] = (float (*)[4][4])pEvent->mUnknown08;
    Source_80144CE0 *pSource;
    float speed;

    pos.mX = (*pMatrix)[0][3];
    pos.mY = (*pMatrix)[1][3];
    pos.mZ = (*pMatrix)[2][3];
    fn_80137EC4((Object_80137ABC *)pEvent->mUnknown10, &velocity);
    speed = fn_802270D4(&velocity);
    if (pos.mZ < 0.15f && ((Object_80137ABC *)pEvent->mUnknown10)->mState.mState == 5 && speed > 0.06f
        && pEvent->mUnknown18 == 0) {
        pSource = (Source_80144CE0 *)((Object_80137ABC *)pEvent->mUnknown10)->mpUnknown00->mUnknown660;
        if (pSource != 0) {
            fn_801D03D0(m);
            m[2][3] = m[1][3] = m[0][3] = 0.0f;
            fn_801D03D0(pEvent->mUnknown20);
            pEvent->mUnknown20[0][3] = pos.mX;
            pEvent->mUnknown20[1][3] = pos.mY;
            pEvent->mUnknown20[2][3] = pos.mZ;
            args.mUnknown0C = 0;
            args.mUnknown10 = 0;
            args.mUnknown08 = &m;
            args.mUnknown04 = &pEvent->mUnknown20;
            args.mUnknown00 = fn_80144FE8(pSource->mUnknown08);
            pEvent->mUnknown18 = fn_80144CE0(&args, 0, pSource);
        }
    }
}
